#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* create_node(int value){
    Node* new_Node = (Node *)malloc(sizeof(Node));
    new_Node->data = value;
    new_Node->next = new_Node->prev = NULL;
    return new_Node;
}

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

void free_list(DoublyLinkedList* list){
    Node* current = list->head;
    while(current){
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

DoublyLinkedList* create_list(){
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = list->tail = NULL;
    return list;
}

void insert_at_head(DoublyLinkedList* list, int value){
    Node* new_node = create_node(value);
    if(list->head == NULL){
        list->head = list->tail = new_node;
    }  else{
        new_node->prev = NULL;
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
}
    
void insert_at_tail(DoublyLinkedList* list, int value){
    Node* new_node = create_node(value);
    if (list->tail != NULL){
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        list->head = list->tail = new_node;
    }
}

void print_doubly_linked_list(DoublyLinkedList* list){
    Node *temp = list->head;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

void print_doubly_linked_list_backwards(DoublyLinkedList* list){
    Node *temp = list->tail;
    printf("NULL");
    while (temp != NULL){
        printf(" <-> %d", temp->data);
        temp = temp->prev;
    }
    printf(" <-> NULL\n");
}

void insert_at_n(DoublyLinkedList* list, int n, int value){
    if (n == 0){
        insert_at_head(list, value);
        return;
    }
    if (list->head == NULL){
        printf("Out of bounds");
        return;
    }
    Node* new_node = create_node(value);
    Node* current = list->head;
    int tracker = 0;
    while(tracker < n-1){
        if (current->next == NULL){
            printf("Out of bounds");
            free(new_node);
            return;
        }
        current = current->next;
        tracker ++;
    }
    new_node->next=current->next;
    new_node->prev=current;
    current->next = new_node;
    if(new_node->next != NULL){
        new_node->next->prev = new_node;
    } else list->tail = new_node;
}

bool search_key(DoublyLinkedList* list, int key)
{
    Node *curr = list -> head;

    while (curr != NULL)
    {
        if (curr->data == key) return true;
        curr = curr->next;
    }

    return false;
}

void delete_head(DoublyLinkedList* list)
{
    if (list->head == NULL) return;

    Node* temp = list->head;
    list->head = temp->next;

    if (list->head != NULL) list->head->prev = NULL;
    else list->tail = NULL;

    free(temp);
}

void delete_tail(DoublyLinkedList* list)
{
    if (list->tail == NULL) return;

    Node* temp = list->tail;

    if (list->head == list->tail) list->head = list->tail = NULL;
    else {
        list->tail = temp->prev;
        list->tail->next = NULL;
    }
    free(temp);
}

void delete_at_n(DoublyLinkedList* list, int position)
{
    if (list->head == NULL) return;

    if (position == 0){
        delete_head(list);
        return;
    }

    Node* curr = list->head;
    for (int i = 0; i < position - 1 && curr->next != NULL; i++) curr = curr->next;

    if (curr->next == NULL) return;

    Node* temp = curr->next;
    
    if (temp == list->tail){
        delete_tail(list);
        return;
    }
    curr->next = temp->next;
    temp->next->prev = curr;
    free(temp);
}


int main(){
    DoublyLinkedList* my_list = create_list();
    insert_at_head(my_list, 1);
    insert_at_head(my_list, 2);
    insert_at_head(my_list, 3);
    insert_at_tail(my_list, 4);
    insert_at_tail(my_list, 5);

    print_doubly_linked_list(my_list);
    print_doubly_linked_list_backwards(my_list);

    insert_at_n(my_list, 5, 3);
    insert_at_n(my_list, 6, 4);
    print_doubly_linked_list_backwards(my_list);

    free_list(my_list);
    return 0;
}