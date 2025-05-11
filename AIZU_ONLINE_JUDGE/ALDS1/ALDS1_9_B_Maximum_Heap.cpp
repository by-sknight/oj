#include <bits/stdc++.h>
#include <iomanip>

void max_heapify(std::vector<int>& vec, int now) {
    int left = 2 * now + 1;
    int right = 2 * now + 2;
    int max_index = now;
    if (left < vec.size() && vec[max_index] < vec[left]) {
        max_index = left;
    }
    if (right < vec.size() && vec[max_index] < vec[right]) {
        max_index = right;
    }
    if (max_index != now) {
        std::swap(vec[max_index], vec[now]);
        max_heapify(vec, max_index);
    }
}

void build_max_heap(std::vector<int>& vec) {
    for (int i = (vec.size() - 1) / 2; i >= 0; i--) {
        max_heapify(vec, i);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) std::cin >> vec[i];

    build_max_heap(vec);
    for (int i = 0; i < vec.size(); i++) {
        if (i != 0) {
            std::cout << " ";
        }
        std::cout << vec[i];
    }
    std::cout << std::endl;
}

// 堆化: 所有叶节点认为是有序的，从中间开始，使其满足堆的性质，如果顶部满足，并且子树满足，因此直接完成，如果顶部不满足，交换后，交换的那一半继续递归下去
