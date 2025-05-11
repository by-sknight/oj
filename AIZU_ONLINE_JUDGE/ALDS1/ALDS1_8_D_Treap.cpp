#include <bits/stdc++.h>
#include <iomanip>

struct Treap {
    int value = 0;
    int priority = 0;
    Treap* left = nullptr;
    Treap* right = nullptr;
    Treap(int value, int priority, Treap* left = nullptr, Treap* right = nullptr) {
        this->value = value;
        this->priority = priority;
        this->left = left;
        this->right = right;
    }
};

Treap* right_rotate(Treap* now) {
    Treap* new_root = now->left;
    now->left = new_root->right;
    new_root->right = now;
    return new_root;
}

Treap* left_rotate(Treap* now) {
    Treap* new_root = now->right;
    now->right = new_root->left;
    new_root->left = now;
    return new_root;
}
Treap* insert(Treap* now, int x, int p) {
    if (now == nullptr) {
        return new Treap(x, p);
    }
    if (x < now->value) {
        now->left = insert(now->left, x, p);
        if (now->left->priority > now->priority) {
            now = right_rotate(now);
        }
    } else {
        now->right = insert(now->right, x, p);
        if (now->right->priority > now->priority) {
            now = left_rotate(now);
        }
    }
    return now;
}

bool find(Treap* now, int x) {
    if (now == nullptr) {
        return false;
    }
    if (x == now->value) {
        return true;
    } else if (x < now->value) {
        return find(now->left, x);
    } else { // x > now->value
        return find(now->right, x);
    }
}

Treap* remove(Treap* now, int x);

Treap* _remove(Treap* now, int x) {
    if (now->left == nullptr && now->right == nullptr) {
        delete now;
        return nullptr;
    } else if (now->right == nullptr) { // has left subtree
        now = right_rotate(now);
    } else if (now->left == nullptr) {  // has right subtree
        now = left_rotate(now);
    } else { // has left and right subtree
        if (now->left->priority > now->right->priority) {
            now = right_rotate(now);
        } else {
            now = left_rotate(now);
        }
    }
    Treap* ret = remove(now, x);
    return ret;
//    return remove(now, x);
}

Treap* remove(Treap* now, int x) {
    if (now == nullptr) {
        return nullptr;
    }
    if (x == now->value) {
        Treap* ret = _remove(now, x);
        return ret;
//        return _remove(now, x);
    } else if (x < now->value) {
        now->left = remove(now->left, x);
    } else { // x > now->value
        now->right = remove(now->right, x);
    }
    return now;
}

void inorder(Treap* now) {
    if (now == nullptr) {
        return;
    }
    inorder(now->left);
    std::cout << " " << now->value;
    inorder(now->right);
}

void preorder(Treap* now) {
    if (now == nullptr) {
        return;
    }
    std::cout << " " << now->value;
    preorder(now->left);
    preorder(now->right);
}

void print(Treap* root) {
    inorder(root);
    std::cout << std::endl;
    preorder(root);
    std::cout << std::endl;
}

void my_release(Treap* now) {
    if (now == nullptr) {
        return;
    }
    my_release(now->left);
    my_release(now->right);
    delete now;
}

int main() {
    int n;
    std::cin >> n;

    std::string command;
    int x, p;
    Treap* root = nullptr;
    for (int i = 0; i < n; i++) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> x >> p;
            root = insert(root, x, p);
        } else if (command == "find") {
            std::cin >> x;
            std::cout << (find(root, x) ? "yes" : "no") << std::endl;
        } else if (command == "delete") {
            std::cin >> x;
            root = remove(root, x);
        } else if (command == "print") {
            print(root);
        }
    }

    my_release(root);
}

// 二分查找树 + Heap(优先级堆)
// 通过引入随机优先级，来进行树的旋转，保证一定程度的平衡，删除的时候，是一直通过旋转
// 将待删除节点移动到叶节点的位置，才进行删除，递归思想值得学习与理解
// 代码实现是基于题目中给出的伪代码实现的
