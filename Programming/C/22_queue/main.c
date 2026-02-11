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

void queue_init(queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

bool queue_empty(queue *q) {
    return q->front == NULL;
}

bool queue_enqueue(queue *q, int data) {
    list *l = (list*)malloc(sizeof(list));
    if (l == NULL) return false;
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

bool queue_dequeue(queue *q, int *data) {
    if (q->front == NULL) return false;
    list *tmp = q->front;
    *data = tmp->data;
    q->front = tmp->next;
    free(tmp);
    if (q->front == NULL) q->rear = NULL;
    return true;
}

void queue_dump(queue *q) {
    list *l = q->front;
    printf("queue_dump() front=%p rear=%p ", q->front, q->rear);
    while (l != NULL) {
        printf("%d ", l->data);
        l = l->next;
    }
    printf("\n");
}

int main() {
    int i;
    queue q;
    queue_init(&q);
    
    queue_dump(&q); // queue_dump() front=(nil) rear=(nil) 
    
    for (i = 0; i < 8; i++) {
        queue_enqueue(&q, i);
    }
    queue_dump(&q); // queue_dump() front=0x92d2c0 rear=0x92d3a0 0 1 2 3 4 5 6 7 
    
    while(!queue_empty(&q)) {
        int data = -1;
        bool ret = queue_dequeue(&q, &data);
        printf("ret=%d data=%d\n", ret, data);
        /*
        ret=1 data=0
        ret=1 data=1
        ret=1 data=2
        ret=1 data=3
        ret=1 data=4
        ret=1 data=5
        ret=1 data=6
        ret=1 data=7
        */
    }
    queue_dump(&q); // queue_dump() front=(nil) rear=(nil) 
    
    for (i = 0; i < 16; i++) {
        queue_enqueue(&q, i);
    }
    queue_dump(&q); // queue_dump() front=0x92d380 rear=0x92d4a0 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
    
    return 0;
}
