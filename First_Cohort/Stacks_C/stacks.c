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

typedef struct Stack {
    Node* top;
} Stack;

Stack* create_stack(){
    Stack* stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

bool is_empty(Stack* stack){
    return (stack->top == NULL);
}

void push(Stack* stack, int value){
    Node* new_node = create_node(value);

    new_node->next = stack->top;
    stack->top = new_node;
}

int pop(Stack* stack){
    if(stack->top == NULL){
        printf("Stack is empty\n");
        return -1;
    }

    Node* temp = stack->top;
    int value = temp->data;

    stack->top = stack->top->next;
    free(temp);

    return value;
}

int peek(Stack* stack){
    if(stack->top == NULL){
        printf("Stack is empty\n");
        return -1;
    }

    return stack->top->data;
}

void print_stack(Stack* stack){
    if(stack->top == NULL){
        printf("NULL\n");
        return;
    }

    Node* temp = stack->top;

    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void free_stack(Stack* stack){
    Node* current = stack->top;
    Node* temp;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    free(stack);
}

int main(){
    Stack* my_stack = create_stack();

    push(my_stack, 10);
    push(my_stack, 20);
    push(my_stack, 30);

    print_stack(my_stack);

    printf("Popped: %d\n", pop(my_stack));
    print_stack(my_stack);

    printf("Top: %d\n", peek(my_stack));

    free_stack(my_stack);
    return 0;
}