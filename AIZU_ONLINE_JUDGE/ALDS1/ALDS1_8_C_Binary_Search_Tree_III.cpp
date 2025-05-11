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
        now->parent = now_parent;
    } else {
        now_parent->right = now;
        now->parent = now_parent;
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

int remove_subtree_min(Node* node) {
    Node* now = node;
    while (now->left != nullptr) {
        now = now->left;
    }
    Node* now_parent = now->parent;
    int now_val = now->value;
    if (now != node) {
        now_parent->left = now->right;
    } else {
        now_parent->right = now->right;
    }
    if (now->right != nullptr) {
        now->right->parent = now_parent;
    }
    delete now;
    return now_val;
}

void remove(Node* root, int x) {
    Node* now = root;
    // find x position
    while (now != nullptr) {
        if (now->value == x) {
            break;
        } else if (x < now->value) {
            now = now->left;
        } else {
            now = now->right;
        }
    }
    if (now == nullptr) {
        return;
    }
    Node* now_parent = now->parent;
    if (now->left == nullptr && now->right == nullptr) {
        if (now_parent == nullptr) {
            root = nullptr;
        } else if (x >= now_parent->value) {
            now_parent->right = nullptr;
        } else {
            now_parent->left = nullptr;
        }
        delete now;
    } else if (now->left != nullptr && now->right != nullptr) {
        // has left and right subtree. using right subtree
        int subtree_min = remove_subtree_min(now->right);
        now->value = subtree_min;
    } else if (now->left != nullptr) {
        if (now_parent == nullptr) {
            root = nullptr;
        } else if (now_parent->value < x) {
            now_parent->right = now->left;
            now->left->parent = now_parent;
        } else {
            now_parent->left = now->left;
            now->left->parent = now_parent;
        }
        delete now;
    } else { // now->right != nullptr
        if (now_parent == nullptr) {
            root = nullptr;
        } else if (now_parent->value < x) {
            now_parent->right = now->right;
            now->right->parent = now_parent;
        } else {
            now_parent->left = now->right;
            now->right->parent = now_parent;
        }
        delete now;
    }


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
        } else if (command == "delete") {
            std::cin >> x;
            remove(root, x);
        } else if (command == "print") {
            print(root);
        }
    }

    my_release(root);
}

// 增加了删除操作
//   关于删除操作，如果是没有任何子节点，可以直接删除掉就行
//   如果只有一个子节点，将子节点接到父节点上就可以
//   如果有两个子节点，需要从右侧子节点中，找到最小的值，然后换上来，实际直接采用了删除子树的最小节点实现(不过做了一些限制，因为知道第一个节点一定是父节点的右节点)
