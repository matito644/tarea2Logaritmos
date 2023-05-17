#include<stdio.h>
#include<stdlib.h>

struct node {
    int num;
    struct node *izq, *der;
};

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
        
        if (root->izq->num > num) {
            // Zig
            if (root->izq->izq == NULL)
                root = rightRotate(root);
            // Zig Zig
            else {
                root->izq->izq = splay(root->izq->izq, num);
                root->izq = rightRotate(root->izq);
                root = rightRotate(root);
            }
        }
        
        else if (root->izq->num < num) {
            // Zig
            if (root->izq->der == NULL)
                root = rightRotate(root);
            // Zag Zig
            else {
                root->izq->der = splay(root->izq->der, num);
                root->izq = leftRotate(root->izq);
                root = rightRotate(root);
            }
        }
    }
    else if (root->num < num) {

        if (root->der == NULL)
            return root;

        if (root->der->num < num){
            //Zag
            if (root->der->der == NULL)
                root = leftRotate(root);
            else {
                //Zag Zag
                root->der->der = splay(root->der->der, num);
                root->der = leftRotate(root->der);
                root = leftRotate(root);
            }
        }
        else if (root->der->num > num){
            //Zag
            if(root->der->izq == NULL)
                root = leftRotate(root);
            else{
                //Zig Zag
                root->der->izq = splay(root->der->izq, num);
                root->der = rightRotate(root->der);
                root = leftRotate(root);
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

struct node *insert(struct node *root, int num) {
    insert_ABB(root, num);
    return splay(root, num);
}

void insert_ABB(struct node *root, int num) {
    if (root==NULL) {
        root = createNode(num);
        return;
    }
    else if (num < root->num) {
        insert_ABB(root->izq, num);
        return;
    }
    else if (num > root->num) {
        insert_ABB(root->der, num);
        return;
    }
}

struct node *delete(struct node* root, int num) {
    struct node *father = search_ABB_father(root, num);
    delete_ABB(father, num);
    return splay(root, father->num);
}

struct node *search_ABB_father(struct node* root, int num) {
    if (root->izq == NULL && root->der == NULL) {
        return;
    }
}

void delete_ABB(root, num) {
}

int main() {
    
}