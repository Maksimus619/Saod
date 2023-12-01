#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
  int color;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->parent = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->color = 1;
  return newNode;
}

// Вспомогательная функция для поворота направо
void rotateRight(Node **root, Node *node) {
  Node *leftChild = node->left;
  node->left = leftChild->right;
  if (node->left != NULL)
    node->left->parent = node;
  leftChild->parent = node->parent;
  if (node->parent == NULL)
    (*root) = leftChild;
  else if (node == node->parent->left)
    node->parent->left = leftChild;
  else
    node->parent->right = leftChild;
  leftChild->right = node;
  node->parent = leftChild;
}

// Вспомогательная функция для поворота налево
void rotateLeft(Node **root, Node *node) {
  Node *rightChild = node->right;
  node->right = rightChild->left;
  if (node->right != NULL)
    node->right->parent = node;
  rightChild->parent = node->parent;
  if (node->parent == NULL)
    (*root) = rightChild;
  else if (node == node->parent->left)
    node->parent->left = rightChild;
  else
    node->parent->right = rightChild;
  rightChild->left = node;
  node->parent = rightChild;
}

// Вспомогательная функция для поддержания свойств красно-черного дерева после
// вставки
void fixViolation(Node **root, Node *node) {
  Node *parent = NULL;
  Node *grandparent = NULL;

  // Пока не нарушится свойство 2 (каждый красный узел имеет черного родителя)
  while ((node != *root) && (node->color != 0) && (node->parent->color == 1)) {
    parent = node->parent;
    grandparent = node->parent->parent;

    // Если родительский узел является левым детищем дедушки
    if (parent == grandparent->left) {
      Node *uncle = grandparent->right;

      // Случай 1: Дядя является красным узлом - просто перекрасим
      if (uncle != NULL && uncle->color == 1) {
        grandparent->color = 1;
        parent->color = 0;
        uncle->color = 0;
        node = grandparent;
      } else {
        // Случай 2: Узел является правым детищем - левый поворот
        if (node == parent->right) {
          rotateLeft(root, parent);
          node = parent;
          parent = node->parent;
        }

        // Случай 3: Узел является левым детищем - правый поворот
        rotateRight(root, grandparent);
        int tempColor = parent->color;
        parent->color = grandparent->color;
        grandparent->color = tempColor;
        node = parent;
      }
    }
    // Если родительский узел является правым детищем дедушки
    else {
      Node *uncle = grandparent->left;

      // Случай 1: Дядя является красным узлом - просто перекрасим
      if ((uncle != NULL) && (uncle->color == 1)) {
        grandparent->color = 1;
        parent->color = 0;
        uncle->color = 0;
        node = grandparent;
      } else {
        // Случай 2: Узел является левым детищем - правый поворот
        if (node == parent->left) {
          rotateRight(root, parent);
          node = parent;
          parent = node->parent;
        }

        // Случай 3: Узел является правым детищем - левый поворот
        rotateLeft(root, grandparent);
        int tempColor = parent->color;
        parent->color = grandparent->color;
        grandparent->color = tempColor;
        node = parent;
      }
    }
  }

  // Корень всегда черный
  (*root)->color = 0;
}

Node *tree_lookup(Node *node, int data) {
  if (node == NULL || node->data == data)
    return node;

  if (data < node->data)
    return tree_lookup(node->left, data);

  return tree_lookup(node->right, data);
}
// удаление узла

//поиск высоты
int treeH(Node *root) {
  if (root == NULL) {
    return 0;
  } else {

    int leftH = treeH(root->left);
    int rightH = treeH(root->right);

    // Возвращаем максимальную высоту из двух поддеревьев, увеличенную на 1
    if (leftH > rightH)
      return leftH + 1;
    else
      return rightH + 1;
  }
}

void insertNode(Node **root, int data) {
  Node *newNode = createNode(data);

  Node *current = *root;
  Node *parent = NULL;
  while (current != NULL) {
    parent = current;
    if (newNode->data < current->data)
      current = current->left;
    else
      current = current->right;
  }
  newNode->parent = parent;
  if (parent == NULL)
    *root = newNode;
  else if (newNode->data < parent->data)
    parent->left = newNode;
  else
    parent->right = newNode;

  fixViolation(root, newNode);
}

void RB_TRANSPLANT(Node **root, Node *u, Node *v) {
  if (u->parent == NULL)
    *root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v != NULL)
    v->parent = u->parent;
}

Node *tree_minimum(Node *node) {
  while (node->left != NULL)
    node = node->left;
  return node;
}

void RB_DELETE_FIXUP(Node **root, Node *x) {
  while (x != *root && x->color == 0) {
    if (x == x->parent->left) {
      Node *w = x->parent->right;

      if (w->color == 1) {
        w->color = 0;                // case 1
        x->parent->color = 1;        // case 1
        rotateLeft(root, x->parent); // case 1
        w = x->parent->right;        // case 1
      }

      if (w->left->color == 0 && w->right->color == 0) {
        w->color = 1;  // case 2
        x = x->parent; // case 2
      } else {
        if (w->right->color == 0) {
          w->left->color = 0;   // case 3
          w->color = 1;         // case 3
          rotateRight(root, w); // case 3
          w = x->parent->right; // case 3
        }

        w->color = x->parent->color; // case 4
        x->parent->color = 0;        // case 4
        w->right->color = 0;         // case 4
        rotateLeft(root, x->parent); // case 4
        x = *root;                   // case 4
      }
    } else {
      // Симметричное отражение для правых и левых
      // меняющихся позиций
      Node *w = x->parent->left;

      if (w->color == 1) {
        w->color = 0;                 // case 1
        x->parent->color = 1;         // case 1
        rotateRight(root, x->parent); // case 1
        w = x->parent->left;          // case 1
      }

      if (w->right->color == 0 && w->left->color == 0) {
        w->color = 1;  // case 2
        x = x->parent; // case 2
      } else {
        if (w->left->color == 0) {
          w->right->color = 0; // case 3
          w->color = 1;        // case 3
          rotateLeft(root, w); // case 3
          w = x->parent->left; // case 3
        }

        w->color = x->parent->color;  // case 4
        x->parent->color = 0;         // case 4
        w->left->color = 0;           // case 4
        rotateRight(root, x->parent); // case 4
        x = *root;                    // case 4
      }
    }
  }

  x->color = 0;
}

void RB_DELETE(Node **root, Node *z) {
  Node *y = z;
  Node *x = NULL;
  int y_original_color = y->color;

  if (z->left == NULL) {
    x = z->right;
    RB_TRANSPLANT(root, z, z->right);
  } else if (z->right == NULL) {
    x = z->left;
    RB_TRANSPLANT(root, z, z->left);
  } else {
    y = tree_minimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z)
      x->parent = y;
    else {
      RB_TRANSPLANT(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    RB_TRANSPLANT(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (y_original_color == 0)
    RB_DELETE_FIXUP(root, x);
}



void free_rb_tree(Node *root) {
  if (root == NULL) {
    return;
  }

  free_rb_tree(root->left);
  free_rb_tree(root->right);

    free(root);
}

void print_rb_tree(Node *node, int depth) {
  if (node == NULL) {
    return;
  }

  // Выводим правое поддерево
  print_rb_tree(node->right, depth + 1);

  // Выводим текущий узел
  for (int i = 0; i < depth; i++) {
    if (i == depth - 1) {
      printf("└──");
    } else {
      printf("│   ");
    }
  }
  printf("%d", node->data);
  if (node->color == 1) {
    printf(" (R)\n");
  } else {
    printf(" (B)\n");
  }

  // Выводим левое поддерево
  print_rb_tree(node->left, depth + 1);
}
