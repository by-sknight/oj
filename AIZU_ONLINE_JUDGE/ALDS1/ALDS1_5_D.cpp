#include <bits/stdc++.h>
#include <iomanip>

void merge(std::vector<int>& vec, int left, int mid, int right, long long& cnt) {
    std::vector<int> lv, rv;
    for (int i = left; i < mid; i++) lv.push_back(vec[i]);
    for (int i = mid; i < right; i++) rv.push_back(vec[i]);
    int li = 0, ri = 0, oi = left;
    while (li != lv.size() && ri != rv.size()) {
        if (lv[li] <= rv[ri]) {
            vec[oi] = lv[li];
            oi++;
            li++;
        } else {
            cnt += lv.size() - li;
            vec[oi] = rv[ri];
            oi++;
            ri++;
        }
    }
    while (li != lv.size()) {
        vec[oi] = lv[li];
        oi++;
        li++;
    }
    while (ri != rv.size()) {
        vec[oi] = rv[ri];
        oi++;
        ri++;
    }
}

void merge_sort(std::vector<int>&vec, int left, int right, long long& cnt) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        merge_sort(vec, left, mid, cnt);
        merge_sort(vec, mid, right, cnt);
        merge(vec, left, mid, right, cnt);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec;
    vec.resize(n);
    for (int i = 0; i < vec.size(); i++) {
        std::cin >> vec[i];
    }

    long long cnt = 0;
    merge_sort(vec, 0, vec.size(), cnt);
    std::cout << cnt << std::endl;
}

// 逆序的元素数量
// 目标是计算所有的"当前元素大于后面多少个元素"的和，冒泡排序就是一种方式，每交换一次就证明当前元素大于后面的元素一次，统计交换次数就行，不过当前题目会导致超时
// 题解中给出了答案，可以借用归并排序的思想，效率会高于冒泡排序
// 归并排序是将列表拆分为前后，分别进行排序，然后合并
// 当前元素大于后面多少个元素，也可以理解为，对于当前元素，前面有多少个大于自己的元素
// 因此在合并的阶段中，如果左侧列表当前位置元素大于右侧列表当前位置元素，就意味着右侧列表当前位置元素先进入合并后的列表中，左侧列表中剩余的元素都是大于右侧当前位置元素的(因为左侧已经有序)
//   也就是说，右侧当前位置元素前面有x个大于自己的元素，统计数加上x，继续处理
// 一直处理下去，就能统计出所有逆序元素数量
// 建议阅读 《挑战程序设计竞赛2》 7.6节来进一步理解
