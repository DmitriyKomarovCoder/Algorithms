/*
Требование для всех вариантов Задачи 5
Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
Группа людей называется современниками если был такой момент, когда они могли собраться вместе. 
Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. 
В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.

*/
struct Point {
    int X;
    int Y;
    Point() : X(0), Y(0) {}
    Point(int x, int y) : X(x), Y(y) {}
};

// 1
bool operator < (const Point& l, const Point& r) {
    return l.X < r.X;
}

// 2
bool IsLessByX(const Point& l, const Point& r) {
    return l.X < r.X;
}

// 3
template<class T>
bool IsLessDefault(const T& l, const T& r) {
    return l < r;
}

// 4
class IsLessByX {
 public:
    bool operator()(const Point& l, const Point& r) {return l.X < r.X;}

};

// 5
template<class T>
class IsLessCmpDefault {
 public:
    bool operator()(const T& l, const T& r) {return l < r;}
};

bool IsLessByY(const Point& l, const Point& r) {
    return l.Y < r.Y;
}

// с помощью компоратора
template<class T, class Compare = IsLessCmpDefault<T>>
void MegaSort(T* arr, int l, int r, Compare cmp = IsLessCmpDefault<T>()) {
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r; ++j) {
            if (cmp(arr[j+1] < arr[j])) {
                std::swap(arr[j+1])
            }
        }
    }
}

// реализация указатель на функцию 
template<class T>
void MegaSort(T* arr, int l, int r, bool isLess(const T&, const T&) = IsLessDefault) {
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r; ++j) {
            if (isLess(arr[j+1] < arr[j])) {
                std::swap(arr[j+1])
            }
        }
    }
}
