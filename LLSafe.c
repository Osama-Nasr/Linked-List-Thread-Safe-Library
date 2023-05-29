#include <stdio.h>
#include "LLSafe.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct Book Book;
typedef struct Node Node;
typedef struct LinkedList LinkedList;

pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

void init_Book_types(Book* t, int i, char* a, char* c) {
    t->id = i;
    t->author = a;
    t->content = c;
}

Book* createBook(int i, char* a, char* c) {
    Book* newBook = (Book*)calloc(1, sizeof(Book));
    if (newBook != NULL) {
        init_Book_types(newBook, i, a, c);
    }
    return newBook;
}

void init_list(LinkedList* list, Node* h, int cf) {
    list->head = h;
    list->changeFirst = cf;
    list->comparator = compareNodes;
}

Node* createNode(void* data) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int compareNodes(void* data1, void* data2) {
    Book* ptr1 = (Book*)data1;
    Book* ptr2 = (Book*)data2;

    if (ptr1 == NULL || ptr2 == NULL) {
        return 0;
    }

    int filled1 = 0, filled2 = 0;
    if (ptr1->id != 0) filled1++;
    if (ptr1->author != NULL) filled1++;
    if (ptr1->content != NULL) filled1++;
    if (ptr2->id != 0) filled2++;
    if (ptr2->author != NULL) filled2++;
    if (ptr2->content != NULL) filled2++;

    if (filled1 > filled2) return 1;
    if (filled1 < filled2) return -1;

    int id_cmp = memcmp(&(ptr1->id), &(ptr2->id), sizeof(int));
    if (id_cmp != 0) {
        return id_cmp > 0 ? 1 : -1;
    }

    int author_cmp = strcmp(ptr1->author, ptr2->author);
    if (author_cmp != 0) {
        return author_cmp > 0 ? 1 : -1;
    }

    return strcmp(ptr1->content, ptr2->content) > 0 ? 1 : -1;
}

void append(LinkedList* list, void* data) {
    pthread_mutex_lock(&list_mutex);

    Node* newNode = createNode(data);
    if (newNode == NULL) {
        list->changeFirst = 1;
        pthread_mutex_unlock(&list_mutex);
        return;
    }

    Node* current = list->head;
    Node* previous = NULL;
    int comp = 0;

    while (current != NULL && (comp = list->comparator(newNode->data, current->data)) > 0) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        newNode->next = current;
        list->head = newNode;
        list->changeFirst = 1;
    } else {
        previous->next = newNode;
        newNode->next = current;
    }

    pthread_mutex_unlock(&list_mutex);
}
   
void deleteNodeByIndex(LinkedList* list, int index) {
    if (index < 0) {
        printf("Error: Index must be non-negative\n");
        return;
    }

    pthread_mutex_lock(&list_mutex);

    if (index == 0) {
        Node* nodeToDelete = list->head;
        list->head = nodeToDelete->next;
        if (nodeToDelete->next == NULL) {
            list->changeFirst = 1;
        }
        free(((Book*)nodeToDelete->data)->author);
        free(((Book*)nodeToDelete->data)->content);
        free(nodeToDelete->data);
        free(nodeToDelete);
        pthread_mutex_unlock(&list_mutex);
        return;
    }

    Node* currentNode = list->head;
    Node* previousNode = NULL;
    int currentIndex = 0;

    while (currentNode != NULL && currentIndex != index) {
        previousNode = currentNode;
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (currentNode == NULL) {
        printf("Error: Index out of bounds\n");
        pthread_mutex_unlock(&list_mutex);
        return;
    }

    previousNode->next = currentNode->next;
    free(((Book*)currentNode->data)->author);
    free(((Book*)currentNode->data)->content);
    free(currentNode->data);
    free(currentNode);

    pthread_mutex_unlock(&list_mutex);
}

void printList(LinkedList* list, void (*printData)(void*)) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        printData(currentNode->data);
        currentNode = currentNode->next;
    }
}

void printInt(void* data) {
    printf("%d ", *((int*)data));
}

void printFloat(void* data) {
    printf("%.2f ", *((float*)data));
}

void printBook(void* data) {
    Book* book = (Book*)data;
    printf("%d %s %s\n", book->id, book->author, book->content);
}
