

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

class BinaryTree {
private:
    struct Node {
        int data;
        Node* left, *right;
        Node(int data) {
            this->data = data;
            left = right = nullptr;
        }
    };

    Node* root;

    bool checkSameValue(Node* root, int value) {
        if (root == nullptr)
            return true;
        if (root->data != value)
            return false;
        return checkSameValue(root->left, value) && checkSameValue(root->right, value);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
        }
        else {
            Node* curr = root;
            while (true) {
                if (value < curr->data) {
                    if (curr->left == nullptr) {
                        curr->left = new Node(value);
                        break;
                    }
                    curr = curr->left;
                }
                else {
                    if (curr->right == nullptr) {
                        curr->right = new Node(value);
                        break;
                    }
                    curr = curr->right;
                }
            }
        }
    }

    int minDepth() {
        if (root == nullptr) {
            return 0;
        }
        queue<Node*> q;
        q.push(root);
        int minDepth = 999999999;
        int curr_depth = 1;

        while (!q.empty()) {
            int level_size = q.size();
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();

                if (curr->left == nullptr && curr->right == nullptr) {
                    minDepth = min(minDepth, curr_depth);
                }

                if (curr->left != nullptr) {
                    q.push(curr->left);
                }

                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }
            curr_depth ++;
        }
        return minDepth;
    }

    bool checkSameValue() {
        return checkSameValue(root, root->data);
    }
};


int main() {
    BinaryTree bin_tree;

    string iline;
    getline(cin, iline);

    stringstream input_ss(iline);
    int el;

    while (input_ss >> el) {
        bin_tree.insert(el);
    }

    cout << bin_tree.minDepth();

    return 0;
}