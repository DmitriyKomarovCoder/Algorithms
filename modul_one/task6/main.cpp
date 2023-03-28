/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(n). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. 
Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. 
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>
#include <assert.h>

template<class T>
class CmpDefault {
 public:
    bool operator()(const T& l, const T& r) {return l > r;}
};

template<class T, class Compare = CmpDefault<T>>
int Partition(int* arr, int l, int r, Compare cmp = CmpDefault<T>()) {
    // выбор случайного pivot
    int pivot_index = rand() % (r - l) + l;
    std::swap(arr[pivot_index], arr[l]);
    T pivot = arr[l];

    int j = r;
    int i = j;

    while (j > l + 1) {
        if (cmp(arr[j - 1], pivot)) {
            std::swap(arr[i-1], arr[j-1]);
            --i;
        }
        --j;
    }

    std::swap(arr[l], arr[i-1]);
    return i-1;
}

template<class T, class Compare = CmpDefault<T>>
void FindKStat(T* arr, int size, int k, Compare cmp = CmpDefault<T>()) {
    assert(size > 0);
    int l = 0;
    int r = size;
    while (l < r) {
        int m = Partition<T>(arr, l, r, cmp);
        if (m == k) {
            return;
        } else if (m < k) {
            l = m + 1;
        } else {
            r = m;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    // 10%  перцентиль
    int k = n * 0.1;
    FindKStat(arr, n, k);
    std::cout << arr[k] << std::endl;

    // медиана
    k = n * 0.5;
    FindKStat(arr, n, k);
    std::cout << arr[k] << std::endl;

    // 90%  перцентиль
    k = n * 0.9;
    FindKStat(arr, n, k);
    std::cout << arr[k] << std::endl;

    delete[] arr;
    return 0;
}