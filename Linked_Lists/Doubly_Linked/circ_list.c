#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* create_node(int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

typedef struct CLL {
    Node* tail;
} CLL;

CLL* create_list(){
    CLL* list = (CLL*)malloc(sizeof(CLL));
    return  list;
}

void free_list(CLL* my_list){
    if (my_list->tail == NULL) return;
    Node* head -> my_list->tail->next;
    Node* current = head;
    Node* temp;
    do{
        temp = current;
        current = temp->next;
        free(temp);
    } while(current!=head);
    free(list);
}

void insert_at_tail(CLL* list, int value){
    Node* new_node = create_node(value);
    if (list->tail == NULL){
        list->tail = new_node;
        new_node->next = new_node;
    } else {
        new_node->next = list->tail->next;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}