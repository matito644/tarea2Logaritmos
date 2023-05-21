#pragma once

typedef struct node {
    int val;
    bool color;
    struct node *left, *right, *parent;
} treeNode;

class RedBlackTree {
public:
  treeNode *root;

  RedBlackTree();
  treeNode *getRoot();
  void insert(treeNode *node);
  void leftRotate(treeNode *p);
  void rightRotate(treeNode *p);
};

void printCute(treeNode *root, string sep);
treeNode *createNode(int val);
treeNode *search(treeNode *root, int val);

void megaFree(treeNode *root);
