#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *left_child, *right_child;
} Node;

typedef struct BST{
    Node* root;
} BST;

Node* create_node(int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->left_child = new_node->right_child = NULL;
    return new_node;
}

BST* create_tree(){
    BST* my_tree = (BST*)malloc(sizeof(BST));
    my_tree->root = NULL;
    return my_tree;
}

Node* search_node(Node* root_node, int target){
    if(root_node == NULL || root_node->data == target){
        return root_node;
    }
    if(root_node->data < target) return search_node(root_node->right_child, target);
    return search_node(root_node->left_child, target);
}

Node* find_rightmost(Node* root_node){
    if(root_node == NULL || root_node->right_child == NULL){
        return root_node;
    }
    return find_rightmost(root_node->right_child);
}

Node* find_leftmost(Node* root_node){
    if(root_node == NULL || root_node->left_child == NULL){
        return root_node;
    }
    return find_leftmost(root_node->left_child);
}

Node* find_predecessor(Node* root_node){
    if(root_node == NULL || root_node->left_child == NULL){
        return NULL;
    }
    return find_rightmost(root_node->left_child);
}

Node* find_successor(Node* root_node){
    if(root_node == NULL || root_node->right_child == NULL){
        return NULL;
    }
    return find_leftmost(root_node->right_child);
}

void insert_node(BST* my_tree, int value){
    Node* new_node = create_node(value);
    if(my_tree->root == NULL){
        my_tree->root = new_node;
        return;
    }
    Node* temp = my_tree->root;
    Node* parent = NULL;
    while(temp != NULL){
        parent = temp;
        if(value < temp->data){
            temp = temp->left_child;
        } else {
            temp = temp->right_child;
        }
    }

    if(value < parent->data) {
        parent->left_child = new_node;
    } else {
        parent->right_child = new_node;
    }
}

Node* insert_recursive(Node* root, int value){
    if(root == NULL) return create_node(value);

    if(value < root->data){
        root->left_child = insert_recursive(root->left_child, value);
    } else {
        root->right_child = insert_recursive(root->right_child, value);
    }

    return root;
}

void insert_node_r(BST* tree, int value){
    tree->root = insert_recursive(tree->root, value);
}


void delete_node(BST* my_tree, int value){
    if(my_tree->root == NULL){
        return;
    }
    Node* temp = my_tree->root;
    Node* parent = NULL;
    while(temp != NULL && temp->data != value){
        parent = temp;
        if(value < temp->data){
            temp = temp->left_child;
        } else {
            temp = temp->right_child;
        }
    }
    if (temp == NULL ) return;

    // If the node has two child nodes
    if(temp->left_child != NULL && temp->right_child != NULL){
        Node* predecessor_parent = temp;
        Node* predecessor_node = temp->left_child;
        while(predecessor_node->right_child != NULL){
            predecessor_parent = predecessor_node;
            predecessor_node = predecessor_node -> right_child;
        }
        temp->data = predecessor_node->data;
        temp = predecessor_node;
        parent = predecessor_parent;
    }

    //If the node only has one child node...
    Node* child_node = (temp->left_child != NULL) ? temp->left_child : temp->right_child;

    //It could be the root
    if(parent == NULL){
        my_tree->root = child_node;
    } else if (parent->left_child == temp){
        parent->left_child = child_node;
    } else {
        parent->right_child = child_node;
    }
    free(temp);
}

void in_order(Node* root){
    if(root){
        in_order(root->left_child);
        printf("%d ", root->data);
        in_order(root->right_child);
    }
}

void free_tree(Node* root){
    if(root){
        free_tree(root->left_child);
        free_tree(root->right_child);
        free(root);
    }
}

int main(){
    BST* tree = create_tree();

    // Insert values
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values)/sizeof(values[0]);

    printf("Inserting values:\n");
    for(int i = 0; i < n; i++){
        insert_node(tree, values[i]);
        printf("%d ", values[i]);
    }

    printf("\n\nIn-order traversal (should be sorted):\n");
    in_order(tree->root);
    printf("\n");

    // Search test
    int target = 40;
    Node* found = search_node(tree->root, target);
    if(found){
        printf("\nFound node with value: %d\n", found->data);
    } else {
        printf("\nValue %d not found\n", target);
    }

    // Test predecessor & successor
    Node* node = search_node(tree->root, 50);
    if(node){
        Node* pred = find_predecessor(node);
        Node* succ = find_successor(node);

        if(pred)
            printf("Predecessor of %d: %d\n", node->data, pred->data);
        else
            printf("No predecessor for %d\n", node->data);

        if(succ)
            printf("Successor of %d: %d\n", node->data, succ->data);
        else
            printf("No successor for %d\n", node->data);
    }

    // Delete tests
    printf("\nDeleting 20 (leaf node)...\n");
    delete_node(tree, 20);
    in_order(tree->root);
    printf("\n");

    printf("\nDeleting 30 (one child)...\n");
    delete_node(tree, 30);
    in_order(tree->root);
    printf("\n");

    printf("\nDeleting 50 (two children, root)...\n");
    delete_node(tree, 50);
    in_order(tree->root);
    printf("\n");

    // Free memory
    free_tree(tree->root);
    free(tree);
    return 0;
}