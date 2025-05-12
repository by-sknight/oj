#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 50
#define MAX_PLAN 10
bool valid[MAX_PLAN];
bool must[MAX_PLAN];



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
        vec.push_back(tbs);
        if ((bs & tbs).any()) {
            valid[i] = false;
        } else {
            valid[i] = true;
        }
        must[i] = false;
    }
    int valid_cnt = 0;
    for (int i = 0; i < p; i++) {
        if (valid[i]) {
            valid_cnt += 1;
        }
    }
    if (valid_cnt == 0) {
        std::cout << -1 << std::endl;
        return 0;
    }

    std::bitset<MAX_SIZE> bs_cov = bs;
    for (int i = 0; i < p; i++) {
        if (valid[i]) {
            bs_cov = bs_cov | vec[i];
        }
    }
    if (bs_cov.count() != n * m) {
        std::cout << -1 << std::endl;
        return 0;
    }

    std::vector<int> cover(n * m);
    for (int i = 0; i < n * m; i++) {
        if (bs.test(i)) {
            cover[i] = 99;
        } else {
            cover[i] = 0;
        }
    }
    for (int i = 0; i < p; i++) {
        if (valid[i]) {
            for (int j = 0; j < n * m; j++) {
                if (vec[i].test(j)) {
                    cover[j] += 1;
                }
            }
        }
    }
    for (int i = 0; i < n * m; i++) {
        if (cover[i] == 1) {
            for (int j = 0; j < p; j++) {
                if (!valid[j]) break;
                if (vec[j].test(i)) {
                    must[j] = true;
                }
            }
        }
    }
    std::vector<int> valid_id;
    std::vector<int> must_id;
    std::vector<int> valid_but_not_must_id;
    for (int i = 0; i < p; i++) {
        if (valid[i]) {
            valid_id.push_back(i);
            if (must[i]) {
                must_id.push_back(i);
            } else {
                valid_but_not_must_id.push_back(i);
            }
        }
    }
    // if all must cover all places, no need to check valid but not must
    bs_cov = bs;
    for (auto id : must_id) {
        bs_cov = bs_cov | vec[id];
    }
    if (bs_cov.count() == n * m) {
        std::cout << must_id.size() << std::endl;
        for (int i = 0; i < must_id.size(); i++) {
            if (i != 0) {
                std::cout << " ";
            }
            std::cout << must_id[i] + 1;
        }
        std::cout << std::endl;
        return 0;
    }
    std::bitset<MAX_SIZE> bs_with_must = bs_cov;
    // i: choose numbers
    bool end_flag = false;
    for (int i = 1; i <= valid_but_not_must_id.size(); i++) {
        std::vector<int> choose_box;
        for (int j = 0; j < i; j++) {
            choose_box.push_back(1);
        }
        for (int j = 0; j < valid_but_not_must_id.size() - i; j++) {
            choose_box.push_back(0);
        }

        while (true) {
            bs_cov = bs_with_must;
            for (int k = 0; k < choose_box.size(); k++) {
                if (choose_box[k] == 1) {
                    bs_cov = bs_cov | vec[valid_but_not_must_id[k]];
                }
            }
            if (bs_cov.count() == n * m) {
                // print
                std::vector<int> ret;
                for (int k = 0; k < p; k++) {
                    if (must[k]) {
                        ret.push_back(k);
                    }
                }
                for (int k = 0; k < choose_box.size(); k++) {
                    if (choose_box[k] == 1) {
                        ret.push_back(valid_but_not_must_id[k]);
                    }
                }
                std::sort(ret.begin(), ret.end());
                std::cout << ret.size() << std::endl;
                for (int k = 0; k < ret.size(); k++) {
                    if (k != 0) {
                        std::cout << " ";
                    }
                    std::cout << ret[k] + 1;
                }
                std::cout << std::endl;
                return 0;
            }
            if (!std::prev_permutation(choose_box.begin(), choose_box.end())) {
                break;
            }
        }
    }
}
// 就一点点试
