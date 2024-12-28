#include <iostream>
#include <string>
#include <zmq.hpp>
#include <unistd.h>
#include <signal.h>
#include <sys/prctl.h>
#include <cstdlib>
#include "../include/msg.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <node_id>\n";
        return 1;
    }
    string my_id_str = argv[1];

    zmq::context_t context;

    // ????????? ???????
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.connect("tcp://127.0.0.1:5556"); // ???? ??? ???????? ?????????

    zmq::socket_t sub(context, zmq::socket_type::sub);
    sub.connect("tcp://127.0.0.1:5555"); // ???? ??? ????????? ?????????

    // ???????? ?? ????????? ??? ????? ????
    sub.set(zmq::sockopt::subscribe, my_id_str);
    // ???????? ?? ????????????????? ????????? (????????, pingall)
    sub.set(zmq::sockopt::subscribe, "-100");

    // ???????? ??????? ? ??????????
    {
        zmq::message_t ready_msg(my_id_str);
        publisher.send(ready_msg, zmq::send_flags::none);
    }

    // ????? ???????, ???? ???????????? ??????? ??????????
    prctl(PR_SET_PDEATHSIG, SIGKILL);

    // ???????? ???? ????????? ?????????
    while (true) {
        zmq::message_t first_part;
        auto res = sub.recv(first_part, zmq::recv_flags::none);
        if (!res.has_value()) {
            continue;
        }
        string target_id = first_part.to_string();

        if (target_id == "-100") {
            // ????????? ????????????????? ????????? (????????, pingall)
            zmq::message_t second_part;
            res = sub.recv(second_part, zmq::recv_flags::none);
            if (!res.has_value()) {
                continue;
            }
            string cmd_str = second_part.to_string();
            if (cmd_str == to_string(Message_type::pingall)) {
                zmq::message_t resp(my_id_str);
                publisher.send(resp, zmq::send_flags::none);
            }
        } else if (target_id == my_id_str) {
            // ????????? ????????? ??? ????? ????
            zmq::message_t second_part;
            res = sub.recv(second_part, zmq::recv_flags::none);
            if (!res.has_value()) {
                continue;
            }
            string cmd_str = second_part.to_string();

            if (cmd_str == to_string(Message_type::create)) {
                // ????????? ??????? create
                zmq::message_t new_child_msg;
                res = sub.recv(new_child_msg, zmq::recv_flags::none);
                if (!res.has_value()) {
                    continue;
                }
                string new_id_str = new_child_msg.to_string();

                int pid = fork();
                if (pid == 0) {
                    execl("./node", "./node", new_id_str.c_str(), NULL);
                    perror("execl failed");
                    _exit(1);
                } else if (pid > 0) {
                    cout << "Ok:" << my_id_str << ": " << pid << "\n";
                } else {
                    perror("fork failed");
                }
            } else if (cmd_str == to_string(Message_type::exec)) {
                // ????????? ??????? exec
                zmq::message_t n_msg;
                res = sub.recv(n_msg, zmq::recv_flags::none);
                if (!res.has_value()) {
                    cerr << "Error: Failed to receive text length" << endl;
                    continue;
                }
                int n = stoi(n_msg.to_string());

                string text_string;
                for (int i = 0; i < n; i++) {
                    zmq::message_t char_msg;
                    res = sub.recv(char_msg, zmq::recv_flags::none);
                    if (!res.has_value()) {
                        cerr << "Error: Failed to receive text character at index " << i << endl;
                        break;
                    }
                    text_string += (char)stoi(char_msg.to_string());
                }

                zmq::message_t m_msg;
                res = sub.recv(m_msg, zmq::recv_flags::none);
                if (!res.has_value()) {
                    cerr << "Error: Failed to receive pattern length" << endl;
                    continue;
                }
                int m = stoi(m_msg.to_string());

                string pattern_string;
                for (int i = 0; i < m; i++) {
                    zmq::message_t char_msg;
                    res = sub.recv(char_msg, zmq::recv_flags::none);
                    if (!res.has_value()) {
                        cerr << "Error: Failed to receive pattern character at index " << i << endl;
                        break;
                    }
                    pattern_string += (char)stoi(char_msg.to_string());
                }

                // ????? ???? ????????? ?????????
                size_t pos = text_string.find(pattern_string);
                string result = "";

                while (pos != string::npos) {
                    if (!result.empty()) {
                        result += ";"; // ????????? ??????? ?????? ? ???????
                    }
                    result += to_string(pos); // ????????? ?????? ?????????
                    pos = text_string.find(pattern_string, pos + 1); // ???? ????????? ?????????
                }

                // ???? ????????? ?? ???????, ?????????? -1
                if (result.empty()) {
                    result = "-1";
                }

                // ??????? ?????????
                cout << "Ok:" << my_id_str << ": " << result << "\n";
            }
        } else {
            // ????????? ?? ??? ????? ????, ??????????
            zmq::message_t discard;
            res = sub.recv(discard, zmq::recv_flags::none);
        }
    }

    return 0;
}