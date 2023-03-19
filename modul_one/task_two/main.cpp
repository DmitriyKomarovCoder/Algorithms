/*
2_3. Даны два массива неповторяющихся целых чисел, 
упорядоченные по возрастанию. 
A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение.
Требования: Время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.. 
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. 
Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером 
порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/

#include <iostream>
#include <cassert>

int min(int num1, int num2) {
    if (num1 > num2) {
        return num2;
    }
    return num1;
}

int intersectionArrays(
    const int A[], int sizeA,
    const int B[], int sizeB,
    int sect[]
) {
    int k = 0;
    int previous = 0;
    for (int i = 0; i < sizeB; i++) {
        if (previous >= sizeA) {
            break;
        }
        // определение диапазона для поиска текущего элемента B
        int rangeSize = 1;
        while (previous + rangeSize < sizeA && A[previous + rangeSize] < B[i]) {
            rangeSize *= 2;
        }
        int first = previous;
        int last = min(previous + rangeSize, sizeA);
        // бинарный поиск элемента B в диапазоне
        while (first < last) {
            int mid = (first + last) / 2;
            if (A[mid] < B[i]) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        if (first < sizeA && A[first] == B[i]) {
            sect[k] = B[i];
            k++;
        }
        previous = first;  // запоминаем индекс последнего элемента
    }
    return k;
}


int main() {
    int n, m;

    std::cin >> n;
    std::cin >> m;

    assert(n > 0 && m > 0);
    const int sizeA = n;
    const int sizeB = m;

    int A[sizeA];
    int B[sizeB];
    // ввод данных
    for (int i = 0; i < sizeA; i++) {
        std::cin >> A[i];
    }

    for (int i = 0; i < sizeB; i++) {
        std::cin >> B[i];
    }

    int sect[sizeB];
    int k = intersectionArrays(A, sizeA, B, sizeB, sect);

    // вывод данных в консоль
    for (int i = 0; i < k; i++) {
        std::cout << sect[i] << " ";
    }
    return 0;
}
