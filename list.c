#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static List arr_list[LIST_MAX_NUM_HEADS]; //to store items that are in use
static Node arr_node[LIST_MAX_NUM_NODES];

static List ptr_free_nodes; //to store free ones not in use
//static List ptr_free_heads;
typedef struct ptr_free_head_s ptr_head;
struct ptr_free_head_s
{
	List *list_head;
	List *list_tail;
	int size;
};
ptr_head ptr_free_heads;
//remove node and update node_used array, node waapis aajaye jisme nyi list bana sake
void removeNode(int index)
{
    //iif all nodes are unused, return coz nikalne ke liye kuch nhi hai
    if (ptr_free_nodes.size == LIST_MAX_NUM_NODES)
    {
        return;
    }
    else
    {
        //remove node from array arr_node aur isko next available node banado
        //arr_node ke uss index ki node available krvado
        Node *remove_node = &arr_node[index];
        remove_node->node_index = 0;
        remove_node->node_index = 0;
        remove_node->node_next = NULL;
        remove_node->node_previous = NULL;

        //if no unused node is present, it will be first 
        if (ptr_free_nodes.size == 0)
        {
            ptr_free_nodes.list_head = remove_node;
            ptr_free_nodes.list_tail = remove_node;
        }
        //vrna isko wapis list main daldo
        else
        {
            ptr_free_nodes.list_tail->node_next = remove_node;
            ptr_free_nodes.list_tail = remove_node;
        }

        ptr_free_nodes.size = ptr_free_nodes.size -1;
    }
}
void removeHead(int index)
{
    if(ptr_free_heads.size == LIST_MAX_NUM_HEADS)
    {
        return;
    }
    else
    {
    
        List* list = &arr_list[index];
        list->list_next = NULL;
        if(ptr_free_heads.size == 0)
        {
            ptr_free_heads.list_head = list;
            ptr_free_heads.list_tail = list;
        }
        else
        {
            ptr_free_heads.list_tail->list_next = list;
            ptr_free_heads.list_tail = list;
        }
        ptr_free_heads.size = ptr_free_heads.size + 1;
    }
}
bool firstInvoke = true;
int get_free_node() //return idnex of free node from ptr_free_nodes
{
    //no available nodes
    if(ptr_free_nodes.size == 0){
        return -1;
    }
    //give the current avalable, reduce size and move ptr to next node
    else
    {
        int index = ptr_free_nodes.list_head->node_index;
        ptr_free_nodes.list_head = ptr_free_nodes.list_head->node_next;
        ptr_free_nodes.size = ptr_free_nodes.size - 1;
        return index;
    }
}
int get_free_head() // to use in list_create
{
    if(ptr_free_heads.size == 0){
        return -1;
    }
    else{
        int index = ptr_free_heads.list_head->list_index;
        ptr_free_heads.list_head = ptr_free_heads.list_head->list_next;
        ptr_free_heads.size = ptr_free_heads.size - 1;
        return index;      
    }
}

List* List_create()
{
    if (firstInvoke)
    {
        firstInvoke = false;
        //create empty lists and nodes and attacht hem to next ones
        for(int i = 0; i < LIST_MAX_NUM_HEADS; i++)
        {
            List* list = &arr_list[i];
            list->list_index = i;

            if(i < LIST_MAX_NUM_HEADS)
            {
                list->list_next = &arr_list[i+1];
            }
        }
        ptr_free_heads.list_head = &arr_list[0];
        ptr_free_heads.list_tail = &arr_list[LIST_MAX_NUM_HEADS-1];
        ptr_free_heads.size = LIST_MAX_NUM_HEADS;
   
        for(int i = 0; i < LIST_MAX_NUM_NODES; i++)
        {
            Node* node = &arr_node[i];
            node->node_index = i;

            if(i < LIST_MAX_NUM_NODES)
            {
                node->node_next = &arr_node[i+1];
            }
        }

        ptr_free_nodes.list_head = &arr_node[0];
        ptr_free_nodes.list_tail = &arr_node[LIST_MAX_NUM_NODES-1];
        ptr_free_nodes.size = LIST_MAX_NUM_NODES;

    }
    //we have free nodes available
    if (ptr_free_heads.size != 0 )
    {
        //get position
        int index = get_free_head();
        //add it to used list array arr_list and initialize its values
        List* pList = &arr_list[index];
        pList->size = 0;
	    pList->list_head = NULL;
	    pList->list_current = NULL;
        pList->list_bound = LIST_OOB_FALSE;
	    pList->list_tail = NULL;
        pList->list_index = index;
        pList->list_next = NULL;
        return pList;
    }

    //last case if no free node is available
    return NULL;
}

int List_count(List* pList)
{
    return pList->size;
}

void* List_first(List* pList)
{
    //set first item = curr item
    //return pointer to curr of first item node of list
    if (pList->size != 0)
    {
        pList->list_current = pList->list_head;
        return pList->list_current->node_item;
    }

    //else current of list = null, return null;
    //remove out of bounds, if any
    pList->list_current = NULL;
    pList->list_bound = LIST_OOB_FALSE;
    return NULL;
}

void* List_last(List* pList)
{
    //same logic as list_first
    if (pList->size != 0)
    {
        pList->list_current = pList->list_tail;
        return pList->list_current->node_item;
    }

    //else current of list = null, return null;
    //remove out of bounds, if any
    pList->list_current = NULL;
    pList->list_bound = LIST_OOB_FALSE;
    return NULL;
}

void* List_next(List* pList)
{
    // empty list or already out of bound
    if (pList->size == 0 || pList->list_bound == LIST_OOB_END)
    {
        return NULL;
    }
    
    // if curr is before start, return head node as current and OOB False
    if (pList->list_bound == LIST_OOB_START)
    {
        pList->list_current = pList->list_head;
        pList->list_bound = LIST_OOB_FALSE;
        return pList->list_current->node_item;
    }
    // curr is in list
    else
    {
        // if curr is at tail, return null and OOB end
        if (pList->list_current == pList->list_tail)
        {
            pList->list_current = NULL;
            pList->list_bound = LIST_OOB_END;
            return NULL;
        }
        else //if curr is not at tail, return next
        {
            pList->list_current = pList->list_current->node_next;
            return pList->list_current->node_item;
        }
    }
}

void* List_prev(List* pList)
{
    // empty list or already out of bound
    if (pList->size == 0 || pList->list_bound == LIST_OOB_START)
    {
        return NULL;
    }
    
    // if curr is after end, return tail node as current and OOB False
    if (pList->list_bound == LIST_OOB_END)
    {
        pList->list_current = pList->list_tail;
        pList->list_bound = LIST_OOB_FALSE;
        return pList->list_current->node_item;
    }
    // curr is in list
    else
    {
        // if curr is at head, return null and OOB start
        if (pList->list_current == pList->list_head)
        {
            pList->list_current = NULL;
            pList->list_bound = LIST_OOB_START;
            return NULL;
        }
        else //if curr is not at head, return previous
        {
            pList->list_current = pList->list_current->node_previous;
            return pList->list_current->node_item;
        }
    }
}

void* List_curr(List* pList)
{   //return curr of node at list_curr if not null
    if (pList->list_current != NULL)
    {
        return pList->list_current->node_item;
    }
    return NULL;
}

int List_insert_after(List* pList, void* pItem)
{
    //if nodes are available, add and change position of empty node array
    if(ptr_free_nodes.size != 0)
    {
        //get index from array where free node is available
        //fir uss index ko ptr krke node banake insert after krdo
        int index = get_free_node();
        Node *insert_this = &arr_node[index];
        insert_this->node_item = pItem;
        insert_this->node_next = NULL;
        insert_this->node_previous = NULL;

        //if plist is empty, add as tail & head
        if(pList->size == 0)
        {
            pList->list_head = insert_this;
            pList->list_tail = insert_this;
            pList->size = pList->size + 1;
            pList->list_current = insert_this;
            pList->list_bound = LIST_OOB_FALSE;
            return 0;
        }
        else
        {
            //if beyond start, as a head insert krdo
            if(pList->list_bound == LIST_OOB_START)
            {
                insert_this->node_next = pList->list_head;
                insert_this->node_next->node_previous = insert_this;
                pList->list_head = insert_this;
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
            //if after end, as a tail add krdo
            else if(pList->list_bound == LIST_OOB_END || pList->list_current == pList->list_tail)
            {
                insert_this->node_previous = pList->list_tail;
                insert_this->node_previous->node_next = insert_this;
                pList->list_tail = insert_this;
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
            else
            {
                insert_this->node_next = pList->list_current->node_next;  
                pList->list_current->node_next = insert_this;
                insert_this->node_previous = pList->list_current;
                insert_this->node_next->node_previous = insert_this;
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
        }
    }
    return -1;
}

int List_insert_before(List* pList, void* pItem)
{
    //if nodes are available, add and change position of empty node array
    //---same logic as insert_after---//
    if(ptr_free_nodes.size != 0)
    {
        if(ptr_free_nodes.size  != 0)
        {

        int index = get_free_node();
        Node* insert_this = &arr_node[index];
        insert_this->node_item = pItem; 
        insert_this->node_next = NULL;
        insert_this->node_previous= NULL;

        if(pList->size == 0){
            pList->list_head= insert_this;
            pList->list_tail = insert_this;
            pList->size = pList->size + 1;
            pList->list_current = insert_this;
            pList->list_bound = LIST_OOB_FALSE;
            return 0;
        }
        else{
            if(pList->list_bound == LIST_OOB_START || pList->list_current == pList->list_head){
                insert_this->node_next = pList->list_head;
                insert_this->node_next->node_previous = insert_this;
                pList->list_head = insert_this;
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
            else if(pList->list_bound == LIST_OOB_END ){
                insert_this->node_previous = pList->list_tail;
                insert_this->node_previous->node_next = insert_this;
                pList->list_tail = insert_this;
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
            else{
                insert_this->node_next = pList->list_current;
                insert_this->node_previous = pList->list_current->node_previous;
                pList->list_current->node_previous->node_next = insert_this;
                pList->list_current->node_previous = insert_this; 
                pList->size = pList->size + 1;
                pList->list_current = insert_this;
                pList->list_bound = LIST_OOB_FALSE;
                return 0;
            }
        }
    }
    }

    return -1;
}

int List_append(List* pList, void* pItem)
{
    //set curr to last item using list_last func, then use insert_after to insert
    List_last(pList);
    return List_insert_after(pList, pItem);
}

int List_prepend(List* pList, void* pItem)
{
    //set curr to first item using list_first func, then use insert_before to insert *same as append*
    List_first(pList);
    return List_insert_before(pList, pItem);
}

void* List_remove(List* pList)
{
    Node *node = pList->list_current;
    void *item_return = pList->list_current->node_item;
    //empty list or oob
    if (pList->list_current == NULL || pList->size == 0)
    {
        return NULL;
    }
    //single element
    else if (pList->list_current == pList->list_head && pList->list_current == pList->list_tail)
    {
        pList->list_head = NULL;
        pList->list_tail = NULL;
        pList->list_current = NULL;
        pList->size = pList->size - 1;
        removeNode(node->node_index);
        return item_return;
    }
    //multiple element, curr at head
    else if (pList->list_current == pList->list_head)
    {
        pList->list_current = pList->list_current->node_next;
        pList->list_head = pList->list_head->node_next;
        pList->list_head->node_previous = NULL;
        pList->size = pList->size - 1;
        removeNode(node->node_index);
        return item_return;
    }
    //multiple element, curr at tail
    else if (pList->list_current == pList->list_tail)
    {
        pList->list_current = pList->list_current->node_previous;
        pList->list_tail = pList->list_tail->node_previous;
        pList->list_tail->node_next = NULL;
        pList->size = pList->size - 1;
        removeNode(node->node_index);
        return item_return;
    }
    //multiple element, curr at some point
    else
    {
        pList->list_current->node_previous->node_next = pList->list_current->node_next;
        pList->list_current->node_next->node_previous = pList->list_current->node_previous;
        pList->list_current = pList->list_current->node_next;
        pList->size--;
        removeNode(node->node_index);
        return item_return;
    }

}

void* List_trim(List* pList)
{
    //empty list returns null
    if (pList->size == 0)
    {
        return NULL;
    }
    //if head is tail
    if (pList->size == 1 || pList->list_head == pList->list_tail)
    {
        void *item = pList->list_tail->node_item;
        Node *prevTail = pList->list_tail;
        pList->list_head = NULL;
        pList->list_current = NULL;
        pList->size = 0;
        pList->list_bound = LIST_OOB_FALSE;
        removeNode(pList->list_tail->node_index);
        pList->list_tail = NULL;
        return prevTail->node_item;
    }
    else //list has data
    {
        Node *newTail = pList->list_tail->node_previous;
        void *item = pList->list_tail->node_item;
        Node *prevTail = pList->list_tail;
        newTail->node_next = NULL;
        pList->list_tail = newTail;
        pList->list_current = newTail;
        removeNode(prevTail->node_index);
        pList->size = pList->size - 1;
        return item;
        
    }
}

void List_concat(List* pList1, List* pList2)
{
    //plist2 has data
    if (pList2->size > 0)
    {
        //plist1 has data
        if (pList1->size > 0)
        {
            //attach both at tail of plist1
            pList1->list_tail->node_next = pList2->list_head;
            pList2->list_head->node_previous = pList1->list_tail;
            pList1->list_tail = pList2->list_tail;
            pList1->size = pList1->size + pList2->size;
            //delete plist2
            removeHead(pList2->list_index);
            pList2->list_head = NULL;
            pList2->list_tail = NULL;
            pList2->list_current = NULL;
            pList2->size = 0;
            pList2->list_bound = LIST_OOB_FALSE;
        }
        else //plist1 has no data
        {
            pList1->list_tail = pList2->list_tail;
            pList1->list_head = pList2->list_head;
            pList1->size = pList2->size;
            pList1->list_current = pList1->list_head;
            //delete plist2
            removeHead(pList2->list_index);
            pList2->list_head->node_previous = NULL;
            pList2->list_tail->node_next = NULL;
            pList2->list_head = NULL;
            pList2->list_tail = NULL;
            pList2->list_current = NULL;
            pList2->size = 0;
            pList2->list_bound = LIST_OOB_FALSE;
            
        }
    }
    else //plist2 has no data
    {
        //just delete plist2
        removeHead(pList2->list_index);
        pList2->list_head->node_previous = NULL;
        pList2->list_tail->node_next = NULL;
        pList2->list_head = NULL;
        pList2->list_tail = NULL;
        pList2->list_current = NULL;
        pList2->list_bound = LIST_OOB_FALSE;
        
    }
}

typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn)
{
    //agar list khali hai to seedha free krdo
    if(pList->size == 0)
    {
        pList->list_head = NULL;
        pList->list_tail = NULL;
        pList->list_current = NULL;
        pList->size = 0;
        pList->list_bound = LIST_OOB_FALSE;
        removeHead(pList->list_index);
    }
    else
    {
        //store current node and remove current one until list is empty (list->head == null)
        Node* node = pList->list_head;
        while(node != NULL){
            Node *nextNode = node->node_next;
            void* itemToBeFreedFromNode = node->node_item;          
            node->node_item = NULL;
            node->node_next = NULL;
            node->node_previous = NULL;
            removeNode(node->node_index);
            (*pItemFreeFn)(itemToBeFreedFromNode);
            node = nextNode;
        }
        //again remove krdo list ko
        pList->list_head = NULL;
        pList->list_tail = NULL;
        pList->list_current = NULL;
        pList->size = 0;
        pList->list_bound = LIST_OOB_FALSE;
        removeHead(pList->list_index);
    }
}

typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
    if (pList->list_bound == LIST_OOB_START)
    {
        List_first(pList);
    }
    if (pList->size == 0)
    {
        return NULL;
    }
    int counter = 1;
    Node *node = pList->list_current;
    void *item_ret = NULL;
    while(pList->list_current != NULL)
    {
        item_ret = List_curr(pList);
        if (pComparator(item_ret, pComparisonArg))
        {
            return item_ret;
        }
        else
        {
            if (pList->list_bound == LIST_OOB_END)
            {
                if (counter)
                {
                    pList->list_current = pList->list_head;
                    pList->list_bound = LIST_OOB_FALSE;
                }
                else
                {
                    --counter;
                    return NULL;
                }
            }
            else
            {
                List_next(pList);
            }
        }
    }
    return NULL;
}
