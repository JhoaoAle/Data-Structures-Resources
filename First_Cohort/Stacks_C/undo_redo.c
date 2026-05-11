#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* s, char c) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = c;
    new_node->next = s->top;
    s->top = new_node;
}

char pop(Stack* s) {
    if (s->top == NULL)
        return '\0';

    Node* temp = s->top;
    char value = temp->data;

    s->top = temp->next;
    free(temp);

    return value;
}

char peek(Stack* s) {
    if (s->top == NULL)
        return '\0';

    return s->top->data;
}

bool is_empty_stack(Stack *s){
    return (s->top == NULL);
}
void free_stack(Stack *s){
    while(!is_empty_stack(s)) pop(s);
    free(s);
}

void clean_stack(Stack *s){
    while(!is_empty_stack(s)) pop(s);
}

void print_stack(Stack *s){
    Node* temp = s->top;
    while(temp != NULL){
        printf("%c \n", temp->data);
        temp = temp ->next;
    }
}

int main(){
    Stack* undo = createStack();
    Stack* redo = createStack();
    char c = '0';
    while(c != '1'){
        c = getchar();
        if(c == '\n') continue;
        if(c == 'q') return 0;
        if(c == '3'){
            char removed = pop(undo);
            if(removed != '\0') push(redo, removed);
            printf("\nUndo stack: \n");
            print_stack(undo);
            printf("Redo stack: \n");
            print_stack(redo);
        } else if(c == '4'){
            char restored = pop(redo);
            if(restored != '\0') push(undo,restored);
            printf("\nUndo stack: \n");
            print_stack(undo);
            printf("Redo stack: \n");
            print_stack(redo);
        } else if (c == '2'){
            printf("\nChecking stacks: \n");
            printf("Undo stack: \n");
            print_stack(undo);
            printf("\n Redo stack: \n");
            print_stack(redo);
        } 
        else {
            push(undo,c);
            clean_stack(redo);
        } 
    }   
    return 0;
}