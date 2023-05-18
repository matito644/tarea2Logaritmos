#include<stdio.h>
#include<stdlib.h>

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
        
        else if (root->izq->num == num)
            root = rightRotate(root);
        
        else if (root->izq->num > num) {
            // Zig
            if (root->izq->izq == NULL)
                root = rightRotate(root);
            // Zig Zig
            else {
                root->izq->izq = splay(root->izq->izq, num);
                root = rightRotate(root);
                root->izq = rightRotate(root->izq);
            }
        }
        
        else if (root->izq->num < num) {
            // Zig
            if (root->izq->der == NULL)
                root = rightRotate(root);
            // Zag Zig
            else {
                root->izq->der = splay(root->izq->der, num);
                root = rightRotate(root);
                root->izq = leftRotate(root->izq);
            }
        }
    }
    else if (root->num < num) {

        if (root->der == NULL)
            return root;

        else if (root->der->num == num)
            root = leftRotate(root);

        else if (root->der->num < num){
            //Zag
            if (root->der->der == NULL)
                root = leftRotate(root);
            else {
                //Zag Zag
                root->der->der = splay(root->der->der, num);
                root = leftRotate(root);
                root->der = leftRotate(root->der);
            }
        }
        else if (root->der->num > num){
            //Zag
            if(root->der->izq == NULL)
                root = leftRotate(root);
            else{
                //Zig Zag
                root->der->izq = splay(root->der->izq, num);
                root = leftRotate(root);
                root->der = rightRotate(root->der);
            }
        }
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

int main() {
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
    preOrder(arbol);
    printf("\n");
    arbol = insert(&arbol, 50);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(arbol);
    printf("\n");
    arbol = insert(&arbol, 200);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(arbol);
    printf("\n");
    arbol = insert(&arbol, 40);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(arbol);
    printf("\n");
    arbol = insert(&arbol, 30);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(arbol);
    printf("\n");
    arbol = insert(&arbol, 20);
    printf("Preorder traversal of the Splay tree is \n");
    preOrder(arbol);
    printf("\n"); 
}