#include <bits/stdc++.h>
#include <iomanip>

void heap_insert(std::vector<int>& vec, int x) {
    int now = vec.size();
    vec.push_back(x);
    while (true) {
        int parent = (now - 1) / 2;
        if (parent < 0 || vec[parent] >= vec[now]) {
            break;
        }
        std::swap(vec[parent], vec[now]);
        now = parent;
    }
}

int heap_remove(std::vector<int>& vec) {
    if (vec.empty()) {
        return -1;
    }
    int ret = vec[0];
    std::swap(vec[0], vec[vec.size() - 1]);
    vec.pop_back();
    int now = 0;
    while (true) {
        int left = 2 * now + 1;
        int right = 2 * now + 2;
        int max_index = now;
        if (left < vec.size() && vec[left] > vec[max_index]) {
            max_index = left;
        }
        if (right < vec.size() && vec[right] > vec[max_index]) {
            max_index = right;
        }
        if (max_index != now) {
            std::swap(vec[now], vec[max_index]);
            now = max_index;
        } else {
            break;
        }
    }
    return ret;
}

int main() {
    std::vector<int> vec;
    std::string command;
    int x;
    while (true) {
        std::cin >> command;
        if (command == "end") {
            break;
        }
        if (command == "insert") {
            std::cin >> x;
            heap_insert(vec, x);
        } else if (command == "extract") {
            std::cout << heap_remove(vec) << std::endl;
        }
    }
}
