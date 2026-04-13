/* Rahul, a software engineer, is developing a file indexing feature for an operating system like Microsoft Windows. Instead of scanning all folders every time, Rahul designs a system that stores file IDs (or sizes) in an organized hierarchical structure of connected nodes. This helps in: Fast insertion when a new file is added, Fast deletion when a file is removed. To ensure data is not lost after restarting the system, Rahul stores the file index in a disk file. He is using a program based on a node-based hierarchical structure.

Smaller IDs → go to the left

Larger IDs → go to the right

This helps users quickly search for places and update map data efficiently.

Input Format

an integer number, number of nodes n

1 2 3 ... n

Node to be inseted in a tree.

Node to be deleted.

Constraints

General Constraints 1 ≤ n ≤ 100 → Number of nodes (files/locations) 1 ≤ q ≤ 50 → Number of operations Node names / IDs are unique Maximum tree depth ≤ 20

Output Format

Current File Index sorted in ascending order.

Sample Input 0*/
#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int data;
    struct node *left, *right;
};

// Create node
struct node* create(int val) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}

// Insert
struct node* insert(struct node* root, int val) {
    if (root == NULL)
        return create(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

// Find minimum
struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node
struct node* deleteNode(struct node* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->data)
        root->left = deleteNode(root->left, val);
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
    else {
        // No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // One child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        // Two children
        else {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// Inorder traversal
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int n, i, x, del;
    struct node* root = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
    }

    scanf("%d", &x);   // insert one more node
    root = insert(root, x);

    scanf("%d", &del); // delete node
    root = deleteNode(root, del);

    printf("Current File Index sorted in ascending order: ");
    inorder(root);

    return 0;
}
