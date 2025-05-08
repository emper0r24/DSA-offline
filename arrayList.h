//#include "arrayList.h"
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if(a >= b)      return a;
    return b;
}

int min(int a, int b){
    if(a <= b)      return a;
    return b;
}

typedef struct 
{
    int *array;
    int capacity;
    int size;
    int cur_index;
} arrayList;

// Initialize list
void init(arrayList* list)
{
    list->capacity = 2;
    list->size = 0;
    list->array = (int *)malloc(sizeof(int) * list->capacity);
    list->cur_index = -1;
}

// Free memory
void free_list(arrayList* list)
{
    free(list->array);
    list->array = NULL;
    list->capacity = 0;
    list->size = 0;
    list->cur_index = -1;
}

// Double capacity
void increase_capacity(arrayList* list)
{    
    if(list->size > list->capacity / 2){
    list->capacity *= 2;
    list->array = (int *)realloc(list->array, sizeof(int) * list->capacity);
    printf("Capacity increased from %d to %d\n", list->capacity / 2, list->capacity);
    }
}

// Shrink capacity if needed
void decrease_capacity(arrayList* list)
{
    if (list->capacity > 4 && list->size < list->capacity / 4)
    {
        list->capacity /= 2;
        list->array = (int *)realloc(list->array, sizeof(int) * list->capacity);
        printf("Capacity decreased from %d to %d\n", list->capacity * 2, list->capacity);
    }
}

// Print list
void print(arrayList* list)
{   
    if(list->size == 0){
        printf("[ . ]\n");
        return;
    }
    printf("[ ");
    for (int i = 0; i < list->size; i++){
        printf("%d", list->array[i]);
        if(i == list->cur_index)    printf("| ");
        else    printf(" ");
    } 
    printf("]\n");
}

// Append to end
void append(int item, arrayList* list)
{   
    if(list->size == 0)     list->cur_index++;
    list->array[list->size++] = item;
    increase_capacity(list);
    print(list);
}

// Insert at current index
void insert(int item, arrayList* list)
{   
    for (int i = list->size; i > list->cur_index + 1; i--){
        list->array[i] = list->array[i - 1];
    }
    list->cur_index++;
    list->array[list->cur_index] = item;
    list->size++;
    increase_capacity(list);
    print(list);
}

// Delete item at current index
int delete_cur(arrayList* list)
{
    if (list->size == 0) return -1;
    int to_delete = list->array[list->cur_index];
    for (int i = list->cur_index; i < list->size - 1; i++){
        list->array[i] = list->array[i + 1];
    }
    if(list->cur_index == list->size - 1)   list->cur_index--;
    list->size--;
    decrease_capacity(list);
    print(list);
    return to_delete;
   // printf("%d is deleted\n", to_delete);
}

// Return size
int size(arrayList* list)
{
    return list->size;
}

// Move current index backward
void prev(int n, arrayList* list)
{
    list->cur_index -= n;
    list->cur_index = max(0, list->cur_index);
    print(list);
}

// Move current index forward
void next(int n, arrayList* list)
{
    list->cur_index += n;
    list->cur_index = min(list->cur_index, list->size - 1);
    print(list);
}

// Check if item is present
int is_present(int n, arrayList* list)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->array[i] == n)
            return 1;
    }
    return 0;
}

// Clear list
void clear(arrayList* list)
{
    free(list->array);
    list->capacity = 2;
    list->size = 0;
    list->cur_index = -1;
    list->array = (int *)malloc(sizeof(int) * list->capacity);
    print(list);
}

// Delete first occurrence of item
void delete_item(int item, arrayList* list)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->array[i] == item)
        {   
            if(i < list->cur_index || (i == list->cur_index && i == list->size - 1))     list->cur_index--;
            for (int j = i; j < list->size - 1; j++){
                list->array[j] = list->array[j + 1];
            }
               list->size--;
               decrease_capacity(list);
               print(list);
               return;
        }
    }
    printf("%d not found\n", item);
}

// Swap elements at two indices
void swap_ind(int ind1, int ind2, arrayList* list){
    
    if (ind1 < 0 || ind1 >= list->size || ind2 < 0 || ind2 >= list->size) {
        printf("Invalid indices for swap: %d, %d\n", ind1, ind2);
        print(list);
        return;
    }

    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp;
    print(list);
}
