#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Create node
struct node* create(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

// Insert (Binary Tree - simple)
struct node* insert(struct node* root, int data) {
    if (root == NULL)
        return create(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

// Inorder Traversal
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Search
void search(struct node* root, int key) {
    if (root == NULL) {
        printf("Not Found\n");
        return;
    }
    if (root->data == key) {
        printf("Found\n");
        return;
    }
    if (key < root->data)
        search(root->left, key);
    else
        search(root->right, key);
}


// Find minimum value node (inorder successor)
struct node* minValueNode(struct node* root) {
    struct node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete node
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    // Traverse tree
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {
        // Case 1 & 2: one or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: two children
        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}
int main() {
    struct node* root = NULL;
    int choice, val;

    while (1) {
        printf("\n1.Insert\n2.Display\n3.Search\n4.delete \n5Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Tree (Inorder): ");
                inorder(root);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                search(root, val);
                break;


          case 4:
    printf("Enter value to delete: ");
    scanf("%d", &val);
    root = deleteNode(root, val);
    break;

case 5:
    exit(0);


            default:
                printf("Invalid choice\n");
        }
    }
}
