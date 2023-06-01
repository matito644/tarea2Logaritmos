#include<stdio.h>
#include<stdlib.h>
#define COUNT 5

struct node {
    int num;
    struct node *izq, *der;
};

void insert_ABB(struct node **root, int num);

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */

struct node* createNode(int num) {
    struct node* newNode = (struct node*) (malloc(sizeof(struct node)));
    newNode->num = num;
    newNode->izq = NULL;
    newNode->der = NULL;
    return newNode;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.

struct node *rightRotate(struct node *x) {
    struct node *y = x->izq;
    x->izq = y->der;
    y->der = x;
    return y;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.

struct node *leftRotate(struct node *x) {
    struct node *y = x->der;
    x->der = y->izq;
    y->izq = x;
    return y;
}

// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root.  This function modifies the tree and returns the new root

struct node *splay(struct node *root, int num) {
    
    if (root==NULL || root->num == num) 
        return root;
    
    if (root->num > num) {
        
        if (root->izq == NULL)
            return root;
        
        else if (root->izq->num > num) {
            root->izq->izq = splay(root->izq->izq, num);
            root = rightRotate(root);    
        }
        
        else if (root->izq->num < num) {
            root->izq->der = splay(root->izq->der, num);
            if (root->izq->der != NULL)
                root->izq = leftRotate(root->izq);
        }

        if (root->izq != NULL)
            root = rightRotate(root);

    }
    else if (root->num < num) {

        if (root->der == NULL)
            return root;

        else if (root->der->num < num){
            root->der->der = splay(root->der->der, num);
            root = leftRotate(root);
        }
        else if (root->der->num > num){
            root->der->izq = splay(root->der->izq, num);
            if (root->der->izq != NULL)
                root->der = rightRotate(root->der);
        }

        if (root->der != NULL)
            root = leftRotate(root);

    }

    return root;

}

// The search function for Splay tree.  Note that this function
// returns the new root of Splay Tree.  If key is present in tree
// then, it is moved to root.

struct node *search(struct node *root, int num) {
    return splay(root, num);
}

// The insert function for Splay tree.  Note that this function
// returns the new root of Splay Tree.  If key is present in tree
// then, it is moved to root.

struct node *insert(struct node **root, int num) {
    insert_ABB(root, num);
    return splay(*root, num);
}

void insert_ABB(struct node **root, int num) {
    if (*root==NULL) {
        *root = createNode(num);
        return;
    }
    else if (num < (*root)->num) {
        insert_ABB(&(*root)->izq, num);
        return;
    }
    else if (num > (*root)->num) {
        insert_ABB(&(*root)->der, num);
        return;
    }
}

void preOrder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->num);
        preOrder(root->izq);
        preOrder(root->der);
    }
}

void print2D(struct node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void print2DUtil(struct node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->der, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->num);
 
    // Process left child
    print2DUtil(root->izq, space);
}

/* int main() {
    struct node *root = createNode(100);
    root->izq = createNode(50);
    root->der = createNode(200);
    root->izq->izq = createNode(40);
    root->izq->izq->izq = createNode(30);
    root->izq->izq->izq->izq = createNode(20);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(root);
    printf("\n");
    
    struct node* arbol= NULL;
    arbol = insert(&arbol, 100);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n");
    arbol = insert(&arbol, 50);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n");
    arbol = insert(&arbol, 200);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n");
    arbol = insert(&arbol, 40);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n");
    arbol = insert(&arbol, 30);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n");
    arbol = insert(&arbol, 20);
    printf("Preorder traversal of the Splay tree is \n");
    print2D(arbol);
    printf("\n"); 
} */