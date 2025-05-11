#include <bits/stdc++.h>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) std::cin >> vec[i];

    for (int i = 0; i < n; i++) {
        std::cout << "node " << i + 1 << ": key = " << vec[i] << ", ";
        if ((i + 1) / 2 - 1 >= 0) {
            std::cout << "parent key = " << vec[(i + 1) / 2 - 1] << ", ";
        }
        if ((i + 1) * 2 - 1 < n) {
            std::cout << "left key = " << vec[(i + 1) * 2 - 1] << ", ";
        }
        if ((i + 1) * 2 < n) {
            std::cout << "right key = " << vec[(i + 1) * 2] << ", ";
        }
        std::cout << std::endl;
    }
}

// 如果使用1作为起始的话
// left = now * 2, right = now * 2 + 1, parent = now / 2
// 如果使用0作为起始的话
// left = (now + 1) * 2 - 1 = 2 * now + 1
// right = (now + 1) * 2 = 2 * now + 2
// parent = (now + 1) / 2 - 1 = (now - 1) / 2
