#include <stdio.h>
#include <stdlib.h>

// implement a list
typedef struct list {
    int data;
    list* next;
} list;

bool list_insert(list** head, int data) {
    list* t = (list*)malloc(sizeof(list));
    if(t == NULL) return false;
    t->data = data;
    t->next = *head;
    *head = t;
    return true;
}

list* list_search(list **head, int data) {
    list *t = *head;
    while (t != NULL) {
        if (t->data == data) {
            return t;
        }
        t = t->next;
    }
    return NULL;
}

bool list_remove(list **head, int data) {
    list *pre = NULL;
    list *tmp = *head;
    while (tmp != NULL && tmp->data != data) {
        pre = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return false; // not found
    if (pre == NULL) {
        *head = tmp->next; // Notice
    } else {
        pre->next = tmp->next;
    }
    free(tmp);
    return true;
}

void list_print(list** head) {
    list * t = *head;
    printf("list_print(): ");
    while (t != NULL) {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");
}


void list_clear_all(list** head) {
    list *t = *head;
    while (t != NULL) {
        list *tmp = t;
        t = t->next;
        free(tmp);
    }
    *head = NULL; // Notice
}

int main() {
    list *head = NULL;
    list_print(&head); // list_print(): 
    
    list_insert(&head, 1);
    list_insert(&head, 2);
    list_insert(&head, 3);
    list_print(&head); // list_print(): 3 2 1 
    
    list_clear_all(&head);
    list_print(&head); // list_print(): 
    
    list_insert(&head, 1);
    list_insert(&head, 2);
    list_insert(&head, 3);
    list_remove(&head, -1);
    list_print(&head); // list_print(): 3 2 1 
    
    list_remove(&head, 3);
    list_print(&head); // list_print(): 2 1 
    
    list_remove(&head, 1);
    list_print(&head); // list_print(): 2
    
    list_remove(&head, 1);
    list_print(&head); // list_print(): 2
    
    return 0;
}
