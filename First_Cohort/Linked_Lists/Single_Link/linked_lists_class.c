#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int value){
    Node* new_Node = (Node *)malloc(sizeof(Node));
    new_Node->data = value;
    new_Node->next = NULL;
    return new_Node;
}

void print_list(Node* head){
    Node *temp = head;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

Node* insert_at_head(Node* head, int value){
    Node* new_Node = create_node(value);
    new_Node->next = head;
    return new_Node;
}

Node* insert_at_tail(Node* head, int value){
    Node* new_Node = create_node(value);
    Node *temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_Node;
    return head;
}

int main(){
    Node *head = create_node(2);
    head->next = create_node(3);
    head->next->next = create_node(4);
    head->next->next->next = create_node(5);


    int x = 1;
    head = insert_at_head(head, x);
    head = insert_at_tail(head, x);
    print_list(head);
    return 0;
}