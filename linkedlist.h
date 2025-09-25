#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
    void* val;
    struct Node* next;
} Node;

typedef struct
{
    int count;
    Node* head;
    Node* tail;
} LinkedList;

LinkedList* createLinkedList();
void insertStart(LinkedList* list, void* entry);
void* removeStart(LinkedList* list);
void insertLast(LinkedList* list, void* entry);
void* removeLast(LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif