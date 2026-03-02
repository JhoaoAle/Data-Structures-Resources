#include <stdio.h>
#include <stdlib.h>

//Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main(){
    // Node creation
    Node *head = NULL;
    Node *second = NULL;
    Node * third = NULL;

    head = (Node*)malloc(sizeof(Node));
    second = (Node*)malloc(sizeof(Node));
    third = (Node*)malloc(sizeof(Node));

    //Assigning values and linking Nodes
    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    //How to print
    Node *temp = head;

    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");

    return 0;
}