#include <iostream>
#include <string>

#include <vector>
#include <queue>
#include <unordered_map>

#include "Test.hpp"


class Haffman {
 public:

    Haffman() : root(nullptr), table() {}
    ~Haffman() {
        deleteTree(root);
    }

    std::vector<bool> getCode(byte symbol) const {
        return table.at(symbol);
    }

    void encode(byte symbol, BitWriter& bitWriter) const {
        std::vector<bool> code = getCode(symbol);
        for (bool bit : code) {
            bitWriter.WriteBit(bit);
        }
    }

    void Serialize(BitWriter& writer) {
        _Serialize(root, writer);
    }

    void encodeTree(IOutputStream& compressed) {
        _encodeTree(root, compressed);
    }

    void buildTree(std::unordered_map<byte, int> Table) {
        std::priority_queue<Node*, std::vector<Node*>, comp> pq;
        for (const auto& pair : Table) {
            if (pair.second > 0) {
                Node* node = new Node (pair.first, pair.second);
                pq.push(node);
            }
        }
        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();

            Node* parent = new Node(0, left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }
        root = pq.top();
    }

    void buildTable(std::vector<bool> code) {
        _buildTable(root, code);
    }

 private:
    struct Node {
        byte ch;
        int freq;
        Node* left;
        Node* right;
        Node(char ch_, int freq_) : ch(ch_), freq(freq_) {}
    };

    struct comp {
        bool operator()(Node* l, Node* r) {
            return l->freq > r->freq;
        }
    };
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void _encodeTree(Node* node, IOutputStream& compressed) {
        if (node->left == nullptr && node->right == nullptr) {
            compressed.Write(true);
            compressed.Write(node->ch);
            return;
        }
        compressed.Write(false);
        _encodeTree(node->left, compressed);
        _encodeTree(node->right, compressed);
    }

    void _buildTable(Node* node, std::vector<bool>& code) {
        if (node->left == nullptr && node->right == nullptr) {
            table[node->ch] = code;
            return;
        }
        if (node->left != nullptr) {
            code.push_back(false);
            _buildTable(node->left, code);
            code.pop_back();
        }
        if (node->right != nullptr) {
            code.push_back(true);
            _buildTable(node->right, code);
            code.pop_back();
        }
    }

    void _Serialize(Node* node, BitWriter& writer) {
        if (!node) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            writer.WriteBit(1);
            writer.WriteBit(node->freq);
        } else {
            writer.WriteBit(0);
            _Serialize(node->left, writer);
            _Serialize(node->right, writer);
        }
    }

    Node* root = nullptr;
    std::unordered_map<byte, std::vector<bool>> table;
};
