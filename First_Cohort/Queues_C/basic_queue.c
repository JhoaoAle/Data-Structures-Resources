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

typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

Queue* create_queue(){
    Queue* my_queue = (Queue *)malloc(sizeof(Queue));
    my_queue->head = my_queue->tail = NULL;
    return my_queue;
}

bool is_empty_queue(Queue* my_queue){
    return (my_queue->head == NULL);
}

void enqueue(Queue* my_queue, int value){
    Node* new_node = create_node(value);
    if(my_queue->head == NULL){
        my_queue->head = my_queue->tail = new_node;
        return;
    } else {
        my_queue->tail->next = new_node;
        my_queue->tail = new_node;
    }
}

int dequeue(Queue* my_queue){
    if(my_queue->head == NULL){
        printf("Queue is empty\n");
        return -1;
    }

    Node* temp = my_queue->head;
    int value = my_queue->head->data;

    my_queue->head = my_queue->head->next;

    if(my_queue->head == NULL) my_queue->tail = NULL;
    free(temp);
    return value;
}

int peek(Queue* my_queue){
    if(my_queue->head == NULL){
        printf("Queue is empty\n");
        return -1;
    }
    return my_queue->head->data;
}

void print_queue(Queue* my_queue){
    if(my_queue->head == NULL){
        printf("NULL\n");
        return;
    }
    Node* temp = my_queue->head;
    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void free_queue(Queue* queue){
    Node* current = queue->head;
    Node* temp;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    free(queue);
}

int main(){
    Queue* my_queue = create_queue();

    enqueue(my_queue, 10);
    enqueue(my_queue, 20);
    enqueue(my_queue, 30);

    print_queue(my_queue);

    printf("Dequeued: %d\n", dequeue(my_queue));
    print_queue(my_queue);

    printf("Front: %d\n", peek(my_queue));

    free_queue(my_queue);
    return 0;
}
