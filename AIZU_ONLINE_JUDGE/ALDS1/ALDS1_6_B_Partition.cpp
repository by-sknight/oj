#include <bits/stdc++.h>
#include <iomanip>

int partition(std::vector<int>& vec, int left, int right) {
    int d = vec[right - 1];
    int pos = left;
    for(int i = left; i < right - 1; i++) {
        if (vec[i] <= d) {
            std::swap(vec[pos], vec[i]);
            pos++;
        }
    }
    std::swap(vec[pos], vec[right - 1]);
    return pos;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) std::cin >> vec[i];
    int pos = partition(vec, 0, vec.size());
    for (int i = 0; i < vec.size(); i++) {
        if (i != 0) {
            std::cout << " ";
        }
        if (i == pos) {
            std::cout << "[" << vec[i] << "]";
        } else {
            std::cout << vec[i];
        }
    }
    std::cout << std::endl;
}
