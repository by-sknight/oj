#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    std::vector<int> vec;
    std::cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }

    std::vector<int> left(n, 0); // 左侧最长严格递增长度(不含自己)
    std::vector<int> right(n, 0); // 右侧最长严格递减长度(不含自己)
    for (int i = 0; i < n; i++) {
        int len = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (vec[j] < vec[i]) {
                len = std::max(len, left[j] + 1);
            }
        }
        left[i] = len;
    }
    for (int i = n - 1; i >= 0; i--) {
        int len = 0;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[i]) {
                len = std::max(len, right[j] + 1);
            }
        }
        right[i] = len;
    }
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        if (left[i] + right[i] + 1 > max_len) {
            max_len = left[i] + right[i] + 1;
        }
    }
    std::cout << n - max_len << std::endl;
}

// 输入n个高度，最小取出多少个，可以满足左侧严格递增，右侧严格递减(位置不限)
//   关于中间位置的选取是一个核心，如果选取i作为中间，那么前半部分最多有多少严格递增元素，后半部分最多有多少严格递减元素
//   设 left[i] 表示，i左侧有多少个严格递增的元素 right[i] 表示i右侧有多少个严格递减元素，那么只要统计所有left[i]+right[i]就能找到谁是最大的，然后最终结果就是n-(left[i]+right[i]+1)次取出
//   left[i]的计算，如果左侧存在某个元素小于i位置的元素，那么将i放在后面一定是单调递增的，但是不同的位置，可能带来的结果不同，因此对于所有前面的数据都需要遍历下
//       left[i] = max(left[x])  // x是左侧小于i元素值的元素的下标，所有的都要比较下，找出最大的
//   right[i]的计算同理，从右侧向左侧计算
