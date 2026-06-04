#include <stdio.h>
#include <vector>

using namespace std;
//0426_ConvertBST2SortedLinkedList

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

void recursive(Node** pre, Node* curr, Node** head) {
    if(curr == nullptr) return;
    recursive(pre, curr->left, head);

    if(*head == nullptr) {
        *head = curr;
    } else {
        (*pre)->right = curr;
        curr->left = *pre;
    }
    *pre = curr;

    recursive(pre, curr->right, head);
}

Node* solution(Node* r) {
    Node* head = nullptr;
    Node* pre = nullptr;
    recursive(&pre, r, &head);
    return head;
}

int main() {
    //     3
    //    / \
    //   1   4
    //  / \
    // 0   2
    Node* r = new Node(3);
    r->left = new Node(1);
    r->right = new Node(4);
    r->left->left = new Node(0);
    r->left->right = new Node(2);

    Node* n = solution(r);
    while(n != nullptr) {
        printf("%d ", n->data);
        n = n->right;
    }
    printf("\n");

    return 0;
}
