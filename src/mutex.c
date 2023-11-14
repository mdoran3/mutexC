/*
* This program demonstrates the use of a mutex for multithreading in C
*
* @author Mitchell Doran, Ruben Acuña
* @version 1.2
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10000

//data node
struct dataNode {
    int data;
    struct dataNode* next;

};

/////////////////////////////////////
//GLOBALS
/////////////////////////////////////
//linked list
struct dataNode* listHead = NULL;
//mutex lock
pthread_mutex_t lock;


//add node to front of linked list
void addFront(int data) {
    struct dataNode* node = (struct dataNode*)malloc(sizeof(struct dataNode));

    node->data = data;

    /*
    /////////////////////////////////////////////////////////////////////////////
                                                                                |
    88b           d88  88        88  888888888888  88888888888  8b        d8    |
    888b         d888  88        88       88       88            Y8,    ,8P     |
    88`8b       d8'88  88        88       88       88             `8b  d8'      |
    88 `8b     d8' 88  88        88       88       88aaaaa          Y88P        |
    88  `8b   d8'  88  88        88       88       88"""""          d88b        |
    88   `8b d8'   88  88        88       88       88             ,8P  Y8,      |
    88    `888'    88  Y8a.    .a8P       88       88            d8'    `8b     |
    88     `8'     88   `"Y8888Y"'        88       88888888888  8P        Y8    |
                                                                                |
    /////////////////////////////////////////////////////////////////////////////
    */
    pthread_mutex_lock(&lock);   //LOCK with mutex
        node->next = listHead;
        listHead = node;
    pthread_mutex_unlock(&lock); //UNLOCK with mutex
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

//runner method for threading
void* runnerCreateArgNode(void* arg) {
    int data = (int)(intptr_t)arg;

    addFront(data);

    pthread_exit(0);
}

//main
int main() {
    pthread_t tids[NUM_THREADS];

    //initialize mutex
    pthread_mutex_init(&lock, NULL);

    //create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tids[i], NULL, runnerCreateArgNode, (void*)(intptr_t) i);
    }

    //join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    //print
    displayList();

    //destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}