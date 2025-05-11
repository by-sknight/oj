#include <bits/stdc++.h>
#include <iomanip>

struct Node {
    int value = 0;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
};

void insert(Node*& root, int x) {
    Node* now_parent = nullptr;
    Node* now = root;
    while (now != nullptr) {
        now_parent = now;
        if (x < now->value) {
            now = now->left;
        } else {
            now = now->right;
        }
    }
    now = new Node();
    now->value = x;
    if (now_parent == nullptr) {
        root = now;
    } else if (x < now_parent->value) {
        now_parent->left = now;
    } else {
        now_parent->right = now;
    }
}

void find(Node* root, int x) {
    Node* now = root;
    while (now != nullptr) {
        if (now->value == x) {
            std::cout << "yes" << std::endl;
            return;
        } else if (x < now->value) {
            now = now->left;
        } else {
            now = now->right;
        }
    }
    std::cout << "no" << std::endl;
}

void inorder(Node* node) {
    if (node == nullptr) {
        return;
    }
    inorder(node->left);
    std::cout << " " << node->value;
    inorder(node->right);
}

void preorder(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << " " << node->value;
    preorder(node->left);
    preorder(node->right);
}

void print(Node* node) {
    inorder(node);
    std::cout << std::endl;
    preorder(node);
    std::cout << std::endl;
}

void my_release(Node* node) {
    if (node == nullptr) {
        return;
    }
    my_release(node->left);
    my_release(node->right);
    delete node;
}

int main() {
    int n;
    std::cin >> n;

    std::string command;
    int x;
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> x;
            insert(root, x);
        } else if (command == "find") {
            std::cin >> x;
            find(root, x);
        } else if (command == "print") {
            print(root);
        }
    }

    my_release(root);
}

// 添加了 find
