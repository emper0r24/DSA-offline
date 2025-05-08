//#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct {
    node* head;
    node* tail;
    node* cur;
    int size;
} linkedList;

void init(linkedList* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
}

void free_list(linkedList* list)
{
    node* current = list->head;
    while (current){
        node* next = current->next;
        free(current);
        current = next;
    }
    list->head = list->tail = list->cur = NULL;
    list->size = 0;
}

void print(linkedList* list)
{
    if(list->size == 0){
        printf("[ . ]\n");
        return;
    }
    node* temp = list->head;
    printf("[ ");
    while (temp != NULL){
        printf("%d", temp->element);
        if(temp == list->cur)  printf("| ");
        else    printf(" ");
        temp = temp->next;
    }
    printf("]\n");
}

void insert(int item, linkedList* list)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->element = item;
    new_node->prev = new_node->next = NULL;
    if(list->cur == NULL){      // Empty DLL
        list->head = new_node;
        list->tail = new_node;
    }
    else if(list->cur->next == NULL){   
        new_node->prev = list->cur;
        list->cur->next = new_node;
        list->tail = new_node;
    }
    else{
        new_node->next = list->cur->next;
        new_node->prev = list->cur;
        list->cur->next->prev = new_node;
        list->cur->next = new_node;
    }

    list->cur = new_node;
    list->size++;
    print(list);
}

void append(int item, linkedList* list)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->element = item;  
    new_node->prev = new_node->next = NULL;
    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
        list->cur = new_node;
    }
    else{
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    print(list);
}

void delete_head(linkedList* list){
    if (list->head == NULL) return;

    node* temp = list->head;

    if (list->head == list->tail) {
        list->head = list->tail = list->cur = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
        if (list->cur == temp)
            list->cur = list->head;
    }
    free(temp);
    list->size--;
}



void delete_tail(linkedList* list){
    if (list->tail == NULL) return;

    node* temp = list->tail;

    if (list->tail == list->head) {
        list->head = list->tail = list->cur = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        if (list->cur == temp)
            list->cur = list->tail;
    }

    free(temp);
    list->size--;
}


int delete_cur(linkedList* list)
{
    if (list->cur == NULL) return -1;
    int st = list->cur->element;

    if (list->cur == list->head){
        delete_head(list);
    }
    else if (list->cur == list->tail){
        delete_tail(list);
    }
    else {
        node* temp = list->cur;
        node* next = list->cur->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = temp->prev = NULL;
        list->cur = next;
        free(temp);
        list->size--;
    }

    print(list);
    return st;
}


int size(linkedList* list)
{
    return list->size;
}

void prev(int n, linkedList* list)
{   
    for(int i = 1; i <= n; i++){
        list->cur = list->cur->prev;
        if(!list->cur){
            list->cur = list->head;
            break;
        }
    }
    print(list);
}

void next(int n, linkedList* list)
{   
    for(int i = 1; i <= n; i++){
        list->cur = list->cur->next;
        if(!list->cur){
            list->cur = list->tail;
            break;
        }
    }
    print(list);
}

int is_present(int n, linkedList* list)
{
    node* temp = list->head;
    while (temp) {
        if (temp->element == n)     return 1;
        temp = temp->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    free_list(list);
    init(list);
    print(list);
}

void delete_item(int item, linkedList* list)
{
    node* temp = list->head;
    while (temp) {
        if (temp->element == item) {
            if(temp == list->head){
                if(list->cur == list->head)     list->cur = temp->next;
                delete_head(list);
            }
            else if(temp == list->tail){
                if(list->cur == list->tail)     list->cur = temp->prev;
                delete_tail(list);
            }
            else{
                if(temp == list->cur)       list->cur = temp->next;
                list->size--;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp->next = temp->prev = NULL;
                free(temp);
            }
            print(list);
            return;
        }
        temp = temp->next;
    }

    printf("%d not found\n", item);

}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    if (ind1 == ind2) return;
    if (ind1 >= list->size || ind2 >= list->size || ind1 < 0 || ind2 < 0) return;

    node* node1 = list->head;
    node* node2 = list->head;

    for (int i = 0; i < ind1; i++) node1 = node1->next;
    for (int i = 0; i < ind2; i++) node2 = node2->next;

    int temp = node1->element;
    node1->element = node2->element;
    node2->element = temp;
    print(list);
}