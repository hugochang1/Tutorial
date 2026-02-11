#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    tree *l;
    tree *r;
    int data;
} tree;

tree *tree_create(int data) {
    tree *t = (tree*)malloc(sizeof(tree));
    t->data = data;
    t->l = NULL;
    t->r = NULL;
    return t;
}

// binary tree traversal - part 1
  // pre-order: root > left > right (depth first search, DFS)
  // in-order: left > root > right
  // post-order: left > right > root

void tree_traversal_preorder(tree *t) {
    if (t == NULL) return;
    printf("%d ", t->data);
    tree_traversal_preorder(t->l);
    tree_traversal_preorder(t->r);
}

void tree_traversal_inorder(tree *t) {
    if (t == NULL) return;
    tree_traversal_inorder(t->l);
    printf("%d ", t->data);
    tree_traversal_inorder(t->r);
}

void tree_traversal_postorder(tree *t) {
    if (t == NULL) return;
    tree_traversal_postorder(t->l);
    tree_traversal_postorder(t->r);
    printf("%d ", t->data);
}

//--------------------------------------
// binary tree traversal - part 2
  // level-order 
// implement a queue
typedef struct list {
    tree *data;
    list *next;
} list;

typedef struct queue {
    list *front;
    list *rear;
} queue;

void queue_init(queue *q) {
    q->front = q->rear = NULL;
}

void queue_enqueue(queue *q, tree * data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->data = data;
    tmp->next = NULL;
    if (q->front == NULL) {
        q->front = tmp;
    } else {
        q->rear->next = tmp;
    }
    q->rear = tmp;
}

bool queue_empty(queue *q) {
    return q->front == NULL;
}

bool queue_dequeue(queue *q, tree **data) {
    if (queue_empty(q)) return false;
    list *tmp = q->front;
    *data = tmp->data;
    q->front = tmp->next;
    if (q->front == NULL) q->rear = NULL;
    return true;
}

void tree_traversal_levelorder(tree *t) {
    if (t == NULL) return;
    queue q;
    queue_init(&q);
    
    queue_enqueue(&q, t);
    while (!queue_empty(&q)) {
        tree *tmp = NULL;
        if (queue_dequeue(&q, &tmp)) {
            printf("%d ", tmp->data);
        }
        if(tmp->l) queue_enqueue(&q, tmp->l);
        if(tmp->r) queue_enqueue(&q, tmp->r);
    }
}

//--------------------------------------
int main() {
    tree *root = tree_create(1);
    root->l = tree_create(2);
    root->r = tree_create(3);
    root->l->l = tree_create(4);
    root->l->r = tree_create(5);
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    
    tree_traversal_preorder(root); // 1 2 4 5 3 
    printf("\n");
    
    tree_traversal_inorder(root); // 4 2 5 1 3 
    printf("\n");
    
    tree_traversal_postorder(root); // 4 5 2 3 1 
    printf("\n");

    tree_traversal_levelorder(root); // 1 2 3 4 5 
    printf("\n");

    return 0;
}
