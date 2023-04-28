#include <iostream>
#include <assert.h>
#include <string>

class Stack {
 public:
    explicit Stack(int size);

    ~Stack();

    void Push(char value);
    char Pop();

    void grow();

 private:
    char* buffer;
    int top;
    int bufferSize;
};

Stack::Stack(int size) :
    bufferSize(size),
    top(-1)
{
    buffer = new char[bufferSize];
}

Stack::~Stack() {
    delete[] buffer;
}

void Stack::Push(char value) {
    if (top + 1 > bufferSize) {
        grow();
    }
    buffer[++top] = value;
}

char Stack::Pop() {
    assert(top != -1);
    return buffer[top--];
}

void Stack::grow() {
    int newBufferSize = bufferSize * 2;
    char* newBuffer = new char[newBufferSize];
    for (int i = 0; i <= top; i++) {
        newBuffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

bool IsAnagrama(std::string value1, std::string value2) {
    if (value1.size() != value2.size()) {
        return false;
    }
    std::string value3;
    Stack One(value1.size());
    Stack Two(value1.size());
    for (int i = 0; i < value1.size(); i++) {
        One.Push(value1[i]);
    }

    for (int i = 0; i < value1.size(); i++) {
        Two.Push(One.Pop());
    }   

    for (int i = 0; i < value1.size(); i++) {
        value3[i] = Two.Pop();
        std::cout << value3[i];
    }
    if (value2 != value3) {
        return false;
    }

    return true;
}

int main() {
    std::string value1;
    std::string value2;
    std::cin >> value1 >> value2;
    std::cout << (IsAnagrama(value1, value2) ? "YES" : "NO");
    return 0;
}