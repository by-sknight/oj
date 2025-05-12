#include <bits/stdc++.h>
#include <iomanip>
#define MAX 1002
int _cache[MAX][MAX];

// str1 [0, p1) and str2 [0, p2) longest common subsequence
int lcs(std::string &str1, std::string &str2, int p1, int p2) {
    if (_cache[p1][p2] != -1) {
        return _cache[p1][p2];
    }
    if (p1 == 0 || p2 == 0) {
        _cache[p1][p2] = 0;
        return 0;
    }
    int ret = 0;
    if (str1[p1 - 1] == str2[p2 - 1]) {
        ret = lcs(str1, str2, p1 - 1, p2 - 1) + 1;
    } else {
        ret = std::max(lcs(str1, str2, p1 - 1, p2), lcs(str1, str2, p1, p2 - 1));
    }
    _cache[p1][p2] = ret;
    return ret;
}

int main() {
    int q;
    std::cin >> q;
    std::string clear;
    std::getline(std::cin, clear);
    for (int i = 0; i < q; i++) {
        std::string str1, str2;
        std::getline(std::cin, str1);
        std::getline(std::cin, str2);
        for (int i = 0; i <= str1.length(); i++) {
            for (int j = 0; j <= str2.length(); j++) {
                _cache[i][j] = -1;
            }
        }
        std::cout << lcs(str1, str2, str1.length(), str2.length()) << std::endl;
    }
}

// 最开始实现的时候，使用的是 std::map<std::pair<int, int>, int> cache; 作为缓存参数传入进去，从而减少每次计算，但是这个map本身也是很消耗资源的，不如数组的下标访问快捷，因此超时，调整为固定大小数组后，通过
// 同样是动态规划的题目，还是减少问题规模和最小规模时的处理
// 需要的是X和Y的最长子序列，如何分解问题规模和处理最小问题
//   最开始想的是，我是否将X的规模减少，当前处理的是X[i]，X[i]位置的元素最后一次出现在Y中，是在什么位置？但是Y中这个元素是否已经用于构建最长子串，假设位置是j，X[i]与Y[j-1]之前的结果加上1应该就是X[i]与Y的结果
//     但是这样的话，我需要检查出现位置，以及没有时处理逻辑，感觉思路是不对的
//   重新梳理一下，感觉可以将i,j(分别表示X前i个字符和Y前j个字符)作为参数，最小规模很好确认，如果i为0，任意j，最终结果都是0，j为0，任意i，最终结果都是0，先表示为lcs(i,j)
//     下一个最小的问题，lcs(1,1)的值呢，如果X[0]和Y[0]相同，那么就是lcs(0,0)+1，如果不相同呢，那就还是0，但是这个0如何得到？这个例子不是很明显
//     那就继续扩大 lcs(2,2)的值呢，如果X[1]和Y[1]相同，那么就是lcs(1,1)+1，如果不相同，但是X[1]与Y[0]相同，且X[0]不用Y[0]相同呢，或者X[0]与Y[1]相同，且X[0]不用Y[0]相同，对应的不就是 lcs(2,1) 和 lcs(1,2)
//     再捋捋概念，X当前元素和Y当前元素，相同时，就是lcs(i-1,j-1)+1，不相同时，X当前元素可能被Y的更小范围使用或者Y当前元素被X的更小范围使用，那就取最大值 max(lcs(i-1,j), lcs(i,j-1))
//   整理最终结果
//     lcs(i,j) 表示 X 前 i 个字符和 Y 前 j 个字符的最大子串长度
//       lcs(0,...)=0 lcs(..., 0)=0
//       lcs(i,j) = lcs(i-1,j-1) + 1 当 X 第 i 个字符与 Y 第 j 个字符相同时
//       lcs(i,j) = max(lcs(i-1,j),lcs(i,j-1)) 当 X 第 i 个字符与 Y 第 j 个字符不同时
