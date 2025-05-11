#include <bits/stdc++.h>
#include <iomanip>

#define MAX 30

struct Node {
    int parent = -1;
    int left = -1;
    int right = -1;
};

Node nodes[MAX];

void preorder(int now) {
    if (now == -1)
        return;
    std::cout << " " << now;
    preorder(nodes[now].left);
    preorder(nodes[now].right);
}

void inorder(int now) {
    if (now == -1)
        return;
    inorder(nodes[now].left);
    std::cout << " " << now;
    inorder(nodes[now].right);
}

void postorder(int now) {
    if (now == -1)
        return;
    postorder(nodes[now].left);
    postorder(nodes[now].right);
    std::cout << " " << now;
}

int main() {
    int n;
    std::cin >> n;
    int x, l, r;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> l >> r;
        if (l != -1) {
            nodes[x].left = l;
            nodes[l].parent = x;
        }
        if (r != -1) {
            nodes[x].right = r;
            nodes[r].parent = x;
        }
    }
    // find root
    int root = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i].parent == -1) {
            root = i;
            break;
        }
    }
    // calc depth and height
    std::cout << "Preorder" << std::endl;
    preorder(root);
    std::cout << std::endl;
    std::cout << "Inorder" << std::endl;
    inorder(root);
    std::cout << std::endl;
    std::cout << "Postorder" << std::endl;
    postorder(root);
    std::cout << std::endl;
}
