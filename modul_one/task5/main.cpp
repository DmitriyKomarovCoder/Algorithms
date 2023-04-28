/*
Требование для всех вариантов Задачи 5
Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться вместе. 
Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. 
В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
*/
#include <iostream>
#include <assert.h>

struct Date {
    int day;
    int month;
    int year;
<<<<<<< HEAD

    // используется для подсчета современников, для
    // сортировки при равенстве всех остальных значений
    int isDead;

    Date() : day(0), month(0), year(0), isDead(-1) {}
    Date(int day, int month, int year, int isDead) :
    day(day), month(month), year(year) , isDead(isDead){}
};

void CopyDate(Date& dest, const Date& src) {
    dest.day = src.day;
    dest.month = src.month;
    dest.year = src.year;
    dest.isDead = src.isDead;
=======
    bool isBorn; // используется для подсчета современников
    Date() : day(0), month(0), year(0), isBorn(true) {}
    Date(int day, int month, int year, bool isBorn) : day(day), month(month), year(year) , isBorn(isBorn){}

};

void copyDate(Date& dest, const Date& src) {
    dest.day = src.day;
    dest.month = src.month;
    dest.year = src.year;
    dest.isBorn = src.isBorn;
>>>>>>> 307c1d7333d53ba460059980c1841393def724d6
}


class DateCmp {
 public:
    bool operator()(const Date& value1, const Date& value2) {
        if (value1.year != value2.year) {
            return value1.year < value2.year;
        }

        if (value1.month != value2.month) {
            return value1.month < value2.month;
        }
<<<<<<< HEAD
        if (value1.day != value2.day) {
            return value1.day < value2.day;
        }
        return value1.isDead < value2.isDead;
=======

        return value1.day < value2.day;
>>>>>>> 307c1d7333d53ba460059980c1841393def724d6
    }
};

template<class T>
class IsLessCmpDefault {
 public:
    bool operator()(const T& l, const T& r) {return l < r;}
};

template<class T, class Compare = IsLessCmpDefault<T>>
<<<<<<< HEAD
void Merge(
=======
void merge(
>>>>>>> 307c1d7333d53ba460059980c1841393def724d6
    T* arr, int left, int mid, int right,
    Compare cmp = IsLessCmpDefault<T>()
) {
    T* buffer = new T[right - left + 1];
    int i = left;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right) {
        if (cmp(arr[i], arr[j])) {
            buffer[k++] = arr[i++];
        } else {
            buffer[k++] = arr[j++];
<<<<<<< HEAD
        }
    }

    while (i <= mid) {
        buffer[k++] = arr[i++];
    }

    while (j <= right) {
        buffer[k++] = arr[j++];
    }

    for (int index = 0; index < k; index++) {
        arr[left + index] = buffer[index];
    }
 
    delete[] buffer;
}

template<class T, class Compare = IsLessCmpDefault<T>>
void MergeSort(T* arr, int size, Compare cmp = IsLessCmpDefault<T>()) {
    for (int i = 1; i < size; i *= 2) {
        for (int left = 0; left < size - i; left += 2 * i) {
            int mid = left + i - 1;
            int right = std::min(left + 2 * i - 1, size - 1);
            Merge(arr, left, mid, right, cmp);
=======
>>>>>>> 307c1d7333d53ba460059980c1841393def724d6
        }
    }

    while (i <= mid) {
        buffer[k++] = arr[i++];
    }

    while (j <= right) {
        buffer[k++] = arr[j++];
    }
    for (int index = 0; index < k; index++) {
        arr[left + index] = buffer[index];
    }
    delete[] buffer;
}

<<<<<<< HEAD
template<class Compare = DateCmp>
bool CheckArguments(Date& dateBorn, Date& dateDead, Compare cmp = DateCmp()) {
    Date date18 = Date(dateBorn.day, dateBorn.month,
    dateBorn.year + 18, 1);

    if (cmp(dateDead, date18)) {
        return false;
    }

    Date date80 = Date(dateBorn.day, dateBorn.month,
    dateBorn.year + 80, -1);

    if (cmp(date80, dateDead)) {
        CopyDate(dateDead, date80);
    }
    CopyDate(dateBorn, date18);
    return true;
}

int CountingContemporaries(Date* arr, int size) {
    int k = 0;
    int max = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].isDead == 1) {
            ++k;
            max = std::max(max, k);
        } else {
            --k;
=======
template<class T, class Compare = IsLessCmpDefault<T>>
void MergeSort(T* arr, int size, Compare cmp = IsLessCmpDefault<T>()) {
    for (int i = 1; i < size; i *= 2) {
        for (int left = 0; left < size - i; left += 2 * i) {
            int mid = left + i - 1;
            int right = std::min(left + 2 * i - 1, size - 1);
            merge(arr, left, mid, right, cmp);
>>>>>>> 307c1d7333d53ba460059980c1841393def724d6
        }
    }
    return max;
}

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    Date* array = new Date[n*2];
    int size = 0;

    for (int i = 0; i < n; ++i) {
        int bornDay, bornMonth, bornYear, deadDay, deadMonth, deadYear;

        std::cin >> bornDay >> bornMonth >> bornYear
        >> deadDay >> deadMonth >> deadYear;

        Date dateBorn(bornDay, bornMonth, bornYear, 1);
        Date dateDead(deadDay, deadMonth, deadYear, -1);
        if (CheckArguments(dateBorn, dateDead)) {
            array[size++] = dateBorn;
            array[size++] = dateDead;
        }
    }

    DateCmp Compare;
    MergeSort(array, size, Compare);

    std::cout<< CountingContemporaries(array, size);
    return 0;
}
template<class Compare = DateCmp>
bool CheckArguments(Date& dateBorn, Date& dateDead, Compare cmp = DateCmp()) {
    Date date18 = Date(dateBorn.day, dateBorn.month,
    dateBorn.year + 18, dateBorn.isBorn);

    // проверим на случай, когда сов. умер в день 18 летия
    if (date18.year == dateDead.year && date18.month == dateDead.month && date18.day == dateDead.day) {
        return false;
    }
    if (cmp(dateDead, date18)) {
        return false;
    }

    Date date80 = Date(dateBorn.day, dateBorn.month,
    dateBorn.year + 80, dateBorn.isBorn);

    if (cmp(date80, dateDead)) {
        copyDate(dateDead, date80);
    }
    copyDate(dateBorn, date18);
    return true;
}

int CountingContemporaries(Date* arr, int size) {
    int k = 0;
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].isBorn) {
            k++;
        } else {
            max = std::max(max, k);
            k = 0;
        }
    }
    if (max == 1) {
        return 0;
    }
    return max;
}

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    Date* array = new Date[n*2];
    int size = 0;

    for (int i = 0; i < n; i++) {
        int bornDay, bornMonth, bornYear, deadDay, deadMonth, deadYear;
        std::cin >> bornDay >> bornMonth >> bornYear
        >> deadDay >> deadMonth >> deadYear;
        Date dateBorn(bornDay, bornMonth, bornYear, true);
        Date dateDead(deadDay, deadMonth, deadYear, false);
        if (CheckArguments(dateBorn, dateDead)) {
            array[size++] = dateBorn;
            array[size++] = dateDead;
        }
    }

    DateCmp Compare;
    MergeSort(array, size, Compare);
    for (int i = 0; i < size; i++) {
        std::cout << array[i].day << ' ' << array[i].month << ' ' << array[i].year << " " << array[i].isBorn << std::endl;
    }
    
    std::cout<< CountingContemporaries(array, size);
    return 0;
}