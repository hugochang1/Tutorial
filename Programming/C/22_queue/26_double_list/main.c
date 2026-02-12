#include <stdio.h>
#include <stdlib.h>

// implement a double linked list
typedef struct node {
    int data;
    node *prev;
    node *next;
} node;

typedef struct dlink {
    node *head;
    node *tail;
} dlink;

void dlink_init(dlink *l) {
    l->head = NULL;
    l->tail = NULL;
}

void dlink_add_to_head(dlink *l, int data) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) return;
    n->data = data;
    if (l->head == NULL) {
        n->prev = n->next = NULL;
        l->head = l->tail = n;
    } else {
        n->prev = NULL;
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    }
}

void dlink_add_to_tail(dlink *l, int data) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) return;
    n->data = data;
    if (l->head == NULL) {
        n->prev = n->next = NULL;
        l->head = l->tail = n;
    } else {
        n->next = NULL;
        n->prev = l->tail;
        l->tail->next = n;
        l->tail = n;
    }
}

node* dlink_get_index(dlink *l, int index) {
    node *n = l->head;
    while(n != NULL && index > 0) {
        n = n->next;
        index--;
    }
    return n;
}

bool dlink_del_from_head(dlink *l) {
    if (l->head == NULL) return false;
    if (l->head == l->tail) {
        free(l->head);
        l->head = l->tail = NULL;
    } else {
        node *tmp = l->head;
        l->head = tmp->next;
        l->head->prev = NULL;
        free(tmp);
    }
    return true;
}

bool dlink_del_from_tail(dlink *l) {
    if (l->tail == NULL) return false;
    if (l->tail == l->head) {
        free(l->tail);
        l->head = l->tail = NULL;
    } else {
        node *tmp = l->tail;
        l->tail = tmp->prev;
        l->tail->next = NULL;
        free(tmp);
    }
    return true;
}

bool dlink_del_from_node(dlink *l, node *n) {
    if (n == NULL) return false;
    if (n == l->head) return dlink_del_from_head(l);
    if (n == l->tail) return dlink_del_from_tail(l);
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
    return true;
}

void dlink_print(dlink *l) {
    printf("dlink_print() ");
    
    node *n = l->head;
    printf("H->T: ");
    while(n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    
    n = l->tail;
    printf("T->H: ");
    while(n != NULL) {
        printf("%d ", n->data);
        n = n->prev;
    }
    
    printf("\n");
}

int main() {
    dlink d;
    node* n;
    dlink_init(&d);
    
    dlink_add_to_head(&d, 3);
    dlink_add_to_head(&d, 2);
    dlink_add_to_head(&d, 1);
    dlink_print(&d); // dlink_print() H->T: 1 2 3 T->H: 3 2 1 
    
    dlink_add_to_tail(&d, 4);
    dlink_add_to_tail(&d, 5);
    dlink_add_to_tail(&d, 6);
    dlink_print(&d); // dlink_print() H->T: 1 2 3 4 5 6 T->H: 6 5 4 3 2 1 
    
    dlink_del_from_head(&d);
    dlink_print(&d); // dlink_print() H->T: 2 3 4 5 6 T->H: 6 5 4 3 2 
    
    dlink_del_from_tail(&d);
    dlink_print(&d); // dlink_print() H->T: 2 3 4 5 T->H: 5 4 3 2 
    
    n = dlink_get_index(&d, 1);
    printf("n %d\n", n->data); // n 3
    dlink_del_from_node(&d, n);
    dlink_print(&d); // dlink_print() H->T: 2 4 5 T->H: 5 4 2 
    
    n = dlink_get_index(&d, 0);
    printf("n %d\n", n->data); // n 2
    dlink_del_from_node(&d, n);
    dlink_print(&d); // dlink_print() H->T: 4 5 T->H: 5 4 
    
    n = dlink_get_index(&d, 1);
    printf("n %d\n", n->data); // n 5
    dlink_del_from_node(&d, n);
    dlink_print(&d); // dlink_print() H->T: 4 T->H: 4 
    return 0;
}
