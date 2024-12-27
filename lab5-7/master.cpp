#include <zmq.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <chrono>
#include <map>
#include <thread>

zmq::context_t context(1);
zmq::socket_t req_socket(context, ZMQ_REQ); // ????? ??? ????????/???????
zmq::socket_t sub_socket(context, ZMQ_SUB); // ????? ??? ????????? heartbit

struct Node {
    int id;
    int pid;
    std::vector<Node> children;
};

Node* root = nullptr;
std::map<int, std::chrono::steady_clock::time_point> last_heartbit_time;
int heartbit_interval = 0;

Node* find_node(Node* current, int id) {
    if (current == nullptr) return nullptr;
    if (current->id == id) return current;
    for (auto& child : current->children) {
        Node* found = find_node(&child, id);
        if (found != nullptr) return found;
    }
    return nullptr;
}

void create_node(int id, int parent) {
    if (find_node(root, id) != nullptr) {
        std::cout << "Error: Already exists" << std::endl;
        return;
    }

    Node* parent_node = find_node(root, parent);
    if (parent != -1 && parent_node == nullptr) {
        std::cout << "Error: Parent not found" << std::endl;
        return;
    }

    std::string message = "create " + std::to_string(id) + " " + std::to_string(parent);
    zmq::message_t request(message.size());
    memcpy(request.data(), message.data(), message.size());
    req_socket.send(request);

    zmq::message_t reply;
    req_socket.recv(&reply);
    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    std::cout << reply_str << std::endl;

    if (reply_str.find("Ok:") == 0) {
        int pid = std::stoi(reply_str.substr(4));
        Node* new_node = new Node{id, pid, {}};

        if (parent == -1) {
            root = new_node;
        } else {
            parent_node->children.push_back(*new_node);
        }
    }
}

void exec_command(int id) {
    std::string text, pattern;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    std::cout << "Enter pattern: ";
    std::getline(std::cin, pattern);

    // ?????????? ???????, ????? ? ??????? ? ???? ?????????
    std::string message = "exec " + std::to_string(id) + "|" + text + "|" + pattern;

    // ?????????? ?????????
    zmq::message_t request(message.size());
    memcpy(request.data(), message.data(), message.size());
    req_socket.send(request);

    // ???????? ?????
    zmq::message_t reply;
    req_socket.recv(&reply);
    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    std::cout << reply_str << std::endl;
}

void heartbit(int id, int time) {
    heartbit_interval = time;
    std::string message = "heartbit " + std::to_string(id) + " " + std::to_string(time);
    zmq::message_t request(message.size());
    memcpy(request.data(), message.data(), message.size());
    req_socket.send(request);

    zmq::message_t reply;
    req_socket.recv(&reply);
    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    std::cout << reply_str << std::endl;
}

void ping(int id) {
    Node* node = find_node(root, id);
    if (node == nullptr) {
        std::cout << "Error: Node not found" << std::endl;
        return;
    }

    auto now = std::chrono::steady_clock::now();
    auto last_time = last_heartbit_time[id];
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();

    if (elapsed <= 4 * heartbit_interval) {
        std::cout << "Ok: 1" << std::endl; // ???? ????????
    } else {
        std::cout << "Ok: 0" << std::endl; // ???? ??????????
    }
}

void check_availability() {
    std::map<int, bool> node_unavailable; // ????? ????????????? ?????

    while (true) {
        if (heartbit_interval > 0) {
            zmq::message_t heartbit_msg;
            if (sub_socket.recv(&heartbit_msg, ZMQ_NOBLOCK)) {
                std::string msg(static_cast<char*>(heartbit_msg.data()), heartbit_msg.size());
                if (msg.find("HB:") == 0) {
                    int id = std::stoi(msg.substr(3));
                    last_heartbit_time[id] = std::chrono::steady_clock::now();
                    node_unavailable[id] = false; // ???? ????? ????????
                }
            }

            auto now = std::chrono::steady_clock::now();
            for (auto& [id, last_time] : last_heartbit_time) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();
                if (elapsed > 4 * heartbit_interval && !node_unavailable[id]) {
                    std::cout << "Heartbit: node " << id << " is unavailable now" << std::endl;
                    node_unavailable[id] = true; // ???? ??????????
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbit_interval));
    }
}

int main() {
    req_socket.connect("tcp://localhost:5555"); // ????? ??? ????????/???????
    sub_socket.connect("tcp://localhost:5556"); // ????? ??? ????????? heartbit
    sub_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0); // ????????????? ?? ??? ?????????

    // ?????? ?????? ??? ???????? ??????????? ?????
    std::thread availability_thread(check_availability);
    availability_thread.detach();

    std::string command;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command)) {
            break; // ????? ??? EOF (Ctrl+D)
        }

        if (command.find("create") == 0) {
            int id, parent;
            if (sscanf(command.c_str(), "create %d %d", &id, &parent) == 2) {
                create_node(id, parent);
            } else {
                std::cout << "Error: Invalid command format" << std::endl;
            }
        } else if (command.find("exec") == 0) {
            int id;
            if (sscanf(command.c_str(), "exec %d", &id) == 1) {
                exec_command(id);
            } else {
                std::cout << "Error: Invalid command format" << std::endl;
            }
        } else if (command.find("heartbit") == 0) {
            int id, time;
            if (sscanf(command.c_str(), "heartbit %d %d", &id, &time) == 2) {
                heartbit(id, time);
            } else {
                std::cout << "Error: Invalid command format" << std::endl;
            }
        } else if (command.find("ping") == 0) {
            int id;
            if (sscanf(command.c_str(), "ping %d", &id) == 1) {
                ping(id);
            } else {
                std::cout << "Error: Invalid command format" << std::endl;
            }
        } else if (command == "exit") {
            break; // ????? ?? ?????
        } else {
            std::cout << "Error: Unknown command" << std::endl;
        }
    }

    return 0;
}