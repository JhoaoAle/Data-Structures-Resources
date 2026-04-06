 #include <stdio.h>
#include <stdlib.h>

/*
    Definition of an AVL Tree node.
    Each node stores:
    - key: the value
    - left/right: child pointers
    - height: height of the node for balancing
*/
struct NodeAVL
{
    int key;
    struct NodeAVL *left;
    struct NodeAVL *right;
    int height;
};

/*
    Returns the height of a node.
    If the node is NULL, height is 0.
*/
int height(struct NodeAVL *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

/*
    Returns the maximum of two integers.
*/
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/*
    Computes the balance factor of a node.
    Balance = height(left subtree) - height(right subtree)

    Possible values:
    > 1  : left heavy
    < -1 : right heavy
    -1,0,1 : balanced
*/
int getBalance(struct NodeAVL *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*
    Creates a new AVL node with a given key.
    Initial height is 1 (leaf node).
*/
struct NodeAVL* newNodeAVL(int key)
{
    struct NodeAVL* node = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

/*
    Performs a right rotation on subtree rooted at y.

           y                             x
          / \                           / \
         x   T3      ---->             T1  y
        / \                               / \
       T1  T2                            T2 T3
*/
struct NodeAVL *rightRotate(struct NodeAVL *y)
{
    struct NodeAVL *x = y->left;
    struct NodeAVL *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights after rotation
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

/*
    Performs a left rotation on subtree rooted at x.

         x                              y
        / \                            / \
       T1  y        ---->             x  T3
          / \                        / \
         T2 T3                      T1 T2
*/
struct NodeAVL *leftRotate(struct NodeAVL *x)
{
    struct NodeAVL *y = x->right;
    struct NodeAVL *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights after rotation
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

/*
    Inserts a key into the AVL tree and rebalances it if necessary.
*/
struct NodeAVL* insertAVL(struct NodeAVL* node, int key)
{
    // Step 1: Perform standard BST insertion
    if (node == NULL)
        return newNodeAVL(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; // Duplicate keys not allowed

    // Step 2: Update height of this node
    node->height = 1 + max(height(node->left), height(node->right));

    // Step 3: Check balance factor
    int balance = getBalance(node);

    // Step 4: Perform rotations if unbalanced

    // Case 1: Left Left (LL)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Case 2: Right Right (RR)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Case 3: Left Right (LR)
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Case 4: Right Left (RL)
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*
    Finds the node with the minimum key in a subtree.
    This is the leftmost node.
*/
struct NodeAVL *minValueNodeAVL(struct NodeAVL* node)
{
    struct NodeAVL* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

/*
    Deletes a key from the AVL tree and rebalances it.
*/
struct NodeAVL* deleteNodeAVL(struct NodeAVL* root, int key)
{
    // Step 1: Perform standard BST deletion
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNodeAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNodeAVL(root->right, key);
    else
    {
        // Node with one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct NodeAVL *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                // One child case: copy child contents
                *root = *temp;
            }

            free(temp);
        }
        else
        {
            // Node with two children:
            // Get inorder successor (smallest in right subtree)
            struct NodeAVL* temp = minValueNodeAVL(root->right);

            // Copy successor's value
            root->key = temp->key;

            // Delete successor
            root->right = deleteNodeAVL(root->right, temp->key);
        }
    }

    // If tree had only one node
    if (root == NULL)
        return root;

    // Step 2: Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Step 3: Check balance
    int balance = getBalance(root);

    // Step 4: Rebalance if necessary

    // Case 1: Left Left (LL)
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Case 2: Left Right (LR)
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 3: Right Right (RR)
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Case 4: Right Left (RL)
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/*
    Preorder traversal: Root -> Left -> Right
*/
void preOrderAVL(struct NodeAVL *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrderAVL(root->left);
        preOrderAVL(root->right);
    }
}

/*
    Main function to test AVL operations.
*/
int main()
{
    struct NodeAVL *rootAVL = NULL;

    // Insert elements
    rootAVL = insertAVL(rootAVL, 10);
    rootAVL = insertAVL(rootAVL, 20);
    rootAVL = insertAVL(rootAVL, 30);
    rootAVL = insertAVL(rootAVL, 40);
    rootAVL = insertAVL(rootAVL, 50);
    rootAVL = insertAVL(rootAVL, 25);

    // Delete an element
    rootAVL = deleteNodeAVL(rootAVL, 40);

    // Print preorder traversal
    preOrderAVL(rootAVL);

    return 0;
}