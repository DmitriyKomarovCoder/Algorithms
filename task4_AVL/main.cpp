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

        ~Node() {
            delete left;
            delete right;
        }
    };

 public:
    explicit AVLTree(Comparator comp = Comparator()) :
                     root(nullptr),
                     tree_size(0),
                     comp(comp) {}

    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator =(const AVLTree&) = delete;
    AVLTree& operator =(AVLTree&&) = delete;

    ~AVLTree() {
        delete root;
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
        return _kStat(root, pos)->key;
    }

 private:
    Node* _kStat(Node* node, const int pos) {
        if (!node) {
            return nullptr;
        }
        int comp_res = comp(pos, node_count(node->left));
        if (comp_res == -1) {
            return _kStat(node->left, pos);
        } else if (comp_res == 1) {
            return _kStat(node->right, pos- comp_res - 1 );  // ?
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
        }
        return node;
    }

    Node* _insert(Node* node, const Key& key, const Value& value) {
        if (!node) {
            tree_size++;
            return new Node(key, value);
        }

        int comp_res  = comp(key, node->key);
        if (comp_res == -1) {
            node->left = _insert(node->left, key, value);
        } else {
            node->right = _insert(node->right, key, value);
        }
        return balance(node);
    }

    Node* _erase( Node* node, const Key& key )
    {
        if ( !node )
        {
            return nullptr;
        }
        
        int comp_res = comp(key, node->key);
        if (comp_res == -1)
        {
            node->left = _erase(node->left, key);
        }
        else if (comp_res == 1)
        {
            node->right = _erase(node->right, key);
        }
        else
        {
            Node* left = node->left;
            Node* right = node->right;
            delete node;

            if (!right) {
                return left;
            }

            Node* min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;
            
            return balance(min_node);
        }
        return balance( node );
    }

    Node* find_min(Node* node) {
        if ( !node->left ) {
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

    uint8_t height(Node* node) const {
        return node ? node->height : 0;
    }

    void fixheight(Node* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    int bfactor(Node* node) const {
        return height(node->right) - height(node->left);
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
    size_t tree_size;
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
            tree.kStat(k);
            std::cout << tree.kStat(k) << std::endl;
        }
    }
    return 0;
}

