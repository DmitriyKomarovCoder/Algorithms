#include <iostream>
#include <vector>
template <class T>
struct DefaultComparator {
    int operator()(const T& l, const T& r) const {
        if ( l < r ) return -1;
        if ( l > r ) return 1;
        return 0;
    }
};

template <class Key, class Value, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Key key;
        Value value;

        uint8_t height;
        int count;

        Node* left;
        Node* right;

        Node(const Key& key, const Value& value) :
            key(key),
            value(value),
            height(1),
            count(1),
            left(nullptr),
            right(nullptr) {}
    };

 public:
    explicit AVLTree(Comparator comp = Comparator()) :
                     root(nullptr),
                     comp(comp) {}

    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator =(const AVLTree&) = delete;
    AVLTree& operator =(AVLTree&&) = delete;

    ~AVLTree() {
        removeAVL(root);
    }

    Value* find(const Key& key) {
        return _find(root, key);
    }

    const Value* find(const Key& key) const {
        return find(key);
    }

    void insert(const Key& key, const Value& value) {
        root = _insert(root, key, value);
    }

    void erase(const Key& key) {
        root = _erase(root, key);
    }
    Value kStat(const int pos) {
        return _kStat(root, pos)->value;
    }

 private:
    void removeAVL(Node* node) {
        if (!node) {
            return;
        }
        removeAVL(node->left);
        removeAVL(node->right);
        
        delete node;
    }

    Node* _kStat(Node* node, const int pos) {
        if (!node) {
            return nullptr;
        }
        int node_left_count = node_count(node->left);
        if (pos < node_left_count) {
            return _kStat(node->left, pos);
        } else if (pos > node_left_count) {
            return _kStat(node->right, pos - node_left_count - 1);
        } else {
            return node;
        }
    }

    int node_count(Node* node) {
        if (node != nullptr) {
            return node->count;
        } else {
            return 0;
        }
    }

    void node_fix_count(Node* node) {
        int count_left = node_count(node->left);
        int count_right = node_count(node->right);

        node->count = count_left + count_right + 1;
    }

    Value* _find(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }
    
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) {
            return _find(node->left, key);
        } else if (comp_res == 1) {
            return _find(node->right, key);
        } else {
            return node; 
        }
    }

    Node* _insert(Node* node, const Key& key, const Value& value) {
        if (!node) {
            return new Node(key, value);
        }

        int comp_res  = comp(key, node->key);
        if (comp_res == -1) {
            node->left = _insert(node->left, key, value);
        } else if (comp_res == 1) {
            node->right = _insert(node->right, key, value);
        }
        return balance(node);
    }

    Node* _erase( Node* node, const Key& key ) {
        if (!node) {
            return nullptr;
        }

        int comp_res = comp(key, node->key);
        if (comp_res == -1) {
            node->left = _erase(node->left, key);
        }
        else if (comp_res == 1) {
            node->right = _erase(node->right, key);
        }
        else {
            Node* node_left = node->left;
            Node* node_right = node->right;
            delete node;

            if (!node_right) {
                return node_left;
            }

            Node* node_min = node_right;
            std::vector<Node*> node_stack;
            node_stack.push_back(node_right);

            while(node_min->left != nullptr) {
                node_min = node_min->left;
                node_stack.push_back(node_min);
            }
            node_stack.pop_back();

            Node* balanced = node_min->right;
            while(!node_stack.empty()) {
                node_stack.back()->left = balanced;
                balanced = balance(node_stack.back());
                node_stack.pop_back();
            }
            node_min->right = balanced;

            node_min->left = node_left;

            return balance(node_min);
        }
        return balance( node );
    }

    Node* find_min(Node* node) {
        if (!node->left) {
            return node;
        }
        return find_min(node->left);
    }

    Node* remove_min(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = remove_min(node->left);
        return balance(node);
    }

    uint8_t node_height(Node* node) const {
        
        return node ? node->height : 0;
    }

    void fixheight(Node* node) {
        node->height = std::max(node_height(node->left), node_height(node->right)) + 1;
    }

    int bfactor(Node* node) const {
        return node_height(node->right) - node_height(node->left);
    }

    Node* rotateleft(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        node_fix_count(q);
        fixheight(p);
        node_fix_count(p);
        return p;
    }

    Node* rotateright(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        node_fix_count(p);
        fixheight(q);
        node_fix_count(q);
        return q;
    }

    Node* balance(Node* node) {
        fixheight(node);
        node_fix_count(node);
        int bf = bfactor(node);

        if (bf == 2) {
            if (bfactor(node->right) < 0) {
                node->right = rotateright(node->right);
            }
            return rotateleft(node);
        } else if (bf == -2) {
            if (bfactor(node->left) > 0) {
                node->left = rotateleft(node->left);
            }
            return rotateright(node);
        }
        return node;
    }

    Node* root;
    Comparator comp;
};

int main() {
    size_t n;
    std::cin >> n;
    AVLTree<int, int, DefaultComparator<int>> tree;
    int num;
    int k;
    for (int i = 0; i < n; i++) {
        std::cin >> num >> k;
        if (num >= 0) {
            tree.insert(num, num);
            std::cout << tree.kStat(k) << std::endl;
        } else {
            tree.erase(std::abs(num));
            std::cout << tree.kStat(k) << std::endl;
        }
    }   
    return 0;
}

