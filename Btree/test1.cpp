template <typename Key>
class BTree
{
public:
    struct Node
    {
        Node(bool leaf)
        : leaf(leaf)
        {
        }
 
        ~Node()
        {
            for (Node* child: children)
            {
                delete child;
            }
        }
 
        bool leaf;
        std::vector<Key> keys;
        std::vector<Node*> children;
    };
 
    BTree(size_t min_degree)
    : root(nullptr), t(min_degree)
    {
        assert(min_degree >= 2);
    }
 
    ~BTree()
    {
        if (root)
            delete root;
    }
 
    void insert(const Key &key)
    {
        if (!root)
            root = new Node(true);
        
        if (is_node_full(root))
        {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            split(root, 0);
        }
 
        insert_non_full(root, key);
    }
 
    bool find(const Key &key)
    {
        return find_aux(root, key);
    }
 
private:
    bool is_node_full(Node *node)
    {
        return node->keys.size() == 2*t - 1;
    }
 
    bool find_aux(Node* node, const Key &key)
    {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
            i++;
 
        if (i < node->keys.size() && key == node->keys[i])
            return true;
        else if (node->leaf)
            return false;
        else
            return find_aux(node->children[i], key);
    }
 
    void split(Node *node, size_t index);
 
 
    void insert_non_full(Node *node, const Key &key)
    {
        int pos = node->keys.size() - 1;
        if (node->leaf)
        {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos])
            {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        }
        else
        {
            while (pos >= 0 && key < node->keys[pos])
            {
                pos--;
            }
 
            if (is_node_full(node->children[pos + 1]))
            {
                split(node, pos + 1);
                if (key > node->keys[pos + 1])
                {
                    pos++;
                }
            }
            insert_non_full(node->children[pos + 1], key);
        }
    }
 
    
    
 
    Node *root;
    size_t t; // minimum degree
  
};