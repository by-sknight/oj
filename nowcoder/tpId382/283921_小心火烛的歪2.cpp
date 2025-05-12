#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 50

int main() {
    int n, m, p;
    char c;
    std::cin >> n >> m >> p;
    std::bitset<MAX_SIZE> bs(0);
    std::vector<std::bitset<MAX_SIZE>> vec;
    for (int i = 0; i < n * m; i++) {
        std::cin >> c;
        if (c == '1') {
            bs.set(i);
        }
    }
    if (bs.count() == n * m) {
        std::cout << 0 << std::endl;
        return 0;
    }
    for (int i = 0; i < p; i++) {
        std::bitset<MAX_SIZE> tbs(0);
        for (int j = 0; j < n * m; j++) {
            std::cin >> c;
            if (c == '1') {
                tbs.set(j);
            }
        }
        if ((bs & tbs).any()) {
            tbs = 0;
        }
        vec.push_back(tbs);
    }
    std::bitset<MAX_SIZE> bs_cov;
    for (int i = 1; i <= p; i++) {
        std::vector<int> choose_box;
        for (int j = 0; j < i; j++) {
            choose_box.push_back(1);
        }
        for (int j = 0; j < p - i; j++) {
            choose_box.push_back(0);
        }
        while (true) {
            bs_cov = bs;
            for (int j = 0; j < choose_box.size(); j++) {
                if (choose_box[j] == 1) {
                    bs_cov = bs_cov | vec[j];
                }
            }
            if (bs_cov.count() == n * m) {
                std::cout << i << std::endl;
                std::vector<int> ret;
                for (int j = 0; j < choose_box.size(); j++) {
                    if (choose_box[j] == 1) {
                        ret.push_back(j);
                    }
                }
                for (int j = 0; j < ret.size(); j++) {
                    if (j != 0) {
                        std::cout << " ";
                    }
                    std::cout << ret[j] + 1;
                }
                std::cout << std::endl;
                return 0;
            }
            if (!std::prev_permutation(choose_box.begin(), choose_box.end())) {
                break;
            }
        }
    }
    std::cout << -1 << std::endl;
}

// 不考虑各种特殊场景来减少性能损耗，直接硬算
