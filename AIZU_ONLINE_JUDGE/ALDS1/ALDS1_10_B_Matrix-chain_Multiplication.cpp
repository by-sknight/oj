#include <bits/stdc++.h>
#include <iomanip>

std::vector<std::pair<int, int>> vec;
std::map<std::pair<int, int>, int> cache;

int cost(int left, int right) {
    if (cache.count({left, right}) != 0) {
        return cache[{left, right}];
    }
    if (left == right) {
        cache[{left, right}] = 0;
        return 0;
    }
    int min_cost = INT_MAX;
    for (int mid = left; mid < right; mid++) {
        min_cost = std::min(min_cost, cost(left, mid) + cost(mid + 1, right) +
                                      vec[left].first * vec[mid].second * vec[right].second);
    }
    cache[{left, right}] = min_cost;
    return min_cost;
}

int main() {
    int n;
    std::cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i].first >> vec[i].second;
    }

    std::cout << cost(0, n - 1) << std::endl;
}

// 动态规划
//   前一个问题是斐波那契数列,f(n) = f(n-1) + f(n-2)
//   以前做过背包问题, cost(weight, index) 表示背包容量为weight的时候，前index个物品的最大价值，就可以写公式
//     cost(weight, index) = std::max(cost(weight, index - 1), cost(weight - w[i], index - 1)) 分别表示不要这个物品和要这个物品，取最大价值的
//   关于这个矩阵相乘的，也可以同样使用动态规划思想，如何将大规模的问题拆分成小规模的问题，是否拆分是有意义的，以及最小规模的问题如何处理
//     cost(left, right) 表示 left 到 right 的最小乘数，最小规模就是 left == right 的时候，是0
//     至于问题怎么拆分，以2个元素为例, left + 1 = right 的场景，可选的乘的位置只有 left 之后，只有一个
//       因此可以遍历乘的位置从 left -> right (不包含right)，然后是 cost(left, left) + row(left) * col(left) * col(right) + cost(left + 1, right)
//       找出最小的消耗 row(left) 是最左侧的行数， col(left)是指遍历乘的位置的列数，col(right)是最右侧的列数
//       左侧的 cost(left, left) 第一个left是最左侧，第二个left是遍历乘的位置，右侧的 cost(left + 1, right) left+1是遍历乘的位置+1，right是最右侧
//   见代码中 mid 范围 [left, right] 遍历
//       不同的mid对应的消耗是 cost(left, mid) + cost(mid + 1, right) + row[left] * col[mid] * col[right]
//   最后使用 map 来缓存，避免重复计算
