#include <stdio.h>
#include <stdlib.h>

//1721_SwappingNodesInALinkedList
struct Node {
    int value;
    Node* next;
    
    Node(): value(0), next(nullptr) {}
    Node(int val): value(val), next(nullptr) {}
    Node(int val, Node* n): value(val), next(n) {}
};

void traversal(Node* head) {
    printf("traversal ");
    Node* tmp = head;
    while(tmp != NULL) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void freeNode(Node* head) {
    while(head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int getNodeSize(Node* head) {
    int count = 0;
    while(head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Node* swapNode(Node* head, int k) {
    int size = getNodeSize(head);
    if(k > size) return head;
    
    Node* tmp = head;
    Node* left = NULL;
    Node* right = NULL;
    int index = 0;
    while(tmp != NULL) {
        index++;
        
        if(index == k) {
            left = tmp;
        }
        if(index == (size - k + 1)) {
            right = tmp;
        }
        if(left != NULL && right != NULL) {
            int tmpValue = left->value;
            left->value = right->value;
            right->value = tmpValue;
            break;
        }
        tmp = tmp->next;
    }
    
    return head;
}

int main() {
    Node* head;
    head = new Node(5);
    head = new Node(4, head);
    head = new Node(3, head);
    head = new Node(2, head);
    head = new Node(1, head);
    traversal(head); // 1 2 3 4 5
    swapNode(head, 2);
    traversal(head); // 1 4 3 2 5 
    freeNode(head);
    
    head = new Node(5);
    head = new Node(9, head);
    head = new Node(0, head);
    head = new Node(3, head);
    head = new Node(8, head);
    head = new Node(7, head);
    head = new Node(6, head);
    head = new Node(6, head);
    head = new Node(9, head);
    head = new Node(7, head);
    traversal(head); // 7 9 6 6 7 8 3 0 9 5 
    swapNode(head, 5);
    traversal(head); // 7 9 6 6 8 7 3 0 9 5 
    freeNode(head); 
    
    return 0;
}
