#include <stdio.h>
#include <stdlib.h>

// implement hash

// Space: O(N)
typedef struct list {
    int key;
    int value;
    list *next;
} list;

// Time: O(1)
void list_insert(list **l, int key, int value) {
    list *tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) return;
    tmp->key = key;
    tmp->value = value;
    tmp->next = *l;
    *l = tmp;
}

// Time: O(N)
bool list_get(list **l, int key, int *value) {
    list *tmp = *l;
    while (tmp != NULL) {
        if (tmp->key == key) {
            *value = tmp->value;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Time: O(N)
bool list_remove(list **l, int key) {
    list *pre = NULL;
    list *tmp = *l;
    while (tmp != NULL && tmp->key != key) {
        pre = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return false; //not found
    if (pre == NULL) {
        *l = tmp->next;
    } else {
        pre->next = tmp->next;
    }
    free(tmp);
    return true;
    
    return true;
}

void list_print(list **l) {
    list *tmp = *l;
    printf("list_print() ");
    while (tmp != NULL) {
        printf("%d/%d ", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

#define HASH_MAX 4
// Space: O(K)
typedef struct hash {
    list *table[HASH_MAX];
} hash;

// Time: O(K)
void hash_init(hash *h) {
    int i;
    for (i = 0; i < HASH_MAX; i++) {
        h->table[i] = NULL;
    }
}

// Time: O(1)
void hash_put(hash *h, int key, int value) {
    int code = key % HASH_MAX;
    list_insert(&h->table[code], key, value);
}

// Time: O(1)
bool hash_get(hash *h, int key, int *value) {
    int code = key % HASH_MAX;
    return list_get(&h->table[code], key, value);
}

// Time: O(1)
bool hash_remove(hash *h, int key) {
    int code = key % HASH_MAX;
    return list_remove(&h->table[code], key);
}

void hash_print(hash *h) {
    int i;
    for (i = 0; i < HASH_MAX; i++) {
        printf("hash index=%d ", i);
        list_print(&h->table[i]);
    }
}

int main() {
    hash h;
    int i;
    
    hash_init(&h);
    hash_print(&h);
    /*
    hash index=0 list_print() 
    hash index=1 list_print() 
    hash index=2 list_print() 
    hash index=3 list_print() 
    */
    
    for (i = 0; i < 8; i++) {
        hash_put(&h, i, i*i);
    }
    hash_print(&h);
    /*
    hash index=0 list_print() 4/16 0/0 
    hash index=1 list_print() 5/25 1/1 
    hash index=2 list_print() 6/36 2/4 
    hash index=3 list_print() 7/49 3/9 
    */

    for (i = 0; i < 8; i++) {
        int value = -1;
        bool ret = hash_get(&h, i, &value);
        printf("key=%d ret=%d value=%d\n", i, ret, value);
        /*
        key=0 ret=1 value=0
        key=1 ret=1 value=1
        key=2 ret=1 value=4
        key=3 ret=1 value=9
        key=4 ret=1 value=16
        key=5 ret=1 value=25
        key=6 ret=1 value=36
        key=7 ret=1 value=49
        */
    }
    hash_print(&h);
    /*
    hash index=0 list_print() 4/16 0/0 
    hash index=1 list_print() 5/25 1/1 
    hash index=2 list_print() 6/36 2/4 
    hash index=3 list_print() 7/49 3/9 
    */
    
    for (i = 0; i < 8; i++) {
        bool ret = hash_remove(&h, i);
        printf("key=%d ret=%d\n", i, ret);
        /*
        key=0 ret=1
        key=1 ret=1
        key=2 ret=1
        key=3 ret=1
        key=4 ret=1
        key=5 ret=1
        key=6 ret=1
        key=7 ret=1
        */
    }
    hash_print(&h);
    /*
    hash index=0 list_print() 
    hash index=1 list_print() 
    hash index=2 list_print() 
    hash index=3 list_print() 
    */

    return 0;
}
