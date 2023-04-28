/*7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. 
Количество чисел не больше 106. 
Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

int Partition(long long int* arr, int first, int last, int highestBit) {
    int i = first;
    int j = last;

    while (i <= j) {
        for (; i <= last && !((arr[i] >> highestBit) & 1); ++i) {}
        for (; j >= first && ((arr[j] >> highestBit) & 1); --j) {}
        if (i < j) {
            std::swap(arr[i++], arr[j--]);
        }
    }
    return i;
}

void BinaryQuickSort(long long int* arr, int first, int last, int highestBit) {
    if (first >= last) {
        return;
    }

    int part = Partition(arr, first, last, highestBit);
    BinaryQuickSort(arr, first, part - 1, highestBit - 1);
    BinaryQuickSort(arr, part, last, highestBit - 1);
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