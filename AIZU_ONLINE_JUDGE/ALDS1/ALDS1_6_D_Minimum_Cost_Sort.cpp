#include <bits/stdc++.h>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) std::cin >> vec[i];
    std::vector<int> vec_sorted = vec;
    std::sort(vec_sorted.begin(), vec_sorted.end());

    int min_val = vec_sorted[0];
    std::vector<bool> checked(n, false);
    std::map<int, int> target_pos;
    for (int i = 0; i < vec_sorted.size(); i++) { // 需要先知道它应该在的位置，才能分析环
        target_pos[vec_sorted[i]] = i;
    }

    long long all_cost = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (checked[i]) {
            continue;
        }

        int now = i;
        int num = 0;
        long sum = 0;
        int min_circle = vec[i];
        while (true) {
            checked[now] = true;
            num += 1;
            sum += vec[now];
            min_circle = std::min(vec[now], min_circle);
            now = target_pos[vec[now]];
            if (checked[now]) {
                break;
            }
        }
        all_cost += std::min(sum + (num - 2) * min_circle, sum + min_circle + (num + 1) * min_val); // 决定是否引入最小元素
    }
    std::cout << all_cost << std::endl;
}

// 最小花费排序  首先确认对应的环，哪些元素是相互联系，在环中，就可以使用最小的元素，来充当交换介质
//     此时的花费是 Sum(环)+(n-2)*min(环) n-2计算说明: n个元素需要(n-1)次交换，其他元素都使用一次
//     而min(环)使用了n-1次，但是Sum(环)中已经有了一次计算了，所以外面的倍数就是(n-2)
//     如果环中最小元素也很大，而整体外面有一个很小的值(m)，此时可以考虑将其借用，通过和min(环)交换的方式
//     这个引入操作增加的花费是 2*(min(环)+m) ，减少的花费是 (n-1)*(min(环)-m)
//     和原有花费整理下就是 Sum(环)+min(环)+(n+1)m
//     因此每个发现的环，比较下是否引入最小元素，从而确认最小消耗，最终计算出总的最小消耗
