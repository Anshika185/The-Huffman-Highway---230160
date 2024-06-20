#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to determine if two trees are isomorphic
bool isIsomorphic(TreeNode* t1, TreeNode* t2) {
    // If both trees are empty, they are isomorphic
    if (t1 == nullptr && t2 == nullptr) {
        return true;
    }

    // If one of the trees is empty and the other is not, they are not isomorphic
    if (t1 == nullptr || t2 == nullptr) {
        return false;
    }

    bool case1 = isIsomorphic(t1->left, t2->left) && isIsomorphic(t1->right, t2->right);
    return case1;
}

// Helper function to create a new tree node
TreeNode* newNode(int data) {
    TreeNode* node = new TreeNode(data);
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

int main() {
    // Tree 1
    TreeNode* t1 = newNode(1);
    t1->left = newNode(2);
    t1->right = newNode(3);
    t1->left->left = newNode(4);
    t1->left->right = newNode(6);
    t1->right->left = newNode(5);
    t1->right->right = newNode(4);

    // Tree 2
    TreeNode* t2 = newNode(1);
    t2->left = newNode(3);
    t2->right = newNode(2);
    t2->left->left = newNode(6);
    t2->left->right = newNode(4);
    t2->right->left = newNode(5);
    t2->right->right = newNode(7);
    

    if (isIsomorphic(t1, t2)) {
        cout << "The trees are isomorphic." << endl;
    } else {
        cout << "The trees are not isomorphic." << endl;
    }
    return 0;
}