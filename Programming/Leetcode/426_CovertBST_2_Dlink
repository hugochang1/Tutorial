#include <iostream>
#include <list>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    
    Node() {
        data = 0;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    Node *prev;
    Node *head;
    
    Solution() {
        prev = NULL;
        head = NULL;
    }
    
    void inorder_traversal(Node *n) {
        if (n == NULL) return;
        
        inorder_traversal(n->left);
        
        if (prev) {
            n->left = prev;
            prev->right = n;
        } else {
            prev = n;
            head = n;
        }
        prev = n;
        
        inorder_traversal(n->right);
    }
};

int main() {
    //     3
    //    / \
    //   1   4
    //  / \
    // 0   2
    Node nodes[5];
    for(int i = 0; i < 5; i++) {
        nodes[i].data = i;
    }
    nodes[3].left = &nodes[1];
    nodes[3].right = &nodes[4];
    nodes[1].left = &nodes[0];
    nodes[1].right = &nodes[2];
    
    Solution s;
    s.inorder_traversal(&nodes[3]);
    
    Node* n = s.head;
    while (n != NULL) {
        printf("%d ", n->data); // 0 1 2 3 4 
        n = n->right;
    }
    printf("\n");
    
    return 0;
}
