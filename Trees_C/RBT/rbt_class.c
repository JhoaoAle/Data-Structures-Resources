#include <stdio.h>
#include <stdlib.h>

typedef struct NodeRBT{
    int data;
    char color;
    struct NodeRBT *left, *right, *parent;
} NodeRBT;

NodeRBT* create_node(int data){
    NodeRBT* new_node = (NodeRBT*)malloc(sizeof(NodeRBT));
    new_node->data = data;
    new_node->right = new_node->left = new_node->parent = NULL;
    new_node->color = 'R';
    return new_node;
}

NodeRBT* left_rotate(NodeRBT* root, NodeRBT* x){
    if (x == NULL || x->right == NULL) return root;
    NodeRBT* y = x->right;
    NodeRBT* B = y->left;

    NodeRBT* parent_x = x->parent;

    x->right = B;
    if(B != NULL)  B->parent = x;

    y->parent = parent_x;
    if(parent_x == NULL) {
        root = y;
    } else if (x == parent_x->right){
        parent_x->right = y;
    } else {
        parent_x->left = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

NodeRBT* right_rotate(NodeRBT* root, NodeRBT* y){
 if (y == NULL || y->left == NULL) return root;
    NodeRBT* x = y->left;
    NodeRBT* B = x->right;

    NodeRBT* parent_y = y->parent;

    y->left = B;
    if(B != NULL)  B->parent = y;

    x->parent = parent_y;
    if(parent_y == NULL) {
        root = x;
    } else if (y == parent_y->left){
        parent_y->left = x;
    } else {
        parent_y->right = x;
    }
    x->right = y;
    y->parent = x;
    return root;
}

NodeRBT* insert_sentinel(NodeRBT* root, NodeRBT* node_check){
    while(node_check->parent != NULL &&
        node_check->parent->parent != NULL &&
        node_check != root &&
        node_check->parent->color == 'R'
    ){
        NodeRBT* uncle;
        if(node_check->parent == node_check->parent->parent->left){
            uncle = node_check->parent->parent->right;
        } else uncle = node_check->parent->parent->left;
        /*
        Uncle is red.
        1. Parent and uncle turn BLACK
        2. Thus, grandparent node turn RED
        3. Move to grandparent
        */
        if(uncle != NULL && uncle->color == 'R'){
            uncle->color = node_check->parent->color = 'B';
            node_check->parent->parent->color = 'R';
            node_check = node_check->parent->parent;
        } else {
            //Uncle is black
            /*
            A. RR
            i. Swap color parent and grandparent
            ii. Left rotate grandparent
            */
            if(node_check->parent == node_check->parent->parent->right && node_check == node_check->parent->right){
                char color_n = node_check->parent->color;
                node_check->parent->color = node_check->parent->parent->color;
                node_check->parent->parent->color = color_n;
                root = left_rotate(root, node_check->parent->parent);
            }

            /*
            B. LL
            i. Swap color parent and grandparent
            ii. Right rotate grandparent
            */
            else if(node_check->parent == node_check->parent->parent->left && node_check == node_check->parent->left){
                char color_n = node_check->parent->color;
                node_check->parent->color = node_check->parent->parent->color;
                node_check->parent->parent->color = color_n;
                root = right_rotate(root, node_check->parent->parent);
            }

            /*
            C. RL
            i. Swap color parent and grandparent
            ii. Right rotate parent
            ii. Left rotate grandparent
            */
            else if(node_check->parent == node_check->parent->parent->right && node_check == node_check->parent->left){
                char color_n = node_check->parent->color;
                node_check->parent->color = node_check->parent->parent->color;
                node_check->parent->parent->color = color_n;
                root = right_rotate(root, node_check->parent);
                root = left_rotate(root, node_check->parent->parent);
            }

            /*
            D. LR
            i. Swap color parent and grandparent
            ii. Left rotate parent
            ii. Right rotate grandparent
            */
            else if(node_check->parent == node_check->parent->parent->left && node_check == node_check->parent->right){
                char color_n = node_check->parent->color;
                node_check->parent->color = node_check->parent->parent->color;
                node_check->parent->parent->color = color_n;
                root = left_rotate(root, node_check->parent);
                root = right_rotate(root, node_check->parent->parent);
            }
        }
    }
    root->color = 'B';
    return root;
}

NodeRBT* insert_node(NodeRBT* root, int data){
    NodeRBT* new_node = create_node(data);

    if(root == NULL){
        new_node->color = 'B';
        root = new_node;
    } else {
        NodeRBT* temp = NULL;
        NodeRBT* current = root;

        while(current!= NULL){
            temp = current;
            if(data<current->data) current=current->left;
            else if (data>current->data) current=current->right;
            else {
                free(new_node);
                return root;
            }
        }
        new_node->parent = temp;
        if(data < temp->data) temp->left = new_node;
        else if(data > temp->data) temp->right = new_node;
    }

    root = insert_sentinel(root, new_node);
    return root;
}

void in_order(NodeRBT* root){
    if(root == NULL){
        return;
    }
    in_order(root->left);
    printf("%d-%c ", root->data, root->color);
    in_order(root->right);
}

int main(){
    NodeRBT* root = NULL;
    for (int i=0; i<=50; i++){
        root = insert_node(root, i);
    }
    in_order(root);
    printf("\n");
    return 0;
}