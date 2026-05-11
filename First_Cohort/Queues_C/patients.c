#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 50;


typedef struct Patient {
    int id;
    char name[50];
    char priority; // R Y G
} Patient;


typedef struct Node {
    Patient* data;
    struct Node* next;
} Node;





Node* create_node(Patient* value){
    Node* new_Node = (Node *)malloc(sizeof(Node));
    new_Node->data = value;
    new_Node->next = NULL;
    return new_Node;
}

Patient* create_patient(int my_id, char my_name[], char my_priority){
    Patient* new_patient = (Patient *)malloc(sizeof(Patient));
    new_patient->id = my_id;
    strcpy(new_patient->name, my_name);
    new_patient->priority = my_priority;
    return new_patient;
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

void enqueue(Queue* my_queue, Patient* value){
    Node* new_node = create_node(value);
    if(my_queue->head == NULL){
        my_queue->head = my_queue->tail = new_node;
        return;
    } else {
        my_queue->tail->next = new_node;
        my_queue->tail = new_node;
    }
}

Patient* dequeue(Queue* my_queue){
    Patient* invalid_patient = create_patient(-1, "None", 'N');
    if(my_queue->head == NULL){
        printf("Queue is empty\n");
        return invalid_patient;
    }

    Node* temp = my_queue->head;
    Patient* value = my_queue->head->data;

    my_queue->head = my_queue->head->next;

    if(my_queue->head == NULL) my_queue->tail = NULL;
    free(temp);
    return value;
}

Patient* peek(Queue* my_queue){
    Patient* invalid_patient = create_patient(-1, "None", 'N'); 

    if(my_queue->head == NULL){
        printf("Queue is empty\n");
        return invalid_patient;
    }
    return my_queue->head->data;
}

typedef struct Triage {
    Queue* red;
    Queue* yellow;
    Queue* green;
} Triage;

Triage* create_triage(){
    Triage* my_system = (Triage *)malloc(sizeof(Triage));
    my_system->red = create_queue();
    my_system->yellow = create_queue();
    my_system->green = create_queue();
    return my_system;
}

void add_patient(Triage* system, Patient* added_patient){
    switch(added_patient->priority){
        case 'R':
            enqueue(system->red, added_patient);
            break;
        case 'Y':
            enqueue(system->yellow, added_patient);
            break;
        case 'G':
            enqueue(system->green, added_patient);
            break;
        default:
            printf("Invalid priority! \n");
    }
}

Patient* treat_patient(Triage* system){
    if(!is_empty_queue(system->red)){
        return dequeue(system->red);
    }
    else if (!is_empty_queue(system->yellow)){
        return dequeue(system->yellow);
    }
    else if (!is_empty_queue(system->green)){
        return dequeue(system->green);
    }
    else {
        return NULL;
    }
}


void print_queue(Queue* my_queue){
    Node* temp = my_queue->head;
    while(temp!=NULL){
        printf("ID: %d , Name: %s -> \n", temp->data->id, temp->data->name);
        temp = temp->next;
    }
    printf("NULL \n");
}


void display_everything(Triage* system){
    printf("\n RED \n");
    print_queue(system->red);

    printf("\n YELLOW \n");
    print_queue(system->yellow);

    printf("\n GREEN \n");
    print_queue(system->green);
}


int main(){
    Triage* my_triage = create_triage();
    display_everything(my_triage);    
    Patient* patient1 = create_patient(1, "Pepito", 'R');
    Patient* patient2 = create_patient(2, "Pablito", 'Y');
    Patient* patient3 = create_patient(3, "Namehere", 'G');
    Patient* patient4 = create_patient(4, "Ernesto", 'R');

    add_patient(my_triage, patient1);
    add_patient(my_triage, patient2);
    add_patient(my_triage, patient3);
    add_patient(my_triage, patient4);
    display_everything(my_triage); 
    printf("\n -- Patients treated -- \n");
    while(true){
        Patient* patient_to_treat;
        patient_to_treat = treat_patient(my_triage);
        if(patient_to_treat == NULL) break;
        printf("Name: %s , Id: %d \n", patient_to_treat->name,      patient_to_treat->id);
    }
    display_everything(my_triage); 

    return 0;
}