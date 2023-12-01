#include "la.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main() {

  Node *root = NULL;
  for (int i = 0; i <= 10; i++) {
    insertNode(&root, i);
  }

  // блок логарефмической прогрессии
  double x = 0, time, time1;
  for (int i = 0; i < 10000; i++) {
    time = wtime();
    Node *look = tree_lookup(root, 10);
    time1 = (wtime() - time) * 1000;
    x += time1;
    //  printf("%f", time1);
  }
  x /= 10000;
 // printf("%f", x);

  Node *look = tree_lookup(root, 8);
  RB_DELETE(&root, look);
  free(look);
  print_rb_tree(root, 8);
  // deleteNode(&root, 8);
  //look = tree_lookup(root, 8); //выход за пределы массива так как нет такого
  // printf("%d", look->data);

  int intH = treeH(root);
 //printf("Высота дерева: %d\n", intH);

  return 0;
}
//сделать освобождение памяти дерева
//вывод дерева по красивому + для удаления
//вывод дерева от определенного узла (в задании указано)
// хорошо знать добавление и удаление элементов, а так же повороты
