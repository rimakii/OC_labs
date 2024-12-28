#pragma once
#include <iostream>
#include <vector>

struct node {
    int ID;
    bool available = false;
    node *child = nullptr;
    node *sibling = nullptr;
};

class tree {
private:
    node *root = nullptr;
    int node_cnt = 0;

    node *find_node(node *current, int ID) {
        if (!current) return nullptr;
        if (current->ID == ID) return current;
        node *found = find_node(current->child, ID);
        if (found) return found;
        return find_node(current->sibling, ID);
    }

    bool insert_bfs(int ID) {
        node *newNode = new node;
        newNode->ID = ID;

        if (!root) {
            root = newNode;
            node_cnt = 1;
            return true;
        }

        std::vector<node*> queue;
        queue.push_back(root);

        while (!queue.empty()) {
            node *current = queue.front();
            queue.erase(queue.begin());

            if (!current->child) {
                current->child = newNode;
                node_cnt++;
                return true;
            } else {
                current = current->child;
                while (current->sibling) {
                    queue.push_back(current);
                    current = current->sibling;
                }
                queue.push_back(current);
            }
        }

        delete newNode;
        return false;
    }

    int find_parent_id(node *current, int child_id) {
        if (!current) return -1;
        if (current->child && current->child->ID == child_id) return current->ID;
        if (current->sibling && current->sibling->ID == child_id) return current->ID;
        int found = find_parent_id(current->child, child_id);
        if (found != -1) return found;
        return find_parent_id(current->sibling, child_id);
    }

    void draw_subtree(node *current, int level) {
        if (!current) return;
        draw_subtree(current->sibling, level);
        for (int i = 0; i < level; ++i) {
            std::cout << "   ";
        }
        std::cout << current->ID << (current->available ? "(+)" : "(-)") << "\n";
        draw_subtree(current->child, level + 1);
    }

    void bypass_reset_subtree(node *current) {
        if (!current) return;
        current->available = false;
        bypass_reset_subtree(current->sibling);
        bypass_reset_subtree(current->child);
    }

    void bypass_collect_unavailable(node *current, std::vector<int> &unavailable) {
        if (!current) return;
        if (!current->available) {
            unavailable.push_back(current->ID);
        }
        bypass_collect_unavailable(current->sibling, unavailable);
        bypass_collect_unavailable(current->child, unavailable);
    }

public:
    tree() {}
    ~tree() {}

    bool is_in_tree(int ID) {
        return find_node(root, ID) != nullptr;
    }

    bool insert(int ID) {
        if (is_in_tree(ID)) {
            return false;
        }
        return insert_bfs(ID);
    }

    node *get(int ID) {
        return find_node(root, ID);
    }

    node *get_root() {
        return root;
    }

    int parent_id(int child_id) {
        if (!root || !is_in_tree(child_id)) {
            return -1;
        }
        if (root->ID == child_id) {
            return -1;
        }
        return find_parent_id(root, child_id);
    }

    void draw_tree() {
        draw_subtree(root, 0);
    }

    bool is_available(int ID) {
        node *n = get(ID);
        if (!n) return false;
        return n->available;
    }

    void change_availability(int ID, bool status) {
        node *n = get(ID);
        if (n) {
            n->available = status;
        }
    }

    void bypass_reset(node *current) {
        bypass_reset_subtree(current);
    }

    void bypass(node *current, std::vector<int> &unavailable) {
        bypass_collect_unavailable(current, unavailable);
    }

    int cnt() {
        return node_cnt;
    }
};