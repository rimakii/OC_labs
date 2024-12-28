#include "../include/manage_node.h"
#include <iostream>
#include <string> 
#include <unistd.h> 

// ???????????: ????????????? ZeroMQ ???????
Manage_node::Manage_node()
    : context(), publisher(context, zmq::socket_type::pub), sub(context, zmq::socket_type::sub) {
    publisher.bind("tcp://127.0.0.1:5555");
    sub.bind("tcp://127.0.0.1:5556");
    sub.set(zmq::sockopt::subscribe, "");
}

// ??????????: ?????????? ???????
Manage_node::~Manage_node() {
    sub.disconnect("tcp://127.0.0.1:5556");
    publisher.disconnect("tcp://127.0.0.1:5555");
}

// ????????? ????????? (????????, ??? pingall)
void Manage_node::receive_msg(Message_type msg_type, tree& tree) {
    int max_attempts = 5;
    int attempt = 0;

    while (attempt < max_attempts) {
        zmq::message_t reply;
        zmq::recv_result_t res = sub.recv(reply, zmq::recv_flags::dontwait);
        if (res.has_value()) {
            string id_str = reply.to_string();
            int id = stoi(id_str);
            tree.change_availability(id, true);
        } else {
            ++attempt;
            usleep(10000);
        }
    }
}

// ???????? ?????????
bool Manage_node::send_msg(Message msg) {
    string type_str = to_string(msg.type);

    switch (msg.type) {
        case Message_type::create: {
            string parent_id_str = to_string(msg.data[0]);
            string new_id_str = to_string(msg.data[1]);

            zmq::message_t request1(parent_id_str);
            publisher.send(request1, zmq::send_flags::sndmore);

            zmq::message_t request2(type_str);
            publisher.send(request2, zmq::send_flags::sndmore);

            zmq::message_t request3(new_id_str);
            publisher.send(request3, zmq::send_flags::none);

            return true;
        }
        case Message_type::exec: {
            string id_str = to_string(msg.data[0]);
            string n_str = to_string(msg.data[1]);

            zmq::message_t request1(id_str);
            publisher.send(request1, zmq::send_flags::sndmore);

            zmq::message_t request2(type_str);
            publisher.send(request2, zmq::send_flags::sndmore);

            zmq::message_t request3(n_str);
            publisher.send(request3, zmq::send_flags::sndmore);

            for (int i = 0; i < msg.data[1]; i++) {
                string num_str = to_string(msg.data[2 + i]);
                zmq::message_t num_msg(num_str);
                if (i == msg.data[1] - 1) {
                    publisher.send(num_msg, zmq::send_flags::none);
                } else {
                    publisher.send(num_msg, zmq::send_flags::sndmore);
                }
            }
            return true;
        }
        case Message_type::heartbit: {
            string time_str = to_string(msg.data[0]);
            zmq::message_t request(time_str);
            publisher.send(request, zmq::send_flags::sndmore);

            zmq::message_t type_msg(to_string(msg.type));
            publisher.send(type_msg, zmq::send_flags::none);

            return true;
        }
        case Message_type::ping: {
            string id_str = to_string(msg.data[0]);
            zmq::message_t request(id_str);
            publisher.send(request, zmq::send_flags::sndmore);

            zmq::message_t type_msg(to_string(msg.type));
            publisher.send(type_msg, zmq::send_flags::none);

            return true;
        }
        default:
            return false;
    }
    return false;
}