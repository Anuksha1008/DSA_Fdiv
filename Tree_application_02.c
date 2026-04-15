/*Scenario: Routing Table Management (Network System)

In a computer network:

Each router is stored as a node in a Binary Search Tree (BST)
Left child → routers with smaller ID
Right child → routers with larger ID*/

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// Inorder Traversal (LNR)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int n, i, val, newRouter;
    struct Node* root = NULL;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    if (n == -1) {
        printf("Invalid input");
        return 0;
    }

    printf("Enter router IDs:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Enter new router ID to insert: ");
    scanf("%d", &newRouter);

    root = insert(root, newRouter);

    printf("Routing table (Inorder): ");
    inorder(root);

    return 0;
}
