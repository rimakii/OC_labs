#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>
#include <zmq.hpp>
#include "../include/tree.hpp"
#include "../include/manage_node.h"
#include "../include/msg.h"

using namespace std;

int start_node_process(int child_id) {
    int pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1;
    } else if (pid == 0) {
        // child
        string id_str = to_string(child_id);
        if (access("./node", X_OK) == -1) {
            perror("Error: ./node not found or not executable");
            _exit(1);
        }
        execl("./node", "./node", id_str.c_str(), nullptr);
        // ???? ????? ????, execl ?? ????????
        perror("execl failed");
        _exit(1);
    } else {
        // parent
        return pid; // ?????? PID
    }
}

int main() {
    map<int, int> parent_of;
    Manage_node nodeManager;

    cout << "Available commands:\n"
         << " create <child_id> <parent_id>\n"
         << " exec <id> <text_string> <pattern_string>\n"
         << " heartbit <time>\n"
         << " ping <id>\n"
         << " q (exit)\n\n";

    while (true) {
        string cmd;
        if (!(cin >> cmd)) {
            // EOF
            break;
        }

        if (cmd == "create") {
            int child_id, parent_id;
            cin >> child_id >> parent_id;
            if (!cin.good()) {
                cout << "Error: bad input\n";
                cin.clear();
                continue;
            }
            if (child_id < 0) {
                cout << "Error: ID must be >= 0\n";
                continue;
            }
            if (parent_of.count(child_id) > 0 || child_id == -1) {
                cout << "Error: Already exists\n";
                continue;
            }
            parent_of[child_id] = parent_id;

            if (parent_id == -1) {
                int pid = start_node_process(child_id);
                if (pid > 0) {
                    cout << "Ok: " << child_id << " (PID=" << pid << ")\n";
                }
            } else {
                Message msg;
                msg.type = Message_type::create;
                msg.data.push_back(parent_id);
                msg.data.push_back(child_id);

                if (!nodeManager.send_msg(msg)) {
                    cout << "Error: can't send create-message\n";
                } else {
                    cout << "Ok: " << parent_id << " -> " << child_id << "\n";
                }
            }
        } else if (cmd == "exec") {
            int id;
            string text_string, pattern_string;
            cin >> id >> text_string >> pattern_string;
            if (!cin.good()) {
                cout << "Error: bad input for exec\n";
                cin.clear();
                continue;
            }
            if (!parent_of.count(id)) {
                cout << "Error: no such node\n";
                continue;
            }

            Message msg;
            msg.type = Message_type::exec;
            msg.data.push_back(id);
            msg.data.push_back(text_string.length());
            for (char c : text_string) {
                msg.data.push_back((int)c);
            }
            msg.data.push_back(pattern_string.length());
            for (char c : pattern_string) {
                msg.data.push_back((int)c);
            }

            if (!nodeManager.send_msg(msg)) {
                cout << "Error: exec send failed\n";
            }
        } else if (cmd == "heartbit") {
            int time;
            cin >> time;
            if (!cin.good()) {
                cout << "Error: bad input for heartbit\n";
                cin.clear();
                continue;
            }

            Message msg;
            msg.type = Message_type::heartbit;
            msg.data.push_back(time);

            if (!nodeManager.send_msg(msg)) {
                cout << "Error: heartbit send failed\n";
            } else {
                cout << "Ok\n";
            }
        } else if (cmd == "ping") {
            int id;
            cin >> id;
            if (!cin.good()) {
                cout << "Error: bad input for ping\n";
                cin.clear();
                continue;
            }

            Message msg;
            msg.type = Message_type::ping;
            msg.data.push_back(id);

            if (!nodeManager.send_msg(msg)) {
                cout << "Error: ping send failed\n";
            }
        } else if (cmd == "q") {
            cout << "Exit.\n";
            break;
        } else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}