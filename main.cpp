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
    free(array);
    free(bigArray);
  }
  return 0;
}
