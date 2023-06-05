#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;

#include "redBlackTree.h"
#include "splayTree.h"

// funcion para crear un arreglo de 1..N
int *createArray(int size) {
  int *array = (int *)malloc(sizeof(int)*size);
  for (int i=0; i<size; i++) {
    array[i] = i+1;
  }
  return array;
}

// funcion para crear un arreglo grande (M)
int *createBigArray(int *input, int rep, int twoK, int twoPower) {
  int *array = (int *)malloc(sizeof(int)*twoPower);
  int slice = 1<<rep;
  int m = 0;
  for (int i=0; i<twoK; i++) {
    for (int j=0; j<slice; j++) {
      array[m] = input[i];
      m++;
    }
  }
  return array;
}

// ideal para shufflear el arreglo
void shuffleArray(int *array, int size) {
  // distinto cada vez que se corre
  auto n = random_device {};
  auto m = default_random_engine { n() };
  // la misma siempre
  // auto rng = default_random_engine { };
  shuffle(array, array+size, m);
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << ' ';
  }
  cout << endl;
}
// para almacenar el nuevo tamaño del arreglo grande
int newSize = 0;
// función para crear un arreglo con skew
int *skew (int * array, int twoK, double alfa, int twoPower){
  // calcular la suma de las frecuencias
  long long sum = 0;
  for (long long i=0; i<twoK; i++) {
    long long phi = floor(pow(i, alfa));
    sum += phi;
  }
  // para conocer el largo final del arreglo grande
  long long M = 0;
  for (long long i=0; i<twoK; i++) {
    long long phi = ceil(floor(pow(i, alfa)) * twoPower /sum);
    phi = max<long long>(1, phi);
    for (long long j=0; j<phi; j++) {
      M++;
    }
  }
  cout << "M es: " << M << endl;
  newSize = M;
  cout << "Creando el arreglo de largo M, que es cercano a 2**28\n";
  int *C = (int *)malloc(sizeof(int)*M);
  cout << "Ahora se escribirán phi copias de los elementos en el arreglo pequeño en el arreglo grande\n";
  int m = 0;
  for (long long i=0; i<twoK; i++) {
    long long phi = ceil(floor(pow(i, alfa)) * twoPower /sum);
    phi = max<long long>(1, phi);
    for (long long j=0; j<phi; j++) {
      C[m] = array[i];
      m++;
    }
  }
  cout << "Desordenar el arreglo, se demora bastante" << endl;
  shuffleArray(C, M);
  return C;
}

// funcion para obtener el promedio
float getMean(float array[]) {
  float sum = 0;
  for(int i=0; i<3; i++) {
    sum += array[i];
  }
  return sum/3;
}

// funcion para obtener la varianza
float getVariance(float array[]) {
  float variance = 0;
  float mean = getMean(array);
  for (int i=0; i<3; i++) {
    variance += pow(array[i] - mean, 2);
  }
  return variance/3;
}

// funcion main
int main() {
  ofstream eqFileSplay("eq_fileSplay.csv");
  ofstream eqFileRDT("eq_fileRDT.csv");
  ofstream skewFileSplay("skew_fileSplay.csv");
  ofstream skewFileRDT("skew_fileRDT.csv");
  eqFileSplay<<"k,prom,var,std\n";
  eqFileRDT<<"k,prom,var,std\n";
  skewFileSplay << "k,alpha,prom,var,std\n";
  skewFileRDT<<"k,alpha,prom,var,std\n";
  int powerr = 26;
  int twoPower = 1<<powerr;
  for (int k=16; k<21; k++) {
    int twoK = 1<<k;
    printf("Se va a crear un arreglo de %d\n", twoK);
    int *array = createArray(twoK);
    printf("Desordenar el arreglo haciendo shuffle.\n");
    shuffleArray(array, twoK);
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
    printf("Listo!\nAhora vienen los tres test de búsqueda\n");
    // para almacenar los tiempos.
    float arrayForMeanSplay[3];
    float arrayForMeanRedBlack[3];
    for (int test=0; test<3; test++) {
      printf("Test %d\n", test+1);
      printf("Se va a crear el bigArray\n");
      int *bigArray = createBigArray(array, powerr-k, twoK, twoPower);
      printf("Desordenar el arreglo haciendo shuffle, se demora bastante\n");
      shuffleArray(bigArray, twoPower);
      printf("Listo!\nAhora se harán las búsquedas\n");
      // BUSQUEDAS
      clock_t timetime;
      // desde acá se cuenta el tiempo
  	  timetime = clock();
      // búsqueda en el red black tree
      rbNode *root = rbTree.getRoot();
      for (int i=0; i<twoPower; i++) {
        search(root, bigArray[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanRedBlack[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el red black tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // búsqueda en el splay tree
      timetime = clock();
      for (int i=0; i<twoPower; i++) {
        sTree.search(sTree.getRoot(), bigArray[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanSplay[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el splay tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // free
      free(bigArray);
      printf("Test %d listo\n", test+1);
    }
    // mostrar el promedio, la varianza y la desviacion estandar
    cout << "Splay, promedio: " << getMean(arrayForMeanSplay) << " || varianza: " << getVariance(arrayForMeanSplay) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanSplay)) << endl;
    cout << "RedBlack, promedio: " << getMean(arrayForMeanRedBlack) << " || varianza: " << getVariance(arrayForMeanRedBlack) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanRedBlack)) << endl;
    eqFileSplay << k << "," << getMean(arrayForMeanSplay) << "," 
                << getVariance(arrayForMeanSplay) << ","
                << sqrt(getVariance(arrayForMeanSplay)) << "\n";
    eqFileRDT << k << "," << getMean(arrayForMeanRedBlack) << "," 
                << getVariance(arrayForMeanRedBlack) << ","
                << sqrt(getVariance(arrayForMeanRedBlack)) << "\n";
    // free a todo
    megaFree(rbTree.getRoot());
    megaFree(sTree.getRoot());
    free(array);
  }
  eqFileSplay.close();
  eqFileRDT.close();

  printf("Terminaron los test sin skew\n\nAhora vienen las búsquedas con skew\n");
  for (int k=16; k<25; k++) {
    // SKEW
    int twoK = 1<<k;
    printf("Vamos con la búsqueda con skew\n");
    printf("Se crea una permutación para luego formar los 3 arreglos con skew\n");
    int *arrayForSkew = createArray(twoK);
    printf("Desordenar dicho arreglo\n");
    shuffleArray(arrayForSkew, twoK);
    printf("Ahora se crean los árboles y se insertar los elementos\n");
    RedBlackTree rbTree;
    SplayTree sTree;
    for (int i=0; i<twoK; i++) {
      rbNode *rbNode = createRedBlackTreeNode(arrayForSkew[i]);
      sNode *sNode = createSplayTreeNode(arrayForSkew[i]);
      rbTree.insert(rbNode);
      sTree.insert(sNode);
    }
    printf("Se crearán los arreglos con skew\nPrimero el con alfa igual 0.5\n");
    int *skew1 = skew(arrayForSkew, twoK, 0.5, twoPower);
    printf("Listo!\nAhora vienen los tres test de búsqueda\n");
    // para almacenar los tiempos.
    float arrayForMeanSplay[3];
    float arrayForMeanRedBlack[3];
    for (int test=0; test<3; test++) {
      printf("Test %d con alfa 0.5\n", test+1);
      clock_t timetime;
      // desde acá se cuenta el tiempo
  	  timetime = clock();
      // búsqueda en el red black tree
      rbNode *root = rbTree.getRoot();
      for (int i=0; i<newSize; i++) {
        search(root, skew1[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanRedBlack[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el red black tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      
      // búsqueda en el splay tree
      timetime = clock();
      for (int i=0; i<newSize; i++) {
        sTree.search(sTree.getRoot(), skew1[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanSplay[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el splay tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // free
      printf("Test %d listo\n", test+1);
    }
    // mostrar el promedio, la varianza y la desviacion estandar
    cout << "Splay, promedio: " << getMean(arrayForMeanSplay) << " || varianza: " << getVariance(arrayForMeanSplay) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanSplay)) << endl;
    cout << "RedBlack, promedio: " << getMean(arrayForMeanRedBlack) << " || varianza: " << getVariance(arrayForMeanRedBlack) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanRedBlack)) << endl;
    skewFileSplay<<k<<","<<0.5<<","<<getMean(arrayForMeanSplay)<<","<<getVariance(arrayForMeanSplay)<<","<< sqrt(getVariance(arrayForMeanSplay))<<"\n";
    skewFileRDT<<k<<","<<0.5<<","<<getMean(arrayForMeanRedBlack)<<","<<getVariance(arrayForMeanRedBlack)<<","<<sqrt(getVariance(arrayForMeanRedBlack))<<"\n";
    free(skew1);
    printf("\nAhora el con alfa igual 1\n");
    int *skew2 = skew(arrayForSkew, twoK, 1, twoPower);
    for (int test=0; test<3; test++) {
      printf("Test %d con alfa 1\n", test+1);
      clock_t timetime;
      // desde acá se cuenta el tiempo
  	  timetime = clock();
      // búsqueda en el red black tree
      rbNode *root = rbTree.getRoot();
      for (int i=0; i<newSize; i++) {
        search(root, skew2[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanRedBlack[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el red black tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // búsqueda en el splay tree
      timetime = clock();
      for (int i=0; i<newSize; i++) {
        sTree.search(sTree.getRoot(), skew2[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanSplay[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el splay tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // free
      printf("Test %d listo\n", test+1);
    }
    // mostrar el promedio, la varianza y la desviacion estandar
    cout << "Splay, promedio: " << getMean(arrayForMeanSplay) << " || varianza: " << getVariance(arrayForMeanSplay) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanSplay)) << endl;
    cout << "RedBlack, promedio: " << getMean(arrayForMeanRedBlack) << " || varianza: " << getVariance(arrayForMeanRedBlack) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanRedBlack)) << endl;
    skewFileSplay<<k<<","<<1<<","<<getMean(arrayForMeanSplay)<<","<<getVariance(arrayForMeanSplay)<<","<< sqrt(getVariance(arrayForMeanSplay))<<"\n";
    skewFileRDT<<k<<","<<1<<","<<getMean(arrayForMeanRedBlack)<<","<<getVariance(arrayForMeanRedBlack)<<","<<sqrt(getVariance(arrayForMeanRedBlack))<<"\n";
    free(skew2);
    
    
    printf("\nFinalmente el con alfa igual 1.5\n");
    int *skew3 = skew(arrayForSkew, twoK, 1.5, twoPower);
    for (int test=0; test<3; test++) {
      printf("Test %d con alfa 1.5\n", test+1);
      clock_t timetime;
      // desde acá se cuenta el tiempo
  	  timetime = clock();
      // búsqueda en el red black tree
      rbNode *root = rbTree.getRoot();
      for (int i=0; i<newSize; i++) {
        search(root, skew3[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanRedBlack[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el red black tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // búsqueda en el splay tree
      timetime = clock();
      for (int i=0; i<newSize; i++) {
        sTree.search(sTree.getRoot(), skew3[i]);
      }
      // obtener el tiempo
      timetime = clock() - timetime;
      // guardar el tiempo
      arrayForMeanSplay[test] = (float)timetime/CLOCKS_PER_SEC;
  	  cout << "La búsqueda en el splay tree tomó " << (float)timetime/CLOCKS_PER_SEC << " segundos" << endl;
      // free
      printf("Test %d listo\n", test+1);
    }
    // mostrar el promedio, la varianza y la desviacion estandar
    cout << "Splay, promedio: " << getMean(arrayForMeanSplay) << " || varianza: " << getVariance(arrayForMeanSplay) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanSplay)) << endl;
    cout << "RedBlack, promedio: " << getMean(arrayForMeanRedBlack) << " || varianza: " << getVariance(arrayForMeanRedBlack) << " || desviación estándar: " << sqrt(getVariance(arrayForMeanRedBlack)) << endl;
    skewFileSplay<<k<<","<<1.5<<","<<getMean(arrayForMeanSplay)<<","<<getVariance(arrayForMeanSplay)<<","<< sqrt(getVariance(arrayForMeanSplay))<<"\n";
    skewFileRDT<<k<<","<<1.5<<","<<getMean(arrayForMeanRedBlack)<<","<<getVariance(arrayForMeanRedBlack)<<","<<sqrt(getVariance(arrayForMeanRedBlack))<<"\n";
    free(skew3);
    printf("Listo!\n\n");
    free(arrayForSkew);
  }
  return 0;
}
