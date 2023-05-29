#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "LLSafe.h"

#define NUM_THREADS 4
#define NUM_BOOKS 1000

void *addBooks(void *arg) {
    LinkedList *list = (LinkedList *) arg;
    int threadNum = *(int *)arg;
    //printf("Thread %d started\n", threadNum);

    // Appending 1000 books to the global list
    for (int i = 0; i < NUM_BOOKS; i++) {
        char author[16], content[16];
        snprintf(author, sizeof(author), "Author %d-%d", threadNum, i);
        snprintf(content, sizeof(content), "Content %d-%d", threadNum, i);

        Book *newBook = createBook(threadNum * NUM_BOOKS + i, strdup(author), strdup(content));

        append(list, newBook);
    }
    
    //printf("Thread %d finished\n", threadNum);
    return NULL;
}

void *removeBooks(void *arg){
    LinkedList *list = (LinkedList *) arg;
    int threadNum = *(int *)arg;

// Removing the first book from the list 1000 times
    for (int i = 0; i < NUM_BOOKS; i++) {
        if (list->head != NULL) {
            deleteNodeByIndex(list, 0);
        }
    }
}

int main() {
    LinkedList list;
    Node* head = NULL;
    init_list(&list, NULL, 0);

    pthread_t tid[NUM_THREADS];
 
    // Creating 4 threads and adding to the list
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tid[i], NULL, addBooks, &list);
    }
   
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tid[i], NULL, removeBooks, &list);
    }

    // Waiting for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Remaining books in the list:\n");
    printList(&list, printBook);
    return 0;
}
