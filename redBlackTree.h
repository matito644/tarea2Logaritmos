#pragma once

typedef struct rbnode {
    int val;
    bool color;
    struct rbnode *left, *right, *parent;
} rbNode;

class RedBlackTree {
public:
  rbNode *root;

  RedBlackTree();
  rbNode *getRoot();
  void insert(rbNode *node);
  void leftRotate(rbNode *p);
  void rightRotate(rbNode *p);
};

void printCute(rbNode *root, string sep);
rbNode *createRedBlackTreeNode(int val);
rbNode *search(rbNode *root, int val);

void megaFree(rbNode *root);
