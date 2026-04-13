#include <stdio.h>
#include <stdlib.h>

typedef struct NodeRBT{
    int data;
    char color;

    struct NodeRBT *left, *right, *parent;
} NodeRBT;

// Global NIL node (all leaves point to this instead of NULL)
NodeRBT *NIL;

// Initialize NIL node
void initNIL(){
    NIL = (NodeRBT*)malloc(sizeof(NodeRBT));
    NIL->color = 'B';
    NIL->left = NIL->right = NIL->parent = NIL;
}

// Create new node
NodeRBT* CreateNode(int data){
    NodeRBT* newNode = (NodeRBT*)malloc(sizeof(NodeRBT));
    newNode->data = data;

    //CHANGE DUE TO NIL:
    // Instead of NULL, children point to NIL
    newNode->left = newNode->right = NIL;
    newNode->parent = NIL;

    newNode->color = 'R';
    return newNode;
}

NodeRBT* LeftRotate(NodeRBT *root, NodeRBT *x){
    NodeRBT* y = x->right;

    x->right = y->left;
    if(y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if(x->parent == NIL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

NodeRBT* RightRotate(NodeRBT *root, NodeRBT *y){
    NodeRBT* x = y->left;

    y->left = x->right;
    if(x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if(y->parent == NIL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

NodeRBT* InsertFixer(NodeRBT* root, NodeRBT* check_node){
    while(check_node->parent->color == 'R'){
        NodeRBT* uncle;

        if(check_node->parent == check_node->parent->parent->left)
            uncle = check_node->parent->parent->right;
        else
            uncle = check_node->parent->parent->left;

        // Possible scenarios when there is a violation:
        //1. Uncle is RED, thus:
        // (i) Change color of parent and uncle as BLACK
        // (ii) Grandparent becomes RED to preserve black height
        // (iii) Move up the tree and continue checking
        if(uncle->color == 'R'){
            check_node->parent->color = 'B';
            uncle->color = 'B';
            check_node->parent->parent->color = 'R';
            check_node = check_node->parent->parent;
        }
        else{
            //1. Uncle is BLACK, thus rotations are needed:

            // A. LL
            // (i) Swap colors of parent and grandparent
            // (ii) Right rotate grandparent
            if(check_node->parent == check_node->parent->parent->left &&
               check_node == check_node->parent->left){
                char temp = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = temp;

                root = RightRotate(root, check_node->parent->parent);
            }

            // B. LR
            // (i) Left rotate parent
            // (ii) Convert to LL case
            else if(check_node->parent == check_node->parent->parent->left &&
                    check_node == check_node->parent->right){
                check_node = check_node->parent;
                root = LeftRotate(root, check_node);

                // Now falls into LL
                char temp = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = temp;

                root = RightRotate(root, check_node->parent->parent);
            }

            // C. RR
            // (i) Swap colors of parent and grandparent
            // (ii) Left rotate grandparent
            else if(check_node->parent == check_node->parent->parent->right &&
                    check_node == check_node->parent->right){
                char temp = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = temp;

                root = LeftRotate(root, check_node->parent->parent);
            }

            // D. RL
            // (i) Right rotate parent
            // (ii) Convert to RR case
            else if(check_node->parent == check_node->parent->parent->right &&
                    check_node == check_node->parent->left){
                check_node = check_node->parent;
                root = RightRotate(root, check_node);

                // Now falls into RR
                char temp = check_node->parent->color;
                check_node->parent->color = check_node->parent->parent->color;
                check_node->parent->parent->color = temp;

                root = LeftRotate(root, check_node->parent->parent);
            }
        }
    }

    // Root must always remain BLACK
    root->color = 'B';
    return root;
}

NodeRBT* InsertRBT(NodeRBT* root, int data){
    NodeRBT* z = CreateNode(data);
    NodeRBT* y = NIL;
    NodeRBT* x = root;

    // Loop continues while x != NIL (not NULL anymore)
    while(x != NIL){
        y = x;
        if(z->data < x->data)
            x = x->left;
        else if(z->data > x->data)
            x = x->right;
        else{
            free(z);
            return root;
        }
    }

    z->parent = y;

    if(y == NIL)
        root = z;
    else if(z->data < y->data)
        y->left = z;
    else
        y->right = z;

    root = InsertFixer(root, z);
    return root;
}

NodeRBT* Minimum(NodeRBT* node){
    while(node->left != NIL)
        node = node->left;
    return node;
}

NodeRBT* Transplant(NodeRBT* root, NodeRBT* u, NodeRBT* v){
    // Replaces subtree rooted at u with subtree rooted at v
    // (i) Update parent of u to point to v
    // (ii) Update parent pointer of v

    if(u->parent == NIL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;

    return root;
}

NodeRBT* DeleteFixer(NodeRBT* root, NodeRBT* x){
    while(x != root && x->color == 'B'){

        NodeRBT* sibling;

        if(x == x->parent->left){
            sibling = x->parent->right;

            // Possible scenarios when there is a violation:
            //1. Sibling is RED, thus:
            // (i) Recolor sibling and parent
            // (ii) Rotate to convert into BLACK sibling case
            if(sibling->color == 'R'){
                sibling->color = 'B';
                x->parent->color = 'R';
                root = LeftRotate(root, x->parent);
                sibling = x->parent->right;
            }

            //2. Sibling is BLACK with both children BLACK:
            // (i) Recolor sibling RED
            // (ii) Move problem up to parent
            if(sibling->left->color == 'B' && sibling->right->color == 'B'){
                sibling->color = 'R';
                x = x->parent;
            }
            else{
                //3. Sibling is BLACK, far child BLACK, near child (closest Sibling child from node) RED:
                // (i) Rotate sibling to convert into final case
                if(sibling->right->color == 'B'){
                    sibling->left->color = 'B';
                    sibling->color = 'R';
                    root = RightRotate(root, sibling);
                    sibling = x->parent->right;
                }

                //4. Sibling is BLACK and far child (farthest Sibling child from node) RED:
                // (i) Recolor sibling with parent color
                // (ii) Make parent BLACK
                // (iii) Rotate parent and fix violation
                sibling->color = x->parent->color;
                x->parent->color = 'B';
                sibling->right->color = 'B';

                root = LeftRotate(root, x->parent);
                x = root;
            }
        }
        else{
            sibling = x->parent->left;

            if(sibling->color == 'R'){
                sibling->color = 'B';
                x->parent->color = 'R';
                root = RightRotate(root, x->parent);
                sibling = x->parent->left;
            }

            if(sibling->right->color == 'B' && sibling->left->color == 'B'){
                sibling->color = 'R';
                x = x->parent;
            }
            else{
                if(sibling->left->color == 'B'){
                    sibling->right->color = 'B';
                    sibling->color = 'R';
                    root = LeftRotate(root, sibling);
                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = 'B';
                sibling->left->color = 'B';

                root = RightRotate(root, x->parent);
                x = root;
            }
        }
    }

    // Final step: ensure x is BLACK
    x->color = 'B';
    return root;
}


NodeRBT* DeleteRBT(NodeRBT* root, int key){
    NodeRBT* z = root;

    //1. Locate node to delete
    while(z != NIL){
        if(key < z->data) z = z->left;
        else if(key > z->data) z = z->right;
        else break;
    }

    if(z == NIL) return root;

    NodeRBT* y = z;
    char y_original_color = y->color;
    NodeRBT* x;

    //2. Perform standard BST deletion
    // Case A: Node has at most one child
    if(z->left == NIL){
        x = z->right;
        root = Transplant(root, z, z->right);
    }
    else if(z->right == NIL){
        x = z->left;
        root = Transplant(root, z, z->left);
    }
    else{
        // Case B: Node has two children
        // (i) Find successor
        // (ii) Replace node with successor
        y = Minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if(y->parent == z){
            x->parent = y;
        }
        else{
            root = Transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        root = Transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    //3. Fix violations only if a BLACK node was removed
    if(y_original_color == 'B')
        root = DeleteFixer(root, x);

    return root;
}

void inorder(NodeRBT* root){
    if(root == NIL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(){
    initNIL();

    NodeRBT* root = NIL;

    root = InsertRBT(root,10);
    root = InsertRBT(root,20);
    root = InsertRBT(root,40);
    root = InsertRBT(root,30);
    root = InsertRBT(root,50);
    root = InsertRBT(root,35);
    root = InsertRBT(root,25);
    root = InsertRBT(root,37);

    root = DeleteRBT(root,40);
    root = DeleteRBT(root,25);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}