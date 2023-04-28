#include <iostream>
#include <cassert>
#include <string>
#include <vector>

void run(std::istream&, std::ostream&);
void testSolution();

template<class T>
class gVector {
    private:
        T* data_;
        int size_;
        int capacity_;

        void grow() {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= 2;
            }

            T* new_arr = new T[capacity_];

            for (int i = 0; i < size_; ++i) {
                new_arr[i] = data_[i];
            }

            delete[] data_;
            data_ = new_arr;
        }
    public:
        gVector(): size_(0), capacity_(0), data_(nullptr) {}
        
        gVector(int size): size_(size), capacity_(size) {
            data_ = new T[size];
        }

        gVector(int size, const T& data): capacity_(size), size_(size) {
            data_ = new T[size];
            for (int i = 0; i < size_; ++i) {
                data_[i] = data;
            }
        }

        gVector(const gVector<T>& vector):
            data_(new T[vector.capacity_]),
            capacity_(vector.capacity_),
            size_(vector.size_) {
                for (int i = 0; i < size_; ++i) {
                    data_[i] = vector.data_[i];
                }
        }

        ~gVector() {
            delete[] data_;
        }

        gVector<T>& operator= (const gVector<T>& vector) {
            if (this != &vector) {
                delete[] this->data_;
                capacity_ = vector.capacity_;
                size_ = vector.size_;

                for (int i = 0; i < size_; ++i) {
                    data_[i] = vector.data_[i];
                }
            }
            return *this;
        }

        T& operator[] (int index) const {
            if (index < 0 && index > size_)
                throw std::out_of_range("index out of range");
            return data_[index];
        }



        bool empty() const {
            return size_ == 0;
        }

        int size() const {
            return size_;
        }

        int get_capacity() const {
            return capacity_;
        }

        void push_back(const T& el) {
            if (size_ == capacity_) {
                this->grow();
            }
            data_[size_++] = el;
        }

        void pop_back() {
            size_--;
        }

        T get_last() const {
            return data_[size_];
        }

        T get_first() const {
            return data_[0];
        }

        void clear() {
            size_ = 0;
        }

        void reserve(int capacity) {
            if (capacity > this->capacity_) {
                T* new_arr = new T[capacity];
                for (int i = 0; i < size_; ++i) {
                    new_arr[i] = data_[i];
                }
                delete[] data_;
                data_ = new_arr;
                capacity_ = capacity;
            }
        }

        void resize(int size) {
            if (size > size_) {
                this->reserve(size);
                for (int i = size_; i < size; ++i) {
                    data_ = T();
                }
                size_ = size;
            } else if (size_ > size) {
                size_ = size;
            }
        }

        void print() {
            if (size_ == 0) {
                std::cerr << "not initalisated vector" << std::endl;
                return;
            }

            std::cout << "[ ";
            for (int i = 0; i < size_ - 1; ++i) {
                std::cout << data_[i] << ", ";
            }
            std::cout << data_[size_ - 1] << " ]" << std::endl;
        }
};

struct element {
    int value;
    int value_id;
    int array_id;
};


class IsLessByValue {
    public:
    bool operator()(const element& l_el, const element& r_el) {
        return l_el.value < r_el.value;
    }
};

template<class T>
class IsLessDefaultCmp {
    public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template <class T, class Compare = IsLessDefaultCmp<T>>
class binHeap {
    public:
        binHeap(Compare cmp = IsLessDefaultCmp<T>()): cmp_(cmp) {}
        binHeap(T* arr, int size, Compare cmp = IsLessDefaultCmp<T>()) {
            data_.reserve(size);

            for (int i = 0; i < size; ++i) 
                this->insert(arr[i]);
            buildHeap();
        }

        void insert(const T& el) {
            data_.push_back(el);
            shiftUp(data_.size() - 1);
        }

        T extractMin() const{
            return data_.get_first();
        }

        const T& peek() const {
            return data_[0];
        }

        size_t size() const {
            return data_.size();
        }
    private:
        Compare cmp_;
        gVector<T> data_;

        void buildHeap() {
            for (int i = data_.size()/2 - 1; i >= 0; --i) {
                shiftDown(i);
            }
        }

        void shiftDown(size_t i) {
            size_t end = data_.size() - 1;
            size_t left = 2*i + 1;
            size_t right = 2*i + 2;
            size_t tmp_index = i; 
            
            while (left <= end) {
                size_t min = tmp_index;

                if (cmp_(data_[left], data_[tmp_index]))
                    min = left;
                if (right <= end && cmp_(data_[right], data_[min]))
                    min = right;
                
                if (min != tmp_index)
                    std::swap(data_[tmp_index], data_[min]);
                else
                    return;
                
                tmp_index = min;
                left = 2*tmp_index + 1;
                right = 2*tmp_index + 2;
            }
        }

        void shiftUp(size_t i) {
            while (i > 0) {
                size_t parent = (i - 1) / 2;
                
                if (cmp_(data_[i], data_[parent])) {
                    std::swap(data_[i], data_[parent]);
                    i = parent;
                } else {
                    return;
                }

            }
        }
};

template<class T>
gVector<T> mergeKArrays(const gVector<gVector<T>>& arr) {
    IsLessByValue comparator;
    binHeap<element, IsLessByValue> heap(comparator);
    gVector<T> output;

    int k = arr.size();
    gVector<int> curr_indices(k, 0);
    int n = arr[0].size();
    element curr_min = {0, 0, 0};

    output.reserve(k*n);

    for (int i = 0; i < k; ++i) {
        element curr_el = {arr[i][0], 0, i};
        heap.insert(curr_el);
    }

    while (heap.size() > 0) {
        curr_min = heap.extractMin();
        output.push_back(curr_min.value);

        int curr_id = curr_min.array_id;
        int next_id = curr_indices[curr_id] + 1;
        if (next_id >= n) {
            continue;
        }
        element next_el = {arr[curr_id][next_id], next_id, curr_id};
        heap.insert(next_el);
        curr_indices[curr_id] = next_id;
    }

    output.print();
    return output;
}

void run(std::istream& input, std::ostream& output) {
    int k, n;
    input >> k >> n;
    gVector<gVector<int>> arr(k, gVector<int>(n));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            int el;
            input >> el;
            arr[i][j] = el;
        }
    }

    mergeKArrays(arr);
}

int main() {
    //testSolution();
    run(std::cin, std::cout);
    return 0;
}