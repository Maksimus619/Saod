**Добавление узла в АА-дерево:**

1. **Инициализация нового узла:**
   - Создается новый узел с заданным значением данных (data), уровнем 1 (level), и без левого и правого потомка.
   - Уровень устанавливается в 1, так как новый узел вставляется на самом нижнем уровне.

```c
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->level = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
```

2. **Операция вставки (`insert`):**
   - Если дерево пусто, созданный узел становится корневым узлом.
   - Иначе, осуществляется рекурсивный поиск подходящего места для вставки узла, с учетом бинарного порядка.
   - После вставки выполняются операции skew и split для поддержания баланса.

```c
Node* insert(Node* root, int data) {
    if (!root) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    root = skew(root);
    root = split(root);
    return root;
}
```

3. **Операция skew (`skew`):**
   - Проверяет, если у текущего узла (root) и его левого потомка (root->left) одинаковый уровень, выполняет правый поворот для поддержания баланса.

```c
Node* skew(Node* root) {
    if (root && root->left && root->level == root->left->level) {
        root = rotateRight(root);
    }
    return root;
}
```

4. **Операция split (`split`):**
   - Проверяет, если у текущего узла (root) и его правого потомка (root->right) и правого потомка правого потомка (root->right->right) одинаковый уровень, выполняет левый поворот и увеличивает уровень правого потомка для поддержания баланса.

```c
Node* split(Node* root) {
    if (root && root->right && root->right->right && root->right->right->level == root->level) {
        root = rotateLeft(root);
    }
    return root;
}
```

Эти операции обеспечивают добавление нового узла в АА-дерево с последующей балансировкой для поддержания его структуры.