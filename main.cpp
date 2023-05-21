#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

#include "redBlackTree.h"


int *createArray(int size) {
  int *array = (int *)malloc(sizeof(int)*size);
  for (int i=0; i<size; i++) {
    array[i] = i+1;
  }
  return array;
}

// ideal para shufflear el arreglo de 2**28
void shuffleArray(int *array, int size) {
  // distinto cada vez que se corre
  auto n = random_device {};
  auto m = default_random_engine { n() };
  // la misma siempre
  // auto rng = default_random_engine { };
  shuffle(array, array+size, m);
  for (int i=0; i<size; i++) {
    cout << array[i] << " ";
  }
  cout << '\n';
}

int main() {
  int *array = createArray(6);
  shuffleArray(array, 6);
  RedBlackTree tree;
  for (int i=0; i<6; i++) {
    treeNode *node = createNode(array[i]);
    tree.insert(node);
  }
  printCute(tree.getRoot(), "");
  megaFree(tree.getRoot());
  free(array);
  return 0;
}
