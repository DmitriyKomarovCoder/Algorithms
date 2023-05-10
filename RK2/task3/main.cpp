#include <iostream>
#include <string>
#include <unordered_set>

struct Node {
    std::string product_name;
    int color;
    int size;
};

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            size_t h1 = std::hash<std::string>{}(node.product_name);
            size_t h2 = std::hash<int>{}(node.color);
            size_t h3 = std::hash<int>{}(node.size);
            return h1 + h2 + h3;
        }
    };
}


bool operator==(const Node& object1, const Node& object2) {
    return object1.product_name == object2.product_name &&
        object1.color == object2.color && object1.size == object2.size;
}

int main() {
    std::unordered_set<Node> products;

    char operation;
    std::string product_name;
    int color, size;

    while (std::cin >> operation >> product_name >> color >> size) {
        Node product = { product_name, color, size };
        if (operation == '+') {
            if (products.insert(product).second) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        } else if (operation == '-') {
            if (products.erase(product)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        } else if (operation == '?') {
            if (products.count(product)) {
                std::cout << "OK"<< std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        }
    }

    return 0;
}