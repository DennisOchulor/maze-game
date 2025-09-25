#include "linkedlist.h"
#include <stdlib.h>

LinkedList* createLinkedList()
{
    LinkedList* list = malloc(sizeof(LinkedList));
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insertStart(LinkedList* list, void* entry)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->val = entry;
    newNode->next = NULL;

    if(list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head = newNode;
    }

    list->count++;
}

void* removeStart(LinkedList* list)
{
    void* deletedVal;
    Node* deletedNode;
    if(list->count == 0)
    {
        deletedVal = NULL;
    }
    else
    {
        deletedNode = list->head;
        deletedVal = deletedNode->val;
        list->head = deletedNode->next;
        
        if(list->count == 1)
        {
            list->tail = NULL;
        }

        free(deletedNode);
        list->count--;
    }

    return deletedVal;
}

void insertLast(LinkedList* list, void* entry)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->val = entry;
    newNode->next = NULL;

    if(list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->count++;
}

void* removeLast(LinkedList* list)
{
    void* deletedVal;
    Node* deletedNode;
    Node* prev, *cur;
    if(list->count == 0)
    {
        deletedVal = NULL;
    }
    else if(list->count == 1)
    {
        deletedNode = list->head;
        deletedVal = deletedNode->val;
        list->head = NULL;
        list->tail = NULL;
        free(deletedNode);
        list->count--;
    }
    else
    {
        prev = NULL;
        cur = list->head;

        while(cur->next != NULL) 
        {
            prev = cur;
            cur = cur->next;
        }

        prev->next = NULL;
        list->tail = prev;
        deletedVal = cur->val;
        free(cur);
        list->count--;
    }

    return deletedVal;
}

void freeLinkedList(LinkedList* list)
{
    Node* prev = NULL;
    Node* node = list->head;
    while(node != NULL)
    {
        free(node->val);
        prev = node;
        node = node->next;
        free(prev);
    }
    free(list);
}