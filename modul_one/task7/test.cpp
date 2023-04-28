/*7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. 
Количество чисел не больше 106. 
Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

int Partition(long long int* arr, int l, int r, int highestBit) {
    int i = l;
    int j = r;

    while (i <= j) {
        for (; i <= r && !((arr[i] >> highestBit) & 1); ++i) {}
        for (; j >= l && ((arr[j] >> highestBit) & 1); --j) {}
        if (i < j) {
            std::swap(arr[i++], arr[j--]);
        }
    }
    return i;
}

void BinaryQuickSort(long long int* arr, int l, int r, int highestBit) {
    if (l >= r) {
        return;
    }

    int part = Partition(arr, l, r, highestBit);
    BinaryQuickSort(arr, l, part - 1, highestBit - 1);
    BinaryQuickSort(arr, part, r, highestBit - 1);
}


int main() {
    int n;
    std::cin >> n;
    long long int* arr = new long long int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    int highestBit = sizeof(long long int) * 8 - 1;
    BinaryQuickSort(arr, 0, n - 1, highestBit);

    for (int i = 0; i < n; i ++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arr;
    return 0;
}