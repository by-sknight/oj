#include <bits/stdc++.h>
#include <iomanip>
#define MAX 50

int cache[MAX];

int f(int x) {
    if (cache[x] != -1) {
        return cache[x];
    }
    if (x == 0) {
        cache[x] = 1;
        return 1;
    }
    if (x == 1) {
        cache[x] = 1;
        return 1;
    }
    cache[x] = f(x - 2) + f(x - 1);
    return cache[x];
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i <= n; i++) {
        cache[i] = -1;
    }
    std::cout << f(n) << std::endl;
}
