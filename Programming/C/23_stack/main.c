#include <stdio.h>
#include <stdlib.h>

// implement a stack
typedef struct stack {
    int data;
    stack *next;
} stack;

void stack_push(stack **s, int data) {
    stack *tmp = (stack*)malloc(sizeof(stack));
    if (tmp == NULL) return;
    tmp->data = data;
    tmp->next = *s;
    *s = tmp;
}

bool stack_pop(stack **s, int *data) {
    stack *tmp = *s;
    if (tmp == NULL) return false;
    *data = tmp->data;
    (*s) = tmp->next;
    free(tmp);
    return true;
}

bool stack_empty(stack **s) {
    return *s == NULL;
}

void stack_print(stack **s) {
    stack *tmp = *s;
    printf("stack_print() ");
    while(tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

int main() {
    int i;
    stack* s = NULL;
    
    for (i = 0; i < 4; i++) {
        stack_push(&s, i);
    }
    stack_print(&s); // stack_print() 3 2 1 0 
    
    while (!stack_empty(&s)) {
        int data = -1;
        bool ret = stack_pop(&s, &data);
        printf("ret=%d data=%d\n", ret, data);
        /*
        ret=1 data=3
        ret=1 data=2
        ret=1 data=1
        ret=1 data=0
        */
    }
    stack_print(&s); // stack_print()
    return 0;
}
