#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_LENGTH 50

typedef struct Patient {
    int id;
    char name[NAME_LENGTH];
    char priority; // 'R', 'Y', 'G'
} Patient;

typedef struct Node {
    Patient data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;


Node* create_node(Patient patient){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = patient;
    new_node->next = NULL;
    return new_node;
}

Queue* create_queue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

bool is_empty(Queue* q){
    return (q->head == NULL);
}

void enqueue(Queue* q, Patient patient){
    Node* new_node = create_node(patient);

    if(is_empty(q)){
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

Patient dequeue(Queue* q){
    Patient empty = {-1, "None", 'N'};

    if(is_empty(q)){
        printf("Queue is empty\n");
        return empty;
    }

    Node* temp = q->head;
    Patient patient = temp->data;

    q->head = q->head->next;
    if(q->head == NULL)
        q->tail = NULL;

    free(temp);
    return patient;
}

void print_queue(Queue* q){
    Node* temp = q->head;

    while(temp != NULL){
        printf("[ID:%d Name:%s] -> ", temp->data.id, temp->data.name);
        temp = temp->next;
    }
    printf("NULL\n");
}


// Triage

typedef struct TriageSystem {
    Queue* red;
    Queue* yellow;
    Queue* green;
} TriageSystem;

TriageSystem* create_triage(){
    TriageSystem* system = (TriageSystem*)malloc(sizeof(TriageSystem));
    system->red = create_queue();
    system->yellow = create_queue();
    system->green = create_queue();
    return system;
}

void add_patient(TriageSystem* system, int id, char name[], char priority){
    Patient patient;
    patient.id = id;
    strcpy(patient.name, name);
    patient.priority = priority;

    switch(priority){
        case 'R':
            enqueue(system->red, patient);
            break;
        case 'Y':
            enqueue(system->yellow, patient);
            break;
        case 'G':
            enqueue(system->green, patient);
            break;
        default:
            printf("Invalid priority!\n");
    }
}

Patient treat_next(TriageSystem* system){
    if(!is_empty(system->red))
        return dequeue(system->red);
    else if(!is_empty(system->yellow))
        return dequeue(system->yellow);
    else if(!is_empty(system->green))
        return dequeue(system->green);
    else{
        Patient empty = {-1, "None", 'N'};
        printf("No patients waiting.\n");
        return empty;
    }
}

void display_all(TriageSystem* system){
    printf("\nRED\n");
    print_queue(system->red);

    printf("\nYELLOW\n");
    print_queue(system->yellow);

    printf("\nGREEN\n");
    print_queue(system->green);
}






int main(){
    TriageSystem* system = create_triage();

    add_patient(system, 1, "Alice", 'G');
    add_patient(system, 2, "Bob", 'R');
    add_patient(system, 3, "Charlie", 'Y');
    add_patient(system, 4, "David", 'R');

    display_all(system);

    while(true){
        printf("\nTreating Patient...\n");

        Patient treated = treat_next(system);

        if(treated.id == -1){
            printf("All patients treated.\n");
            break;
        }

        printf("Treated: %s (ID:%d)\n", treated.name, treated.id);
        display_all(system);
    }
    return 0;
}