#include <iostream>
void test(std::istream &in, std::ostream &out) {
    size_t size = 0;
    in >> size;
    std::cout << size <<std::endl;
    int num = 0;
    BTree<int> t(size); // A B-Tree with minimum degree 2
    while (in >> num) {
        t.insert(num);
        std::cout << num <<std::endl;
    }
    t.BFS([&out](const int& key) {    out « key « " ";});
};
