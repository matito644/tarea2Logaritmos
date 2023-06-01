#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

#include "redBlackTree.h"
#include "splayTree.h"

int jeje=0;

int *createArray(int size) {
  int *array = (int *)malloc(sizeof(int)*size);
  for (int i=0; i<size; i++) {
    array[i] = i+1;
  }
  return array;
}

int *createBigArray(int *input, int rep, int twoK, int twoPower) {
  int *array = (int *)malloc(sizeof(int)*twoPower);
  int slice = 1<<rep;
  int m = 0;
  // printf("size es: %d y rep es: %d y slice es:%d\n", size, rep, slice)
  for (int i=0; i<twoK; i++) {
    for (int j=0; j<slice; j++) {
      array[m] = input[i];
      m++;
      if (m%1000000==0) {
        jeje++;
      }
    }
  }
  return array;
}

void printArray(int *array, int size) {
  for (int i=0; i<size; i++) {
    cout << array[i] << ' ';
  }
  cout << '\n';
}

// ideal para shufflear el arreglo
void shuffleArray(int *array, int size) {
  // distinto cada vez que se corre
  auto n = random_device {};
  auto m = default_random_engine { n() };
  // la misma siempre
  // auto rng = default_random_engine { };
  shuffle(array, array+size, m);
  // for (int i=0; i<size; i++) {
  //   cout << array[i] << " ";
  // }
  // cout << '\n';
}

int main() {

  int twoPower = 1<<28;
  for (int k=16; k<=24; k++) {
    int twoK = 1<<k;
    printf("Se va a crear un arreglo de %d\n", twoK);
    int *array = createArray(twoK);
    printf("Desordenar el arreglo haciendo shuffle.\n");
    shuffleArray(array, twoK);
    printf("Se va a crear el bigArray\n");
    int *bigArray = createBigArray(array, 28-k, twoK, twoPower);
    printf("Desordenar el arreglo haciendo shuffle, se demora bastante\n");
    shuffleArray(bigArray, twoPower);

    // crear los arboles y e insertar los elementos
    printf("Se crean los árboles y se insertan los elementos\n");
    RedBlackTree rbTree;
    SplayTree sTree;
    for (int i=0; i<twoK; i++) {
      rbNode *rbNode = createRedBlackTreeNode(array[i]);
      sNode *sNode = createSplayTreeNode(array[i]);
      rbTree.insert(rbNode);
      sTree.insert(sNode);
    }
    printf("Listo!\nAhora se harán las búsquedas");
    // BUSQUEDAS


    // free a todo
    megaFree(rbTree.getRoot());
    megaFree(sTree.getRoot());
    free(array);
    free(bigArray);
  }

  // ejemplo de juguete
  // int *array = createArray(8);
  // int *bigArray = createBigArray(array, 1, 8, 16);
  // shuffleArray(array, 8);
  // shuffleArray(bigArray, 16);
  // printArray(array, 8);
  // printArray(bigArray, 16);
  //
  // RedBlackTree rbTree;
  // SplayTree sTree;
  // for (int i=0; i<8; i++) {
  //   rbNode *rbNode = createRedBlackTreeNode(array[i]);
  //   sNode *sNode = createSplayTreeNode(array[i]);
  //   rbTree.insert(rbNode);
  //   sTree.insert(sNode);
  // }
  //
  // printCute(rbTree.getRoot(), "", 1);
  // printCuteSplay(sTree.getRoot(), "", 1);
  //
  // megaFree(rbTree.getRoot());
  // megaFree(sTree.getRoot());
  // free(array);
  // free(bigArray);
  return 0;
}
