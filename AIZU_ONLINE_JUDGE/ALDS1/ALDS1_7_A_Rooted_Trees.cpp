#include <bits/stdc++.h>
#include <iomanip>

struct Node {
    int id = 0;
    int parent = -1;
    int depth = 0;
    std::vector<int> childes;
    bool operator<(const Node& o) {
        if (id != o.id) {
            return id < o.id;
        }
        return false;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::map<int, Node> my_map;

    int id, k, x;
    // init
    for (int i = 0; i < n; i++) {
        std::cin >> id >> k;
        Node node;
        node.id = id;
        for (int j = 0; j < k; j++) {
            std::cin >> x;
            node.childes.push_back(x);
        }
        my_map[id] = node;
    }
    // update parent
    for (auto node : my_map) {
        if (!node.second.childes.empty()) {
            for (auto ch : node.second.childes) {
                my_map[ch].parent = node.second.id;
            }
        }
    }
    // find root node
    int root_node;
    for (auto node : my_map) {
        if (node.second.parent == -1) {
            root_node = node.second.id;
            break;
        }
    }
    // update all depth
    std::queue<std::pair<int, int>> id_depth_que;
    id_depth_que.push({root_node, 0});
    while (!id_depth_que.empty()) {
        int id_now = id_depth_que.front().first;
        int depth_now = id_depth_que.front().second;
        id_depth_que.pop();
        my_map[id_now].depth = depth_now;
        for (auto node_id : my_map[id_now].childes) {
            id_depth_que.push({node_id, depth_now + 1});
        }
    }

    // print
    for (auto node : my_map) {
        Node nd = node.second;
        std::cout << "node " << nd.id << ": parent = " << nd.parent << ", depth = " << nd.depth << ", ";
        if (nd.parent == -1) {
            std::cout << "root";
        } else if (!nd.childes.empty()) {
            std::cout << "internal node";
        } else {
            std::cout << "leaf";
        }
        std::cout << ", [";
        for (int i = 0; i < nd.childes.size(); i++) {
            if (i != 0) {
                std::cout << ", ";
            }
            std::cout << nd.childes[i];
        }
        std::cout << "]" << std::endl;
    }

}

// 没有按照标准解题思路
// 按照保存所有可直接保留的数据，按照子节点信息去更新子节点的父节点信息，寻找根节点
// 设置根节点深度为0，依次更新所有子节点深度，打印的流程
