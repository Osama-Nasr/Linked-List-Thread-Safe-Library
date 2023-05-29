#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Book Book;
typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Book {
    int id;
    char* author;
    char* content;
};

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

struct LinkedList {
    Node* head;
    int changeFirst;
    int (*comparator)(void*, void*);
};

void init_Book_types(Book* t, int i, char* a, char* c);

Book* createBook(int i, char* a, char* c);

void init_list(LinkedList* list, Node* h, int cf);

Node* createNode(void* data);

int compareNodes(void* data1, void* data2);

void append(LinkedList* list, void* data);

void deleteNodeByIndex(LinkedList* list, int index);

void printList(LinkedList* list, void (*printData)(void*));

void printInt(void* data);

void printFloat(void* data);

void printBook(void* data);