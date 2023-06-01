#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "redBlackTree.h"

RedBlackTree::RedBlackTree() {
  this->root = nullptr;
}

rbNode *RedBlackTree::getRoot() {
  return this->root;
}

void RedBlackTree::insert(rbNode *node) {
  rbNode *aux = nullptr;
  rbNode *where = this->root;
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
    node->color = 0;
    this->root=node;
    return;
  } else {
    if (node->val > aux->val) {
      aux->right = node;
    } else {
      aux->left = node;
    }
  }

  rbNode *aux2;
  // si el arbol solo tiene una raiz se retorno antes
  // si el arbol solo tiene una raiz y un hijo a cada lado no se entra al while
  // como el nodo se parte insertando como si fuera rojo, para mantener que un padre rojo
  // tienen dos hijos negros
  while (node->parent->color == 1) {
    // si mi padre era el hijo izquiedo de su padre
    if (node->parent == node->parent->parent->left) {
      // consideramos el hijo derecho del padre de mi padre
      aux2 = node->parent->parent->right;
      // siempre que dicho hijo exista (no sea una hoja)
      if (aux2 != nullptr) {
        // si el hermano de mi padre era rojo
        if (aux2->color == 1) {
          // lo dejo negro, a mi padre igual y a su padre rojo
          // (cumplir propiedad de que un nodo rojo tiene hijos negros)
          aux2->color = 0;
          node->parent->color = 0;
          node->parent->parent->color = 1;
          // cambiamos el nodo al padre de mi padre para ver si hay que seguir arreglando
          // el arbol hacia arriba
          node = node->parent->parent;
        } else {
          // si el hermano de mi padre no era rojo
          // si yo soy el hijo derecho de mi padre
          if (node == node->parent->right) {
            // me fijo en mi padre
            node = node->parent;
            // quedo yo en la posicion en que estaba mi padre
            leftRotate(node);
          }
          // el color de mi padre queda en negro y su padre en rojo
          node->parent->color = 0;
          node->parent->parent->color = 1;
          // rotar a la derecha del padre de mi padre
          rightRotate(node->parent->parent);
        }
      } else {
        // solo ocurre cuando aux2 era una hoja
        // analogo al else anterior
        if (node == node->parent->right) {
          node = node->parent;
          leftRotate(node);
        }
        node->parent->color = 0;
        node->parent->parent->color = 1;
        rightRotate(node->parent->parent);
      }
    } else {
      // si mi padre era el hijo derecho de su padre
      // consideramos el hermano de mi padre
      aux2 = node->parent->parent->left;
      // si aux2 no es una hoja
      if (aux2 != nullptr) {
        // si era de color rojo
        if (aux2->color == 1) {
          // dejamos su color y el de mi padre como negros
          aux2->color = 0;
          node->parent->color = 0;
          // el del padre de ambos queda rojo
          node->parent->parent->color = 1;
          // me sigo fijando en el padre de mi padre pues le cambie el color
          node = node->parent->parent;
        } else {
          // si no era rojo
          // y soy el hijo izquiedo de mi padre
          if (node == node->parent->left) {
            // quedo en la posicion de mi padre haciendo una rotacion a la derecha
            node = node->parent;
            rightRotate(node);
          }
          // dejamos a mi padre de color negro y a su padre rojo
          node->parent->color = 0;
          node->parent->parent->color = 1;
          // mi padre toma la posicion de su padre con un rotacion a la izquierda
          // notar que mi padre era el hijo derecho de su padre, por eso funciona la
          // rotacion a la izquierda
          leftRotate(node->parent->parent);
        }
      } else {
        // solo ocurre cuando aux2 era una hoja
        // analogo al else anterior
        if (node == node->parent->left) {
          node = node->parent;
          rightRotate(node);
        }
        node->parent->color = 0;
        node->parent->parent->color = 1;
        leftRotate(node->parent->parent);
      }
    }
    // si estoy en raiz salgo
    if (node == this->root) {
      break;
    }
  }
  // la raiz siempre es negra
  this->root->color = 0;
}

// pRight va a quedar en la posicion de p
void RedBlackTree::leftRotate(rbNode *p) {
  rbNode *pRight = p->right;
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
void RedBlackTree::rightRotate(rbNode *p) {
  rbNode *pLeft = p->left;
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

void printCute(rbNode *root, string sep) {
  if (root != nullptr) {
    cout << sep;
    if (root->color) cout << "nodo: " << root->val << "(rojo)" << endl;
    else cout << "nodo: " << root->val << "(negro)" << endl;
    sep += "    ";
    printCute(root->left, sep);
    printCute(root->right, sep);
  }
}

rbNode *createRedBlackTreeNode(int val) {
  rbNode *newNode = (rbNode *)malloc(sizeof(rbNode));
  newNode->val = val;
  newNode->color = 1;
  newNode->left = newNode->right = newNode->parent = nullptr;
  return newNode;
}

rbNode *search(rbNode *root, int val) {
  // mientras no llegue a una hoja
  while (root != nullptr) {
    // si era el que estoy buscando, lo retorno
    if (root->val == val) {
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

void megaFree(rbNode *root) {
  if (root != nullptr) {
    rbNode *left = root->left;
    rbNode *right = root->right;
    free(root);
    megaFree(left);
    megaFree(right);
  }
}
