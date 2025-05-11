#include <bits/stdc++.h>
#include <iomanip>

// input must be sorted
void build_my_heap(std::vector<int>& vec) {
    for (int i = 1; i < vec.size(); i++) {
        int now = i;
        std::swap(vec[now], vec[0]);
        int parent = (now - 1) / 2;
        while (vec[parent] < vec[now]) {
            std::swap(vec[parent], vec[now]);
            now = parent;
            parent = (now - 1) / 2;
        }
        if (i != vec.size() - 1) {
            now = i;
            parent = (now - 1) / 2;
            while (vec[parent] > vec[now]) {
                std::swap(vec[parent], vec[now]);
                now = parent;
                parent = (now - 1) / 2;
                if (now == 0) {
                    break;
                }
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) std::cin >> vec[i];
    std::sort(vec.begin(), vec.end());
    build_my_heap(vec);
    for (int i = 0; i < vec.size(); i++) {
        if (i != 0) {
            std::cout << " ";
        }
        std::cout << vec[i];
    }
    std::cout << std::endl;
}

// 目标是求出某种满足堆的性质的序列，同时又使其进行堆排序的时候，交换次数最多
// 假设输入的已经是满足堆性质的序列了
// 正向的流程是: 首元素和队尾元素交换，有效区域长度减少，此时需要重新使其满足堆的性质，需要交换元素，如果每次这个过程中交换的次数都是当前最大(堆深度)，那么总的也就是最大了
// 尝试去逆向思考: 当前L->R是一个堆，下一个元素R+1比堆顶元素更大，也就是说此时的状态，对应的是正向流程中，交换完成后，重新使其满足堆性质后的阶段，前一个流程是将一个很小的值交换下去。
//   也就是说，如果我此时能够将一个很小的值交换到顶部，就对应首尾元素交换的阶段，此时我这个地方交换的次数，也就是正向中，使其满足堆性质的交换次数
//   此时，我直接选择最后面的元素，将其交换到顶部，这样就能确保交换次数尽量最大。
