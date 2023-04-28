#include <iostream>

int FindPoint(const int* arr, int count, int value) {
    int l = 0;
    int r = count;
    while (l < r) {
        int mid = (l + r) / 2;
        if (arr[mid] < value)
            l = mid + 1;
        else
    r = mid;
    }
    return l;
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    int value;
    std::cin >> value;

    std::cout << FindPoint(arr, n, value);

    delete[] arr;
    return 0;
}