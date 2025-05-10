#include <bits/stdc++.h>
#include <iomanip>

void counting_sort(std::vector<int>& va, std::vector<int>& vb, int k) {
    std::vector<int> vc(k + 1, 0);
    vb.resize(va.size());
    for (auto a : va) {
        vc[a] += 1;
    }
    for (int i = 1; i <= k; i++) {
        vc[i] += vc[i - 1];
    }
    for (auto a : va) {
        vb[vc[a] - 1] = a; // vc[i] 表示小于等于自己的元素数量 如果vc[i]==1，意味着小于等于自己元素有1个，那就是自己，所以需要减1
        vc[a] -= 1;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec_a(n);
    int max_value = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> vec_a[i];
        max_value = std::max(max_value, vec_a[i]);
    }
    std::vector<int> vec_b;
    counting_sort(vec_a, vec_b, max_value);
    for (int i = 0; i < vec_b.size(); i++) {
        if (i != 0) {
            std::cout << " ";
        }
        std::cout << vec_b[i];
    }
    std::cout << std::endl;
}
