/* 
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса. 
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
4.3 Планировщик процессов
В операционной системе Technux есть планировщик процессов. 
Каждый процесс характеризуется:
приоритетом P
временем, которое он уже отработал t
временем, которое необходимо для завершения работы процесса T 
Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и кладет обратно в очередь процессов.
Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
Требуется посчитать кол-во переключений процессора.

*/
#include <iostream>

struct Process {
    int P;
    int t;
    int T;
    Process() : P(0), t(0), T(0) {}
    Process(int P, int t, int T) : P(P), t(t), T(T) {}
};

template<class T>
class DefualtComparator {
 public:
    bool operator()(const T& value1, const T& value2) {return value1 < value2;}
};

template <class T, class Compare = DefualtComparator<T>>
class Heap {
 public:
    explicit Heap(Compare cmp = Compare) :
    cmp(cmp),
    buffer(nullptr),
    bufferSize(0)
    size(0) {}

    Heap(const T* arr, size_t size, Compare cmp);
    ~Heap();

    void Add(cont T&);
    const T& ExtractMin();
    const T& Peek() const {return buffer[0];}
    size_t Size() const {return size;}

 private:
    void BuildHeap();
    void SiftUp(int i);
    void SiftDown(int i);

    // расширение buffer
    void grow();

    Compare cmp;
    T* buffer;
    size_t bufferSize;
    size_t size;
};

template <class T, class Compare>
Heap<T, Compare>::Heap(const T* arr, size_t size, Compare cmp) :
    cmp(cmp),
    size(size),
    bufferSize(size),
    bufferSize(size) {
        arr = new T[bufferSize];
        BuildHeap(arr);
}

template <class T, class Compare>
Heap<T, Compare>::~Heap() {
    delete[] buffer;
}

template <class T, class Compare>
void Heap<T, Compare>::BuildHeap() {
    for (int i = size / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}


int main() {
    return 0;
}