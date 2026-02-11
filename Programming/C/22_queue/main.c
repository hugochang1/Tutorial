#include <stdio.h>
#include <stdlib.h>

// implement a queue
typedef struct list {
    int data;
    list *next;
} list;

typedef struct queue {
    list *front;
    list *rear;
} queue;

// O(1)
void queue_init(queue *q) {
    q->front = q->rear = NULL;
}

// O(1)
bool queue_empty(queue *q) {
    return q->front == NULL;
}

// O(1)
bool queue_enqueue(queue* q, int data) {
    list *l = (list*)malloc(sizeof(list));
    l->data = data;
    l->next = NULL;
    if (q->front == NULL) {
        q->front = l;
    } else {
        q->rear->next = l;
    }
    q->rear = l;
    return true;
}

// O(1)
bool queue_dequeue(queue* q, int *data) {
    if (queue_empty(q)) return false;
    list *l = q->front;
    *data = l->data;
    q->front = l->next;
    free(l);
    if (q->front == NULL) q->rear = NULL;
    return true;
}

void queue_print(queue *q) {
    list *l = q->front;
    printf("queue_print() ");
    while (l != NULL) {
        printf("%d ", l->data);
        l = l->next;
    }
    printf("\n");
}

int main() {
    queue q;
    int i;
    
    queue_init(&q);
    queue_print(&q); // queue_print() 
    
    for(i = 0; i < 4; i++) {
        queue_enqueue(&q, i);
    }
    queue_print(&q); // queue_print() 0 1 2 3 
    
    while(!queue_empty(&q)) {
        int data = -1;
        bool ret = queue_dequeue(&q, &data);
        printf("ret=%d data=%d\n", ret, data);
        /*
        ret=1 data=0
        ret=1 data=1
        ret=1 data=2
        ret=1 data=3
        */
    }
    queue_print(&q); // queue_print() 

    return 0;
}
