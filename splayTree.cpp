#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "splayTree.h"

SplayTree::SplayTree() {
  this->root = nullptr;
}

sNode *SplayTree::getRoot() {
  return this->root;
}

void SplayTree::insert(sNode *node) {
  sNode *aux = nullptr;
  sNode *where = this->root;
  // ir buscando en donde tiene que ir
  while (where != nullptr) {
    aux = where;
    if (node->val > where->val) {
      where = where->right;
    } else {
      where = where->left;
    }
  }

  node->parent = aux;
  // puede no haber entrado al while, por lo que ahora node es la raiz
  if (aux == nullptr) {
    // raiz siempre es negra
    this->root=node;
    return;
  } else {
    if (node->val > aux->val) {
      aux->right = node;
    } else {
      aux->left = node;
    }
  }
  // llevarlo a la raiz
  splay(node);
}

// pRight va a quedar en la posicion de p
void SplayTree::leftRotate(sNode *p) {
  sNode *pRight = p->right;
  // solo si pRight no era una hoja
  if (pRight != nullptr) {
    p->right = pRight->left;
    // fijar p como padre de pRight->left si es que existia dicho nodo
    if (pRight->left != nullptr) {
      pRight->left->parent = p;
    }
    // como pRight ahora ocupa la posicion de p, hay que fijar su padre como el
    // padre de p
    pRight->parent = p->parent;
    // fijar pRight como el padre de p y p como el hijo izquiero de pRight
    p->parent = pRight;
    pRight->left = p;
    // si p era la raiz ahora pRight lo es
    if (pRight->parent == nullptr) {
      this->root = pRight;
    }
    // falta fijar el pRight como el nuevo hijo de el antiguo padre de p
    // si p solia ser el hijo derecho de su padre
    else if (p == pRight->parent->right) {
      pRight->parent->right = pRight;
    }
    // si solia ser el hijo izquierdo
    else {
      pRight->parent->left = pRight;
    }
  }
}

// pLeft va a quedar en la posicion de p
void SplayTree::rightRotate(sNode *p) {
  sNode *pLeft = p->left;
  // solo si pLeft no era una hoja
  if (pLeft != nullptr) {
    p->left = pLeft->right;
    // fijar p como padre de pLeft->right si es que existia dicho nodo
    if (pLeft->right != nullptr) {
      pLeft->right->parent = p;
    }
    // como pLeft ahora ocupa la posicion de p, hay que fijar su padre como el
    // padre de p
    pLeft->parent = p->parent;
    // fijar pRight como el padre de p y p como el hijo izquiero de pLeft
    p->parent = pLeft;
    pLeft->right = p;
    // si p era la raiz ahora pLeft lo es
    if (pLeft->parent == nullptr) {
      this->root = pLeft;
    }
    // falta fijar el pLeft como el nuevo hijo de el antiguo padre de p
    // si p solia ser el hijo derecho de su padre
    else if (p == pLeft->parent->right) {
      pLeft->parent->right = pLeft;
    }
    // si solia ser el hijo izquierdo
    else {
      pLeft->parent->left = pLeft;
    }
  }
}

void SplayTree::splay(sNode *root){
  // mientras no se llegue a la raiz
  while (root->parent != nullptr) {
    // si mi padre es la raiz (rotaciones unitarias)
    if (root->parent->parent == nullptr) {
      // si root era el hijo derecho, rota a la izquierda, si no, a la derecha
      if (root == root->parent->right) {
        // zig
        leftRotate(root->parent);
      } else {
        // zag
        rightRotate(root->parent);
      }
    } else { // rotaciones dobles
      if (root == root->parent->left && root->parent == root->parent->parent->left) {
        // si root es el hijo izquierdo y su padre es el hijo izquierdo de su padre
        // zig-zig
        rightRotate(root->parent->parent);
        rightRotate(root->parent);
      } else if (root == root->parent->right && root->parent == root->parent->parent->left) {
        // si root es el hijo derecho y su padre es el hijo izquierdo de su padre
        // zig-zag
        leftRotate(root->parent);
        rightRotate(root->parent);
      } else if (root == root->parent->right && root->parent == root->parent->parent->right) {
        // si root es el hijo derecho y su padre es el hijo derecho de su padre
        // zag-zag
        leftRotate(root->parent->parent);
        leftRotate(root->parent);
      } else {
        // si root es el hijo izquierdo y su padre es el hijo derecho de su padre
        // zag-zig
        rightRotate(root->parent);
        leftRotate(root->parent);
      }
    }
  }
}

sNode *SplayTree::search(sNode *root, int val) {
  // mientras no llegue a una hoja
  while (root != nullptr) {
    // si era el que estoy buscando, hago el splay y lo retorno
    if (root->val == val) {
      splay(root);
      return root;
    }
    // si busco uno menor, lo busco en el subarbol izquierdo
    if (root->val > val) {
      root = root->left;
    } else { // si no, en el derecho
      root = root->right;
    }
  }
  // si no estaba, retorno nullptr
  return nullptr;
}

void printCuteSplay(sNode *root, string sep, bool wasItRight) {
  if (root != NULL) {
    cout << sep;
    if (wasItRight) {
      cout << "R-> ";
    } else {
      cout << "L-> ";
    }
    sep += "    ";
    cout << "nodo: " << root->val << endl;
    printCuteSplay(root->left, sep, 0);
    printCuteSplay(root->right, sep, 1);
  }
}

sNode *createSplayTreeNode(int val) {
  sNode *newNode = (sNode *)malloc(sizeof(sNode));
  newNode->val = val;
  newNode->left = newNode->right = newNode->parent = nullptr;
  return newNode;
}

void megaFree(sNode *root) {
  if (root != nullptr) {
    sNode *left = root->left;
    sNode *right = root->right;
    free(root);
    megaFree(left);
    megaFree(right);
  }
}

// int main() {
// 	SplayTree tree;
//   sNode *node1 = createSplayTreeNode(100);
//   sNode *node2 = createSplayTreeNode(50);
//   sNode *node3 = createSplayTreeNode(200);
//   sNode *node4 = createSplayTreeNode(40);
//   tree.insert(node1);
//   tree.insert(node2);
//   tree.insert(node3);
//   tree.insert(node4);
// 	printCuteSplay(tree.getRoot(), "", 1);
//   tree.search(tree.getRoot(), 50);
//   printCuteSplay(tree.getRoot(), "", 1);
// 	return 0;
// }
