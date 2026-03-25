#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    struct Node* next;
    int data;
    struct Node* prev;
} Node;

Node *create_node(int value){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->prev = new_node->next = NULL;
    return new_node;
}

typedef struct DLL{
    Node *head;
    Node *tail;
}DLL;

DLL *create_list(){
    DLL *my_list = (DLL*)malloc(sizeof(DLL));
    my_list->head = my_list->tail = NULL;
    return my_list;
}

void insert_at_head(DLL* list, int value){
    Node* new_node = create_node(value);
    if(list->head == NULL){
        list->head = list->tail = new_node;
    } else{
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
}

void insert_at_tail(DLL* list, int value){
    Node* new_node = create_node(value);
    if(list->tail == NULL){
        list->head = list->tail = new_node;
    } else{
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void insert_at_n(DLL* list, int n, int value){
    if (n==0){
        insert_at_head(list, value);
        return;
    }
    if (list->head == NULL){
        printf("Out of bounds \n");
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
    current->next = new_node;
    new_node->prev = current;
    if (new_node->next != NULL){
        new_node->next->prev = new_node;
    } else list->tail = new_node;
}

void print_dll(DLL* list){
    Node *temp = list->head;
    printf("NULL <-> ");
    while (temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

void print_dll_backwards(DLL* list){
    Node *temp = list->tail;
    printf("NULL <-> ");
    while (temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL \n");
}


bool search_key(DLL* list, int key)
{
    Node *curr = list -> head;

    while (curr != NULL)
    {
        if (curr->data == key) return true;
        curr = curr->next;
    }

    return false;
}

void delete_head(DLL* list)
{
    if (list->head == NULL) return;

    Node* temp = list->head;
    list->head = temp->next;

    if (list->head != NULL) list->head->prev = NULL;
    else list->tail = NULL;

    free(temp);
}

void delete_tail(DLL* list)
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

void delete_at_n(DLL* list, int position)
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
    DLL *my_list = create_list();
    insert_at_head(my_list,7);
    insert_at_head(my_list,9);

    insert_at_tail(my_list, 20);

    insert_at_n(my_list,1,8);
    insert_at_n(my_list,4,42);

    print_dll(my_list);
    print_dll_backwards(my_list);

    delete_at_n(my_list,4);

    print_dll(my_list);
    print_dll_backwards(my_list);

    return 0;
}