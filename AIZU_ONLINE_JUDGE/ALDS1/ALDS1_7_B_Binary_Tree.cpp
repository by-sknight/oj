#include <bits/stdc++.h>
#include <iomanip>

#define MAX 30

struct Node {
    int parent = -1;
    int left = -1;
    int right = -1;
};

int sibling[MAX];
int depth[MAX];
int height[MAX];
Node nodes[MAX];

int calc(int now, int d) {
    depth[now] = d;
    int left_height = 0, right_height = 0;
    if (nodes[now].left != -1) {
        left_height = calc(nodes[now].left, d + 1);
    }
    if (nodes[now].right != -1) {
        right_height = calc(nodes[now].right, d + 1);
    }
    height[now] = std::max(left_height, right_height);
    return height[now] + 1;
}

void display(int n) {
    for (int i = 0; i < n; i++) {
        int degree = 0;
        if (nodes[i].left != -1) {
            degree += 1;
        }
        if (nodes[i].right != -1) {
            degree += 1;
        }
        std::string type;
        if (nodes[i].parent == -1) {
            type = "root";
        } else if (degree == 0) {
            type = "leaf";
        } else {
            type = "internal node";
        }
        std::cout << "node " << i << ": parent = " << nodes[i].parent << ", sibling = " << sibling[i]
        << ", degree = " << degree << ", depth = " << depth[i] << ", height = " << height[i]
        << ", " << type << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        sibling[i] = -1;
        depth[i] = -1;
        height[i] = -1;
    }
    int x, l, r;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> l >> r;
        nodes[x].left = l;
        nodes[x].right = r;
        if (l != -1) {
            nodes[l].parent = x;
            sibling[l] = r;
        }
        if (r != -1) {
            nodes[r].parent = x;
            sibling[r] = l;
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
    calc(root, 0);
    display(n);
}

// 题目中给出n个元素，0->n-1的限制条件
// 这次就使用相对通俗一些的方式，Node只存储父节点、左右节点，其余的兄弟节点、深度、高度都单独存储
//    (其实也可以所有的元素都整合在一起使用id作为小标，或者所有的元素都拆分开)
// 初始化之后，读取并存储元素，在读取的过程中，就顺便更新了id对应的左右节点以及子节点的父节点，兄弟节点信息
// 然后找到根节点，去计算所有节点的深度与高度(很适合使用递归，因此单独实现比较合理，使用队列或者堆栈会更复杂)，最后打印出来
// 关于递归的一个有趣的说法: 循环可能会提升程序的性能，递归可能会提升程序员的性能
//     https://stackoverflow.com/a/72694
