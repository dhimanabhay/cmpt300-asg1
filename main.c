#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
//#include "list.c"

void print(List* pList);
void test_insert_after();
void test_create();
void test_insert_before();
void test_first();
void test_last();
void test_next();
void test_prev();
void test_curr();
void test_remove();
void test_prepend();
void test_append();
void test_remove();
void test_concat();
void test_free();
void free(void* curr);
void test_trim();
bool equal(void* curr, void* pComparisonArg);
void test_search();

int one = 10;
int two = 20;
int three = 30;
int four = 40;
int five = 50;
void* a = &one;
void *b = &two;
void *c = &three;
void *d = &four;
void *e = &five;


int main() 
{
    //test_create();
    //test_insert_after();
    //test_insert_before();
    //test_first();
    //test_last();
    //test_next();
    //test_prev();
    //test_curr();
    //test_remove();
    //test_prepend();
    //test_append();
    test_concat();
    //test_free();
    //test_search();
    return 0;
}

void test_create(){

    printf("____________________ test List_create() ____________________  \n\n");
    
    printf("\n____List: 1____ \n");
    List* list = List_create();
    print(list);
    printf("Nodes           : %d \n", List_count(list) );

    printf("\n____List: 2____  \n");
    List* list2 = List_create();
    print(list2);
    printf("Nodes           : %d \n", List_count(list2) );

    printf("\n____List: 3____  \n");
    List* list3 = List_create();
    print(list3);
    printf("Nodes           : %d \n", List_count(list3) );

    printf("\n____List: 4____  \n");
    List* list4 = List_create();
    print(list4);
    printf("Nodes           : %d \n", List_count(list4) );

    printf("\n____List: 5____  \n");
    List* list5 = List_create();
    print(list5);
    printf("Nodes           : %d \n", List_count(list5) );
    printf("____________________________________________________________\n");
}

void test_insert_after(){

    printf("_________________ test List_insert_after() _________________\n\n");

    List* list = List_create();

    printf("\n\tList_insert_after(10)\n\n");
    List_insert_after(list, a);
    print(list);

    printf("\n\tList_insert_after(20)\n\n");
    List_insert_after(list, b);
    print(list);

    List_next(list);
    printf("\n\tList_next()\n");

    printf("\n\tList_insert_after(30)\n\n");
    List_insert_after(list, c);
    print(list);

    List_prev(list);
    List_prev(list);
    List_prev(list);
    printf("\n\tList_prev()\n");
    printf("\n\tList_prev()\n");
    printf("\n\tList_prev()\n");
    //printf("-------%d\n\n", *(int*)list->list_head->node_item);

    printf("\n\tList_insert_after(40)\n\n");
    List_insert_after(list, d);
    print(list);

    printf("\n\tList_insert_after(50)\n\n");
    List_insert_after(list, e);
    print(list);

}
void test_insert_before(){

    printf("_________________ test List_insert_before() _________________\n\n"); 
    List* list = List_create();

    List_insert_before(list, a);
    printf("\n\tList_insert_before(10)\n\n");
    print(list);

    List_insert_before(list, b);
    printf("\n\tList_insert_before(20)\n\n");
    print(list);

    List_prev(list);

    List_insert_before(list, c);
    printf("\n\tList_insert_before(30)\n\n");
    print(list);

    List_next(list);
    List_next(list);
    List_next(list);
    printf("\n\tList_next()\n\n");
    printf("\n\tList_next()\n\n");
    printf("\n\tList_next()\n\n");

    List_insert_before(list, d);
    printf("\n\tList_insert_before(40)\n\n");
    print(list);

    List_insert_before(list, e);
    printf("\n\tList_insert_before(50)\n\n");
    print(list);
}
void test_first()
{

    printf("_____________________ test List_first() _____________________\n\n");
    List* list = List_create();

    List_insert_after(list, b);
    printf("\n\tList_insert_after(20)\n\n");
    print(list);
    printf("\nFirst value       : %d\n", *(int *)List_first(list));
    printf("Expected first value: %d\n", two);

    List_insert_before(list, a);
    printf("\n\tList_insert_before(10)\n\n");
    print(list);
    printf("\nFirst value       : %d\n", *(int *)List_first(list));
    printf("Expected first value: %d\n", one);

    List_prepend(list, c);
    printf("\n\tList_prepend(30)\n\n");
    print(list);
    printf("\nFirst value       : %d\n", *(int *)List_first(list));
    printf("Expected first value: %d\n", three);

    List_insert_before(list, d);
    printf("\n\tList_insert_before(40)\n\n");
    print(list);
    printf("\nFirst value       : %d\n", *(int *)List_first(list));
    printf("Expected first value: %d\n", four);
}    
void test_last(){
    printf("______________________ test List_last() _____________________\n\n");
    List* list = List_create();

    List_insert_before(list, a);
    printf("\n\tList_insert_before(10)\n\n");
    print(list);
    printf("\nLast value: %d\n", *(int *)List_last(list));
    printf("Expected last value: %d\n", one);

    List_insert_after(list, b);
    printf("\n\tList_insert_after(20)\n\n");
    print(list);
    printf("\nLast value: %d\n", *(int *)List_last(list));
    printf("Expected last value: %d\n", two);

    List_append(list, c);
    printf("\n\tList_append(30)\n\n");
    print(list);
    printf("\nLast value: %d\n", *(int *)List_last(list));
    printf("Expected last value: %d\n", three);

    List_insert_after(list, d);
    printf("\n\tList_insert_after(40)\n\n");
    print(list);
    printf("\nLast value: %d\n", *(int *)List_last(list));
    printf("Expected last value: %d\n", four);

}
void test_next()
{
    printf("______________________ test List_next() _____________________\n\n");
    List* list = List_create();

    List_insert_before(list, a);
    List_insert_before(list, d);
    List_insert_before(list, b);
    List_insert_before(list, c);
    printf("\n\tList_insert_before(10)\n");
    printf("\n\tList_insert_before(40)\n");
    printf("\n\tList_insert_before(20)\n");
    printf("\n\tList_insert_before(30)\n\n");
    
    print(list);
    printf("\n");


    printf("Current : %d \n", *(int*)(list->list_current->node_item));
    printf("Next    : %d \n\n", *(int*)List_next(list));
    
    printf("Current : %d \n", *(int*)(list->list_current->node_item));
    printf("Next    : %d \n\n", *(int*)List_next(list));
    
    printf("Current : %d \n", *(int*)(list->list_current->node_item));
    printf("Next    : %d \n\n", *(int*)List_next(list));
    
    printf("Current : %d \n", *(int*)(list->list_current->node_item));
    if (List_next(list) == NULL)
    {
        printf("Next    : NULL\n\n");
    }
    print(list);
}
void test_prev()
{

    printf("______________________ test List_prev() _____________________\n\n");
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, d);
    List_insert_after(list, c);
    List_insert_after(list, b);
    printf("\n\tList_insert_after(10)\n\n");
    printf("\n\tList_insert_after(40)\n\n");
    printf("\n\tList_insert_after(30)\n\n");
    printf("\n\tList_insert_after(20)\n\n");
    
    print(list);
    printf("\n");


    printf("Current     : %d \n", *(int*)(list->list_current->node_item));
    printf("Previous    : %d \n\n", *(int*)List_prev(list));
    
    printf("Current     : %d \n", *(int*)(list->list_current->node_item));
    printf("Previous    : %d \n\n", *(int*)List_prev(list));
    
    printf("Current     : %d \n", *(int*)(list->list_current->node_item));
    printf("Previous    : %d \n\n", *(int*)List_prev(list));
    
    printf("Current     : %d \n", *(int*)(list->list_current->node_item));
    if (List_prev(list) == NULL)
    {
        printf("Previous    : NULL\n\n");
    }
    print(list);

}
void test_curr()
{

    printf("______________________ test List_curr() ____________________ \n\n");
    List* list = List_create();

    List_insert_before(list, a);
    printf("\n\tList_insert_before(10)\n\n");
    print(list);
    printf("\nCurrent value          : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", one);

    List_insert_after(list, b);
    printf("\n\tList_insert_after(20)\n\n");
    print(list);
    printf("\nCurrent value          : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", two);

    List_append(list, c);
    printf("\n\tList_append(30)\n\n");
    print(list);
    printf("\nCurrent value          : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", three);

    List_prepend(list, d);
    printf("\n\tList_prepend(40)\n\n");
    print(list);
    printf("\nCurrent value         : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", four);

    List_last(list);
    printf("\n\tList_last()\n\n");
    print(list);
    printf("\nCurrent value          : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", three);

    List_first(list);
    printf("\n\tList_first()\n\n");
    print(list);
    printf("\nCurrent value          : %d", *(int *)List_curr(list));
    printf("\nExpected Current value : %d\n", four);
    printf("\n");
}
void test_remove()
{
    printf("_____________________ test List_remove() ____________________\n\n"); 
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, d);
    List_insert_after(list, b);
    List_insert_after(list, c);
    printf("\n\tList_insert_after(10)\n\n");
    printf("\n\tList_insert_after(40)\n\n");
    printf("\n\tList_insert_after(20)\n\n");
    printf("\n\tList_insert_after(30)\n\n");

    print(list);

    printf("Removed Item    : %d \n\n", *(int *)List_remove(list));
    print(list);

    printf("Removed Item    : %d \n\n", *(int *)List_remove(list));
    print(list);

    printf("Removed Item    : %d \n\n", *(int *)List_remove(list));
    print(list);

    printf("Removed Item    : %d \n\n", *(int *)List_remove(list));
    print(list);
}
void test_prepend(){
    printf("_____________________ test List_prepend() ___________________\n\n"); 

    List* list = List_create();

    List_prepend(list, a);
    printf("\n\tList_prepend(10)\n\n");
    print(list);
    
    List_prepend(list, b);
    printf("\n\tList_prepend(20)\n\n");
    print(list);

    List_prepend(list, c);
    printf("\n\tList_prepend(30)\n\n");
    print(list);
    printf("\n");
}
void test_append(){
    printf("_____________________ test List_append() ____________________\n\n"); 

    List* list = List_create();

    List_append(list, a);
    printf("\n\tList_append(10)\n\n");
    print(list);

    List_append(list, b);
    printf("\n\tList_append(20)\n\n");
    print(list);

    List_append(list, c);
    printf("\n\tList_append(30)\n\n");
    print(list);
    printf("\n");
}
void test_concat()
{
    printf("_____________________ test List_concat() ____________________\n\n");
    List* list1 = List_create();

    List_insert_after(list1, a);
    List_insert_after(list1, d);
    List_insert_after(list1, c);
    List_insert_after(list1, b);
    printf("\n\tList_insert_after(10)\n\n");
    printf("\n\tList_insert_after(40)\n\n");
    printf("\n\tList_insert_after(30)\n\n");
    printf("\n\tList_insert_after(20)\n\n");
    
    printf("List 1\n");
    print(list1);

    List* list2 = List_create();
    List_insert_after(list2, a);
    List_insert_after(list2, b);
    List_insert_after(list2, c);
    List_insert_after(list2, d);
    printf("\n\tList_insert_after(10)\n\n");
    printf("\n\tList_insert_after(20)\n\n");
    printf("\n\tList_insert_after(30)\n\n");
    printf("\n\tList_insert_after(40)\n\n");

    printf("List 2 \n");
    print(list1);

    List* list3 = List_create();
    printf("\n");
    printf("--concat non empty-- \n");
    List_concat(list1, list2);
    print(list1);

    printf("--concat empty--  \n");
    List_concat(list3,list1);
    printf("\n\n-------------%d\n\n", List_count(list1));
    print(list3);
}
void test_free()
{
    printf("______________________ test List_free() _____________________\n\n");
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, b);
    List_insert_after(list, c);
    List_insert_after(list, d);
    printf("--list 1-- \n");
    if(list != NULL){
       print(list);
    }

    printf("--free list 1-- \n");
    List_free(list,free);
    printf("done free \n");
    if(list != NULL){
       print(list);
    }

    List* list1 = List_create();
    printf("--free empty list-- \n");
    List_free(list1,free);
    if(list1 != NULL){
       print(list1);
    }
}
void free(void* curr){
    printf("freed: %d \n", *(int *)curr);
}
void test_trim()
{
    printf("______________________ test List_trim() _____________________\n\n");
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, b);
    List_insert_after(list, c);
    List_insert_after(list, d);
    print(list);

    printf("----1----- \n");
    printf("%d \n", *(int *)List_trim(list));
    print(list);

    printf("----2----- \n");
    printf("%d \n", *(int *)List_trim(list));
    print(list);

    printf("----3----- \n");
    printf("%d \n", *(int *)List_trim(list));
    print(list);

    printf("----4----- \n");
    printf("%d \n", *(int *)List_trim(list));
    print(list);if (list->size == 0)
    {
        printf("%s", "List is empty");
        return;
    }
}
/*
void test_search()
{
    printf("_____________________ test List_search() ____________________\n\n"); 
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, b);
    List_insert_after(list, c);
    List_insert_after(list, d);
    print(list);

    printf("---search 4(true)--- \n");
    void* result = List_search(list,equal,d);
    if (result == NULL){
        printf("not found");
    }
    else{
        printf("found = %d \n",*(int *)result);
    }

    printf("---search 1(false)--- \n");
    result = List_search(list,equal,a);
    if (result == NULL){
        printf("not found \n");
    }
    else{
        printf("found = %d \n",*(int *)result);
    }
    
    printf("---search 4(false)--- \n");
    result = List_search(list,equal,d);
    if (result == NULL){
        printf("not found \n");
    }
    else{
        printf("found = %d \n",*(if (pList->size == 0)
    {
        printf("%s", "List is empty");
        return;
    }
    printf("---went back to first node--- \n");
    List_first(list);  t_free()
{
    printf("______________________ test List_free() _____________________\n\n");
    List* list = List_create();

    List_insert_after(list, a);
    List_insert_after(list, b);
    List_insert_after(list, c);
    List_insert_after(list, d);
    printf("--list 1-- \n");
    if(list != NULL){
       print(list);
    }

    printf("--free list 1-- \n");
    List_free(list,free);
    printf("done free \n");
    if(list != NULL){
       print(list);
    }

    List* list1 = List_create();
    printf("--free empty list-- \n");
    List_free(list1,free);
    if(list1 != NULL){
       print(list1);
    }
}
void fre
    printf("---search 3(true)--- \n");
    result = List_search(list,equal,c);
    if (result == NULL){
        printf("not found \n");
    }
    else{
        printf("found = %d \n",*(int *)result);
    }
}
*/
bool equal(void* curr, void* pComparisonArg){
    if ( *(int *)curr == *(int *)pComparisonArg){
        return true;
    }else{
        return false;
    }
}
void print(List *pList)
{
    if (pList->size == 0)
    {
        printf("%s", "Error: List is empty\n\n");
        return;
    }
    if (pList->list_bound == LIST_OOB_START)
    {
       printf("Error ListOutOfBounds : %s \n", "LIST_OOB_START\n\n");
       return;
    }
    if (pList->list_bound == LIST_OOB_END)
    {
        printf("Error ListOutOfBounds : %s \n", "LIST_OOB_END\n\n");
        return;
    }

    printf("List            : ");
    Node* node = pList->list_head;

    
    while (node != NULL)
    {
       printf("%d ", *(int*)node->node_item);
       node = node->node_next;
    }
    printf(" \n");
    printf("Current Node    : %d \n", *(int*)(pList->list_current->node_item));

    printf("Size            : %d \n", List_count(pList));
    if (pList->list_bound == LIST_OOB_START)
    {
        printf("ListOutOfBounds : %s \n", "LIST_OOB_START");
    }
    if (pList->list_bound == LIST_OOB_END)
    {
        printf("ListOutOfBounds : %s \n", "LIST_OOB_END");
    }
    if (pList->list_bound == LIST_OOB_FALSE)
    {
        printf("ListOutOfBounds : %s \n", "LIST_OOB_FALSE");
    }
    
}
