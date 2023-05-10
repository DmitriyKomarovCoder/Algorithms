//  код взят из дз номер 2
#include <iostream>

#include <stack>
#include <queue>
#include <vector>

#include <string>
#include <sstream>

template <class T, class Compare>
class BinaryTree {
 public:
    BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();
    void deleteNode();
    void Add(const T& key);
    bool Has(const T& key) const;
    bool checkAllValuesEqual();
    void DfsInOrder(void (*visit)(const T& key)) const;
 private:
    struct Node  {
        Node* Left;
        Node* Right;
        T Key;
        Node(const T& key) : Left(nullptr), Right(nullptr), Key(key) {}
    };

    void BfsPastOrder(void(*visit)(Node& node));
    Node* root;
    Compare cmp;
};

template <class T, class Compare>
bool BinaryTree<T, Compare>::checkAllValuesEqual() {
    if (root == nullptr) {
        return true;
    }
    T value = root->Key;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node == nullptr) {
            continue;
        }
        if (cmp(node->Key, value) || cmp(value, node->Key)) {
            return false;
        }
        stack.push(node->Left);
        stack.push(node->Right);
    }
    return true;
}

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    deleteNode();
}

template<class T, class Compare>
void BinaryTree<T, Compare>::deleteNode() {
    if (root == nullptr) {
        return;
    }
    BfsPastOrder([](Node& node) {delete &node;});

}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }

    Node* node = root;
    Node* prevNode = nullptr;
    while (node != nullptr) {
        prevNode = node;
        if (cmp(key, node->Key)) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }
    if (cmp(key, prevNode->Key)) {
        prevNode->Left = new Node(key);
    } else {
        prevNode->Right = new Node(key);
    }
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T& key) const {
    Node* node = root;
    while (node != nullptr) {
        if (node->Key == key) {
            return true;
        } else if (cmp(key, node->Key)) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }
    return false;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::DfsInOrder(void(*visit)(const T& key)) const {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> nodeStack;
    Node* node = root;

    while (node != nullptr || !nodeStack.empty()) {
        while (node != nullptr) {
            nodeStack.push(node);
            node = node->Left;
        }
        node = nodeStack.top();
        nodeStack.pop();
        visit(node->Key);
        node = node->Right;
    }
}

template<class T, class Compare>
void BinaryTree<T,Compare>::BfsPastOrder(void(*visit)(Node& node)) {

    std::queue<Node*> nodeQueue;
    std::vector<Node*> vectorBfs;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front();
        nodeQueue.pop();

        vectorBfs.push_back(node);

        if(node->Left != nullptr) {
            nodeQueue.push(node->Left);
        }

        if(node->Right != nullptr) {
            nodeQueue.push(node->Right);
        }
    }

    for(Node* treeNode: vectorBfs) {
        visit(*treeNode);
    }
}



struct IntCmp {
    bool operator()(int l, int r) { return l < r;}
};

int main() {
    std::string inputString;
    getline(std::cin, inputString);

    std::stringstream ss(inputString);

    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    int num;
    while (ss >> num) {
        tree.Add(num);
    }
    if (tree.checkAllValuesEqual()) {
        std::cout << 1 << std::endl;
    } else { 
        std::cout << 0 << std::endl;
    }
    return 0;
}