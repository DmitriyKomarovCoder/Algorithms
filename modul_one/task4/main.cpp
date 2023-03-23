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
#include <assert.h>

struct Process {
    int P;
    int t;
    int T;
    Process() : P(0), t(0), T(0) {}
    Process(int P, int t, int T) : P(P), t(t), T(T) {}
};

template<class T>
class IsProcessFirst {
 public:
    bool operator()(const Process& value1, const Process& value2) {
        return value1.P * (value1.t + 1) < value2.P * (value2.t + 1);
    }
};

template<class T>
class DefaultComparator {
 public:
    bool operator()(const T& value1, const T& value2) {return value1 < value2;}
};

template <class T, class Compare = DefaultComparator<T>>
class Heap {
 public:
    explicit Heap(Compare cmp = DefaultComparator<T>()) :
    cmp(cmp),
    bufferSize(2),
    size_(0) {buffer = new T[bufferSize];}

    Heap(const T* arr, size_t size, Compare cmp = DefaultComparator<T>());
    ~Heap();

    void Add(const T & element);
    const T& ExtractMin();
    const T& Peek() const {return buffer[0];}
    size_t Size() const {return size_;}

 private:
    void SiftUp(int index);
    void SiftDown(int index);
    void BuildHeap();
    // расширение buffer
    void grow();

    Compare cmp;
    T* buffer;
    size_t bufferSize;
    size_t size_;
};

template <class T, class Compare>
Heap<T, Compare>::Heap(const T* arr, size_t size, Compare cmp) :
    cmp(cmp),
    size_(size),
    bufferSize(size) {
        assert(size > 0);
        buffer = new T[bufferSize];
        for (int i = 0; i < size; i++) {
            buffer[i] = arr[i];
        }
        BuildHeap(buffer);
}

template <class T, class Compare>
Heap<T, Compare>::~Heap() {
    delete[] buffer;
}

template <class T, class Compare>
void Heap<T, Compare>::SiftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (cmp(buffer[parent], buffer[index]))
            return;
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template <class T, class Compare>
void Heap<T, Compare>::SiftDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int smaller = index;
    if (left < size_ && cmp(buffer[left], buffer[index]))
        smaller = left;
    if (right < size_ && cmp(buffer[right], buffer[smaller]))
        smaller = right;
    if (smaller != index) {
        std::swap(buffer[index], buffer[smaller]);
        SiftDown(smaller);
    }
}

template <class T, class Compare>
void Heap<T, Compare>::BuildHeap() {
    for (size_t i = size_ / 2 - 1; i >= 0; --i) {
        SiftDown(i);
    }
}

template <class T, class Compare>
void Heap<T, Compare>::Add(const T& element) {
    if (size_ == bufferSize) {
        grow();
    }
    assert(size_ < bufferSize && buffer != 0);
    size_++;
    buffer[size_] = element;
    SiftUp(size_);
}

template <class T, class Compare>
void Heap<T, Compare>::grow() {
    size_t newBufferSize = bufferSize * 2;
    T* newBuffer = new T[newBufferSize];
    for (int i = 0; i < size_; i++) {
        newBuffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template <class T, class Compare>
const T& Heap<T, Compare>::ExtractMin() {
    assert(bufferSize != 0);
    int result = buffer[0];

    buffer[0] = buffer[size_];
    size_--;

    if (size_ > 0) {
        SiftDown(0);
    }
    return result;
}
int main() {
    
    return 0;
}