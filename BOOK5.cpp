#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    string name;
    vector<TreeNode*> children;

    TreeNode(string name) {
        this->name = name;
    }

    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    void printTree(int level = 0) {
        for (int i = 0; i < level; i++) cout << "  ";
        cout << "- " << name << endl;
        for (TreeNode* child : children) {
            child->printTree(level + 1);
        }
    }
};

// Constructing the book structure
TreeNode* constructBook() {
    TreeNode* book = new TreeNode("Book");
    
    TreeNode* chapter1 = new TreeNode("Chapter 1");
    TreeNode* section1_1 = new TreeNode("Section 1.1");
    TreeNode* subsection1_1_1 = new TreeNode("Subsection 1.1.1");
    TreeNode* subsection1_1_2 = new TreeNode("Subsection 1.1.2");
    
    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);
    chapter1->addChild(section1_1);
    
    TreeNode* chapter2 = new TreeNode("Chapter 2");
    TreeNode* section2_1 = new TreeNode("Section 2.1");
    TreeNode* subsection2_1_1 = new TreeNode("Subsection 2.1.1");
    section2_1->addChild(subsection2_1_1);
    chapter2->addChild(section2_1);
    
    book->addChild(chapter1);
    book->addChild(chapter2);
    
    return book;
}

int main() {
    TreeNode* bookTree = constructBook();
    bookTree->printTree();
    
    // Clean up dynamically allocated memory
    delete bookTree;
    return 0;
}

// Time Complexity Analysis:
// Constructing the tree takes O(N), where N is the total number of nodes.
// Printing the tree takes O(N) as we traverse each node once.

// Space Complexity Analysis:
// The space required is O(N), as we store references to each node in memory.
