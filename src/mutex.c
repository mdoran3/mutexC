#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10000

struct dataNode {
    int data;
    struct dataNode* next;

};

struct dataNode* listHead = NULL;

//add node to front of linked list
void addFront(int data) {
    struct dataNode* node = (struct dataNode*)malloc(sizeof(struct dataNode));

    node->data = data;
    node->next = listHead;
    listHead = node;
}

//displays data in each node of linked list
void displayList() {
    struct dataNode* iter = listHead;
    int count = 0;

    while(iter != NULL) {
        printf("Node data = %d\n", iter->data);
        count++;
        iter = iter->next;
    }
    printf("Node count = %d\n", count);
}

void* runnerCreateArgNode(void* arg) {
    int data = (int)(intptr_t)arg;

    addFront(data);

    pthread_exit(0);
}

int main() {
    pthread_t tids[NUM_THREADS];

    //create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tids[i], NULL, runnerCreateArgNode, (void*)(intptr_t) i);
    }

    //join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    displayList();

    return 0;
}