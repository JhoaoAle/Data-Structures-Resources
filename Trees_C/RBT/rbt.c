#include <stdio.h>
#include <stdlib.h>

typedef struct NodeRBT{
    int data;
    char color;

    struct NodeRBT *left, *right, *parent;
} NodeRBT;

NodeRBT* CreateNode(int data){
    NodeRBT* newNode = (NodeRBT*)malloc(sizeof(NodeRBT));
    newNode->data = data;
    newNode -> left = newNode ->right = newNode ->parent = NULL;
    newNode->color = 'R';
    return newNode;
}

NodeRBT* LeftRotate (NodeRBT *root, NodeRBT *x){
    
    if (x == NULL || x->right == NULL) return root;

    NodeRBT* y = x->right;
    NodeRBT* B = y->left;
    NodeRBT* parent_x = x->parent;

    x->right =  B;

    if(B != NULL) B->parent = x;

    y->parent = parent_x;
    if(parent_x == NULL){
        root = y;
    } else if(x == parent_x->left) {
        parent_x->left = y;
    } else {
        parent_x->right = y;
    }
     

    y->left = x;
    x->parent = y;

    return root;
}

NodeRBT* RightRotate (NodeRBT *root, NodeRBT *y){
    
    if (y == NULL || y->left == NULL) return root;

    NodeRBT* x = y->left;
    NodeRBT* B = x->right;
    NodeRBT* parent_y = y->parent;

    y->left =  B;

    if(B != NULL) B->parent = y;

    x->parent = parent_y;
    if(parent_y == NULL){
        root = x;
    } else if(y == parent_y->left) {
        parent_y->left = x;
    } else {
        parent_y->right = x;
    }
     
    x->right = y;
    y->parent = x;

    return root;
}

NodeRBT* InsertFixer( NodeRBT* root, NodeRBT* check_node){
    while(check_node->parent !=NULL &&
        check_node->parent->parent !=NULL &&
        check_node != root && 
        check_node->parent->color == 'R'
        ){
        NodeRBT* uncle;
        if (check_node->parent == check_node->parent->parent->left) uncle = check_node->parent->parent->right;
        else uncle = check_node->parent->parent->left;

        // Possible scenarios when there is a violation:
        //1. Uncle is RED, thus:
        // (i) Change color of parent and uncle as BLACK
        // (ii) This means grandparent has to be RED to preserve black height property
        // (iii) Now we move on to grandparent
        if(uncle != NULL && uncle->color == 'R'){
            uncle->color = 'B';
            check_node->parent->color = 'B';
            check_node->parent->parent->color = 'R';
            check_node = check_node->parent->parent;
        }

        else {
            //1. Uncle is BLACK, thus:
            // A. LL
            // (i) Swap color of parent and grandparent
            // (ii) Right rotate grandparent
            if(check_node->parent == check_node->parent->parent->left && check_node->parent->left == check_node){// Parent and check node are left children
                char color_n = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = color_n;
                root = RightRotate(root, check_node->parent->parent);
            }

            // B. LR
            // (i) Swap colors of current node and grandparent
            // (ii) Left rotate parent
            // (iii) Right rotate grandparent
            else if(check_node->parent == check_node->parent->parent->left && check_node->parent->right == check_node){// Parent is left child and check node is right child
                char color_n = check_node->color;
                check_node->color = check_node->parent->parent->color;
                check_node->parent->parent->color = color_n;
                root = LeftRotate(root, check_node->parent);
                root = RightRotate(root, check_node->parent->parent);
            }
            
            // C. RR
            // (i) Swap color of parent and grandparent
            // (ii) Left rotate grandparent
            else if(check_node->parent == check_node->parent->parent->right && check_node->parent->right == check_node){// Parent and check node are right children
                char color_n = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = color_n;
                root = LeftRotate(root, check_node->parent->parent);
            }

            // D. RL
            // (i) Swap colors of current node and grandparent
            // (ii) Right rotate parent
            // (iii) Left rotate grandparent
            else if(check_node->parent == check_node->parent->parent->right && check_node->parent->left == check_node){// Parent is right child and check node is left child
                char color_n = check_node->color;
                check_node->color = check_node->parent->parent->color;
                check_node->parent->parent->color = color_n;
                root = RightRotate(root, check_node->parent);
                root = LeftRotate(root, check_node->parent->parent);
            }
        }
    }
    root ->color = 'B';
    return root;
}


NodeRBT* InsertRBT(NodeRBT* root, int data){
    NodeRBT* newNode = CreateNode(data);

    if (root == NULL){
        newNode ->color = 'B';
        root = newNode;
    } else {
        NodeRBT* temp = NULL;
        NodeRBT* current = root;

        while(current!= NULL){
            temp = current;
            if (data < current->data) current = current->left;
            else if (data > current->data) current = current->right;
            else{
                free(newNode);
                return root;
            } 
        }
        newNode->parent = temp;
        if (data < temp->data) temp->left = newNode;
        else if (data > temp->data) temp->right = newNode;
    }
    root = InsertFixer(root, newNode);
    return root;

}

void inorder(NodeRBT* root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(){
    NodeRBT *root = NULL;
    root = InsertRBT(root,10);
    root = InsertRBT(root,20);
    root = InsertRBT(root,40);
    root = InsertRBT(root,30);
    root = InsertRBT(root,50);
    root = InsertRBT(root,35);
    root = InsertRBT(root,25);
    root = InsertRBT(root,37);
    printf("inorder Traversal Is : ");
    inorder(root);
    printf("\n");
    return 0;
}