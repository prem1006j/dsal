#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

// Tree node
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Check if the character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Construct expression tree from prefix expression
Node* constructTree(const string& prefix) {
    stack<Node*> s;

    // Traverse the prefix expression from right to left
    for (int i = prefix.size() - 1; i >= 0; --i) {
        char ch = prefix[i];

        Node* node = new Node(ch);

        if (isOperator(ch)) {
            // Operator must have two operands
            if (s.size() < 2) {
                cerr << "Invalid expression!\n";
                return nullptr;
            }
            node->left = s.top(); s.pop();
            node->right = s.top(); s.pop();
        }

        s.push(node);
    }

    if (s.size() != 1) {
        cerr << "Invalid expression!\n";
        return nullptr;
    }

    return s.top();
}

// Non-recursive postorder traversal using two stacks
void postorderNonRecursive(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    cout << "Postorder Traversal (Non-Recursive): ";
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

// Delete tree (recursive method is okay here)
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function
int main() {
    string prefix = "+--a*bc/def";
    Node* root = constructTree(prefix);

    if (root) {
        postorderNonRecursive(root);
        deleteTree(root);
        cout << "Expression tree deleted successfully.\n";
    }

    return 0;
}
