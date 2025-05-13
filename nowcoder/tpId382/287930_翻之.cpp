#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    char ch;
    std::cin >> n >> m;
    std::vector<bool> vec(n*m);
    for (int i = 0; i < n * m; i++) {
        std::cin >> ch;
        if (ch == '1') {
            vec[i] = true;
        } else {
            vec[i] = false;
        }
    }
    // convert col to str and check which str has max times
    std::map<std::string, int> my_map;
    for (int i = 0; i < m; i++) {
        std::string str;
        for (int j = 0; j < n; j++) {
            if (vec[j * m + i]) {
                str.push_back('1');
            } else {
                str.push_back('0');
            }
        }
        if (my_map.count(str) == 0) {
            my_map[str] = 0;
        }
        my_map[str] += 1;
    }
    int max_v = 0;
    for (auto kv : my_map) {
        max_v = std::max(max_v, kv.second);
    }
    std::cout << max_v << std::endl;
}

// 参考牛客题解
//   核心思想  将每列视作字符串，因为是每行翻转，所以每列字符串相同的，无论如何翻转都是相同的(所有字符串中，第i个字符从1变0或从0变1)，因此只需要找到所有的列字符串中，哪种字符串出现的次数最多，那么将这列字符串翻转为全1时，对应的全1列就是最多的
