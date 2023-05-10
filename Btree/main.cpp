#include <iostream>

#include <vector>
#include <queue>

#include <string>
#include <sstream>

template <class T>
class BTree {
 public:
    explicit BTree(size_t _t) : root(nullptr), t(_t) {}
    ~BTree() { delete root; }

    void Insert(const T& ket);
    void BFS(void (*visit)(const T& key)) const;
 private:
    struct Node {
        bool IsLeaf;
        std::vector<T> Keys;
        std::vector<Node*> Children;

        explicit Node(bool isLeaf) : IsLeaf (isLeaf) {}
        ~Node() { for (Node* child : Children) { delete child; } }
    };
    Node* root;
    size_t t;

    bool isNodeFull(Node* node) const { return node->Keys.size() == 2 * t - 1; }
    void insertNonFull(Node*, const T& key);
    void splitChild(Node* node, size_t pos);
};

template<class T>
void BTree<T>::BFS(void(*visit)(const T& key)) const {
    if (!root) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        size_t n = q.size();
        for (size_t i = 0; i < n; i++) {
            Node* node = q.front();
            q.pop();
            for (size_t j = 0; j < node->Keys.size(); j++) {
                visit(node->Keys[j]);
            }
            if (!node->IsLeaf) {
                for (size_t j = 0; j < node->Children.size(); j++) {
                    q.push(node->Children[j]);
                }
            }
        }
        std::cout << std::endl;
    }
}

template<class T>
void BTree<T>::Insert(const T& key) {
    if (root == nullptr) {
        root = new Node(true);
    }

    if (isNodeFull(root)) {
        Node* newRoot = new Node(false);
        newRoot->Children.push_back(root);
        root = newRoot;
        splitChild(root, 0);
    }

    insertNonFull(root, key);
}

template<class T>
void BTree<T>::insertNonFull(Node* node, const T& key) {
    size_t pos = node->Keys.size() - 1;

    // гарантированно не перепеполненный лист -- запишем новый ключ в него
    if (node->IsLeaf) {
        // расширили вектор ключей для вставки нового
        node->Keys.resize(node->Keys.size() + 1);
        while (pos >= 0 && key < node->Keys[pos]) {
            // обходим ключи справа налево, сдвигая вправо на 1
            node->Keys[pos + 1] = node->Keys[pos];
            pos--;
        }
        // вставляем новый ключ на освобожденное в цикле место
        node->Keys[pos + 1] = key;
    } else {
        // ищем позицию потомка, в которого добавим ключ
        while (pos >= 0 && key < node->Keys[pos]) {
            pos--;
        }

        // если потомок и так полон, надо его сначала разбить
        if (isNodeFull(node->Children[pos + 1])) {
            splitChild(node, pos + 1);
            // после разбиения потомка в текущий узел из него поднялся ключ
            // надо сравниться и с ним
            if (key > node->Keys[pos + 1])
                pos++;
        }
        insertNonFull(node->Children[pos + 1], key);
    }
}

template<class T>
void BTree<T>::splitChild(Node* node, size_t pos) {
    Node* fullChild = node->Children[pos];
    Node* newChild = new Node(fullChild->IsLeaf);

    for (size_t j = t; j < fullChild->Keys.size(); ++j) {
        newChild->Keys.push_back(fullChild->Keys[j]);
    }

    if (!fullChild->IsLeaf) {
        for (size_t j = t; j < fullChild->Children.size(); ++j) {
            newChild->Children.push_back(fullChild->Children[j]);
        }
    }

    for (size_t i = fullChild->Keys.size() - 1; i >= t; --i) {
        fullChild->Keys.erase(fullChild->Keys.begin() + i);
    }
    if (!fullChild->IsLeaf) {
        for (size_t i = fullChild->Children.size() - 1; i >= t; --i) {
            fullChild->Children.erase(fullChild->Children.begin() + i);
        }
    }

    node->Keys.insert(node->Keys.begin() + pos, fullChild->Keys.back());

    node->Children.insert(node->Children.begin() + pos + 1, newChild);

    fullChild->Keys.pop_back();
}

int main() {
    int t;
    std::cin >> t;
    std::string inputString;
    getline(std::cin, inputString);

    BTree<int> tree(t);
    getline(std::cin, inputString);
    std::stringstream ss(inputString);

    std::string token;
    while (getline(ss, token, ' ')) {
        int num = std::stoi(token);
        tree.Insert(num);
    }
    tree.BFS([](const int& key) { std::cout << key << " "; });
    return 0;
}
