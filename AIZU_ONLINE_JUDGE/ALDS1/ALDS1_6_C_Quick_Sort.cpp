#include <bits/stdc++.h>
#include <iomanip>

struct Card {
    char suit = ' ';
    int value = 0;
    int input_order = 0;
};

int partition(std::vector<Card>& vec, int left, int right) {
    Card dc = vec[right - 1];
    int pos = left;
    for(int i = left; i < right - 1; i++) {
        if (vec[i].value <= dc.value) {
            std::swap(vec[pos], vec[i]);
            pos++;
        }
    }
    std::swap(vec[pos], vec[right - 1]);
    return pos;
}

void quick_sort(std::vector<Card>& vec, int left, int right) {
    if (left < right - 1) {
        int pos = partition(vec, left, right);
        quick_sort(vec, left, pos);
        quick_sort(vec, pos + 1, right);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Card> vec(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i].suit >> vec[i].value;
        vec[i].input_order = i;
    }
    quick_sort(vec, 0, n);
    bool stable = true;
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i].value == vec[i + 1].value) {
            if (vec[i].input_order > vec[i + 1].input_order) {
                stable = false;
                break;
            }
        }
    }
    std::cout << (stable ? "Stable" : "Not stable") << std::endl;
    for (auto card : vec) {
        std::cout << card.suit << " " << card.value << std::endl;
    }
}
