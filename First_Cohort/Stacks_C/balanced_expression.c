#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct NodeChar {
    char data;               // Symbol ( '(', '[', '{' )
    struct NodeChar *next;   
} NodeChar;

typedef struct {
    NodeChar *top;           
} Stack;

// Create an empty stack
Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}


bool isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Push a character onto the stack
void push(Stack *stack, char c) {
    NodeChar *newNode = (NodeChar*)malloc(sizeof(NodeChar));
    newNode->data = c;
    newNode->next = stack->top; 
    stack->top = newNode;
}

// Pop the top character from the stack
char pop(Stack *stack) {
    if (isEmpty(stack)) return '\0'; // If empty, return null char
    NodeChar *temp = stack->top;
    char popped = temp->data;
    stack->top = temp->next;
    free(temp);             
    return popped;
}

char peek(Stack *stack) {
    if (isEmpty(stack)) return '\0';
    return stack->top->data;
}

void freeStack(Stack *stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}


bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool isBalanced(const char *expr) {
    Stack *stack = createStack();  

    // Traverse the expression character by character
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        // If it's an opening symbol, push onto stack
        if (c == '(' || c == '[' || c == '{') {
            push(stack, c);
        } 
        // If it's a closing symbol, check for matching
        else if (c == ')' || c == ']' || c == '}') {
            if (isEmpty(stack)) {
                freeStack(stack);
                return false;  
            }
            char top = pop(stack);
            if (!isMatchingPair(top, c)) {
                freeStack(stack);
                return false; 
            }
        }
    }

    bool balanced = isEmpty(stack);
    freeStack(stack);
    return balanced;
}

int main(){
    const char *tests[] = {
    "{[()]}",        // Balanced
    "{([)]}",        // Not balanced
    "[(a+b)*{c/d}]"  // Balanced
    };

    for (int i = 0; i < (sizeof(tests)/sizeof(tests[0])); i++) {
        printf("Expression: %s -> %s\n",
            tests[i],
            isBalanced(tests[i]) ? "Balanced" : "Not balanced");
    }
    return 0;
}