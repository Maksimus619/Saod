#include <stdio.h>
#include <stdlib.h>

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

int main() {
    Node* root = NULL;
    int values[] = {10, 7, 20, 30, 5, 8};

    for (int i = 0; i < 6; i++) {
        root = insert(root, values[i]);
    }

    printf("In-order traversal of the AA tree: ");
    inOrder(root);
    printf("\n");

    // Добавление
    root = insert(root, 7);

    // Удаление
    root = deleteNode(root, 7);

    printf("In-order traversal after deletion: ");
    inOrder(root);
    printf("\n");

    return 0;
}
