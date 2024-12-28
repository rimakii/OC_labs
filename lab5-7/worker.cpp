#include <zmq.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "msg.h"

zmq::context_t context(1);
zmq::socket_t rep_socket(context, ZMQ_REP);
zmq::socket_t pub_socket(context, ZMQ_PUB);

void handle_create(int id, int parent) {
    std::cout << "Creating node " << id << " with parent " << parent << std::endl;
    std::string reply = "Ok: " + std::to_string(getpid());
    zmq::message_t response(reply.size());
    memcpy(response.data(), reply.data(), reply.size());
    rep_socket.send(response);
}

std::vector<int> find_substring(const std::string& text, const std::string& pattern) {
    std::vector<int> indices;
    size_t pos = text.find(pattern);
    while (pos != std::string::npos) {
        indices.push_back(static_cast<int>(pos));
        pos = text.find(pattern, pos + 1);
    }
    return indices;
}

void handle_heartbit(int id, int time) {
    std::string reply = "Ok";
    zmq::message_t response(reply.size());
    memcpy(response.data(), reply.data(), reply.size());
    rep_socket.send(response);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        std::string heartbit_msg = "HB:" + std::to_string(id);
        zmq::message_t msg(heartbit_msg.size());
        memcpy(msg.data(), heartbit_msg.data(), heartbit_msg.size());
        pub_socket.send(msg);
    }
}

void handle_exec(int id, const std::string& text, const std::string& pattern) {
    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;

    std::vector<int> indices = find_substring(text, pattern);
    std::string reply = "Ok:" + std::to_string(id) + ":";
    if (indices.empty()) {
        reply += "-1";
    } else {
        for (size_t i = 0; i < indices.size(); ++i) {
            if (i > 0) reply += ",";
            reply += std::to_string(indices[i]);
        }
    }

    zmq::message_t response(reply.size());
    memcpy(response.data(), reply.data(), reply.size());
    rep_socket.send(response);
}

int main() {
    rep_socket.bind("tcp://*:5555");
    pub_socket.bind("tcp://*:5556");

    while (true) {
        zmq::message_t message;
        rep_socket.recv(&message);
        std::string msg(static_cast<char*>(message.data()), message.size());

        int id, parent, time;
        std::string text, pattern;

        if (sscanf(msg.c_str(), "create %d %d", &id, &parent) == 2) {
            handle_create(id, parent);
        } else if (sscanf(msg.c_str(), "exec %d", &id) == 1) {
            size_t delimiter_pos = msg.find('|');
            if (delimiter_pos != std::string::npos) {
                text = msg.substr(delimiter_pos + 1);
                size_t pattern_pos = text.find('|');
                if (pattern_pos != std::string::npos) {
                    pattern = text.substr(pattern_pos + 1);
                    text = text.substr(0, pattern_pos);
                }
            }
            handle_exec(id, text, pattern);
        } else if (sscanf(msg.c_str(), "heartbit %d %d", &id, &time) == 2) {
            handle_heartbit(id, time);
        }
    }

    return 0;
}