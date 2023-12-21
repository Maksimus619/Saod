#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Node {
    int data;
    int level;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->level = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* rotateRight(Node* root) {
    if (root && root->left) {
        Node* left = root->left;
        root->left = left->right;
        left->right = root;
        return left;
    }
    return root;
}

Node* rotateLeft(Node* root) {
    if (root && root->right) {
        Node* right = root->right;
        root->right = right->left;
        right->left = root;
        right->level++;
        return right;
    }
    return root;
}

Node* skew(Node* root) {
    if (root && root->left && root->level == root->left->level) {
        root = rotateRight(root);
    }
    return root;
}

Node* split(Node* root) {
    if (root && root->right && root->right->right && root->right->right->level == root->level) {
        root = rotateLeft(root);
    }
    return root;
}

Node* findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int data) {
    if (!root) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    root = skew(root);
    root = split(root);
    return root;
}

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

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

bool isNodePresent(Node* root, int data) {
    if (!root) {
        return false;
    }

    if (data < root->data) {
        return isNodePresent(root->left, data);
    } else if (data > root->data) {
        return isNodePresent(root->right, data);
    }

    return true;
}

int main() {
    Node* root = NULL;
    int values_count = 100000;

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    // Генерация и добавление случайных значений
    for (int i = 0; i < values_count; i++) {
        int random_value = rand() % (values_count * 10);
        root = insert(root, random_value);
    }

    // Засекаем время перед выполнением операций
    clock_t start_time = clock();

    printf("In-order traversal of the AA tree: ");
    inOrder(root);
    printf("\n");

    // Добавление случайного значения
    int random_insert_value = rand() % (values_count * 10);
    if (!isNodePresent(root, random_insert_value)) {
        root = insert(root, random_insert_value);
        printf("Random element added: %d\n", random_insert_value);
    } else {
        printf("Element already exists.\n");
    }

    // Удаление случайного значения
    int random_delete_value = rand() % (values_count * 10);
    if (isNodePresent(root, random_delete_value)) {
        root = deleteNode(root, random_delete_value);
        printf("Random element deleted: %d\n", random_delete_value);
    } else {
        printf("Element not found.\n");
    }

    printf("In-order traversal after operations: ");
    inOrder(root);
    printf("\n");

    // Засекаем время после выполнения операций
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;
    
    printf("Прошедшее время: %.2f миллисекунд\n", elapsed_time);

    return 0;
}
