#pragma once

typedef struct snode {
    int val;
    struct snode *left, *right, *parent;
} sNode;

class SplayTree {
public:
  sNode *root;

  SplayTree();
  sNode *getRoot();
  void splay(sNode *root);
  sNode *search(sNode *root, int val);
  void insert(sNode *node);
  void leftRotate(sNode *p);
  void rightRotate(sNode *p);
};

void printCuteSplay(sNode *root, string sep, bool wasItRight);
sNode *createSplayTreeNode(int val);

void megaFree(sNode *root);
