#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A node has pointers to the previous and next elements, along with the data it stores (int in-this case)
typedef struct Node {
    struct Node* next;
    int data;
    struct Node* prev;
} Node;

// In order to create a Node we need to know the value. Then we:
/*
1. Allocate memory for a Node, no more no less, and point to where the space has been separated through malloc
2. The data of the new node is the value we receive
3. The node exists in a "vacuum", so before and after is NULL
4. The function is of type "pointer to Node", so its what it returns
*/
Node *create_node(int value){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->prev = new_node->next = NULL;
    return new_node;
}

// A doubly linked list has a head and a tail, both are nodes.
typedef struct DLL{
    Node *head;
    Node *tail;
}DLL;

// In order to create a doubly linked list we need to know nothing at all since the list starts empty. Then we:
/*
1. Allocate memory for a Doubly Linked List, no more no less, and point to where the space has been separated through malloc
2. The list starts empty, so both head and tail are NULL. Try to initialize it with a Node, how whould that work?
4. The function is of type "pointer to Doubly Linked List", so its what it returns
*/DLL *create_list(){
    DLL *my_list = (DLL*)malloc(sizeof(DLL));
    my_list->head = my_list->tail = NULL;
    return my_list;
}

//Inserting a Node at the head of a DLL is easy since we know where the DLL starts. 
// 
// We need to know in which list is it going to go and which value will go in it. 
// Thus:
/*
1. We create a Node with the received value.
2. If the list was empty at first, this first Node is both the head and the tail, assign accordingly
3. If not, the current head of the list will go after this new node, and, accordingly, the predecessor of the current head
will be the new node.
4. Now this node is the head of the list. 
*/
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


//Inserting a Node at the tail of a DLL is easy since we know where the DLL ends. 
// 
// We need to know in which list is it going to go and which value will go in it. 
// Thus:
/*
1. We create a Node with the received value.
2. If the list was empty at first, this last Node is both the head and the tail, assign accordingly
3. If not, the current tail of the list will go before this new node, and, accordingly, the succesor of the current tail
will be the new node.
4. Now this node is the tail of the list. 
*/
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


//Inserting a Node at any position n of a DLL is interesting.
// 
// We need to know in which list is it going to go and which value will go in it, along with the position to insert. 
// Thus:
void insert_at_n(DLL* list, int n, int value){
    // 0 is the head, call the function accordingly
    if (n==0){
        insert_at_head(list, value);
        return;
    }
    // If we are trying to insert something farther than 0 on an empty list that would not make any sense
    if (list->head == NULL){
        printf("Out of bounds \n");
        return;
    }
    // After the sanity checks, the Node is created
    Node* new_node = create_node(value);
    //Start looking from the head forward...
    Node* current = list->head;
    // Keeping track of where we are
    int tracker = 0;
    // We will want to stop just before the position we want to insert into, since this node will be our support to position the new node
    while(tracker < n-1){
        // If while going through the list at the position before we find ourselves at the tail, this would make no sense either
        if (current->next == NULL){
            printf("Out of bounds");
            free(new_node);
            return;
        }
        // Otherwise, keep traversing the list from the head forward
        current = current->next;
        tracker ++;
    }
    // Now we can "wedge" the new node: The next of where we are, will be the succesor of the node we want to insert
    new_node->next=current->next;
    // Since we are wedging the new node, now it will be the succesor of where we are now.
    current->next = new_node;
    // Accordingly, the node where we are will be the predecessor of the new node we "wedged" into the list
    new_node->prev = current;
    // The succesor of the new node is NULL only if we ended up adding the element at the tail, so it is the new tail of the list.
    // Update accordingly.
    if (new_node->next != NULL){
        // If it isnt the tail, then the new node is the predecessor of its succesor, and all assignations are done
        new_node->next->prev = new_node;
    } else list->tail = new_node;
}

// Moving forward from the head
void print_dll(DLL* list){
    Node *temp = list->head;
    printf("NULL <-> ");
    while (temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}
// Moving backwards from the tail
void print_dll_backwards(DLL* list){
    Node *temp = list->tail;
    printf("NULL <-> ");
    while (temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL \n");
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




    return 0;
}