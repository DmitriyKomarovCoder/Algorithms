/*
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
Требования: Очередь должна быть реализована в виде класса.
*/
#include <iostream>
#include <assert.h>

template <class T>
class Queue {
 public:
    explicit Queue(int size);
    ~Queue();

    Queue(Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool isEmpty() const {return head == tail;}

    void pushBack(T value);
    T popFront();

 private:
    T* buffer;
    int bufferSize;
    int head;
    int tail;

    void grow();
};

template<class T>
Queue<T>::Queue(int size):
    bufferSize(size),
    head(0),
    tail(0)
{
    buffer = new T[bufferSize];
}

template<class T>
Queue<T>::~Queue() {
    delete[] buffer;
}

template<class T>
void Queue<T>::pushBack(T value) {
    if ((tail + 1) % bufferSize == head) {
        grow();
    }
    assert((tail + 1) % bufferSize != head);
    buffer[tail] = value;
    tail = (tail + 1) % bufferSize;
}

template<class T>
T Queue<T>::popFront() {
    assert(!isEmpty());
    T value = buffer[head];
    head = (head + 1) % bufferSize;
    return value;
}

// дописать!!
template<class T>
void Queue<T>::grow() {
    int newBufferSize = bufferSize * 2;
    T* newBuffer = new T[newBufferSize];
    int k = 0;
    while (!isEmpty()) {
        newBuffer[k] = this->popFront();
        k++;
    }
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
    head = 0;
    tail = k;
}

int main() {
    Queue<int> queue(2);
    int n = 0;
    std::cin >> n;
    bool result = true;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int data = 0;
        std::cin >> command >> data;
        switch (command) {
            case 2:
                if (queue.isEmpty()) {
                    result = result && data == -1;
                } else {
                    result = result && queue.popFront() == data;
                }
            break;
            case 3:
                queue.pushBack(data);
            break;
        }
    }
    std::cout << (result ? "YES" : "NO");

    return 0;
}
