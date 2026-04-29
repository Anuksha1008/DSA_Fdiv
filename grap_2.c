/*#include<stdio.h>
#include<stdbool.h>

#define MAX 20

int adj[MAX][MAX];
bool visited[MAX];
int queue[MAX];
int front = 0, rear = -1;
int n;

void enqueue(int v){
queue[++rear] = v;
}
int dequeue(){
return queue[front++];
}*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

// Vertex structure
struct Vertex {
    char label;
    bool visited;
};

// Graph variables
struct Vertex* lstVertices[MAX];
int adjMatrix[MAX][MAX];
int vertexCount = 0;

// Queue variables
int queue[MAX];
int front = 0, rear = -1;

// ---------------- Queue Functions ----------------
void insert(int data) {
    queue[++rear] = data;
}

int deleteQ() {
    return queue[front++];
}

bool isQueueEmpty() {
    return front > rear;
}

// ---------------- Graph Functions ----------------
void addVertex(char label) {
    struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->label = label;
    vertex->visited = false;
    lstVertices[vertexCount++] = vertex;
}

void addEdge(int start, int end) {
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1; // undirected graph
}

void displayVertex(int i) {
    printf("%c ", lstVertices[i]->label);
}

int getAdjUnvisitedVertex(int v) {
    for(int i = 0; i < vertexCount; i++) {
        if(adjMatrix[v][i] == 1 && lstVertices[i]->visited == false)
            return i;
    }
    return -1;
}

// ---------------- BFS ----------------
void BFS() {
    if(vertexCount == 0) {
        printf("\nGraph is empty!\n");
        return;
    }

    front = 0; rear = -1;

    lstVertices[0]->visited = true;
    displayVertex(0);
    insert(0);

    while(!isQueueEmpty()) {
        int temp = deleteQ();

        int adj;
        while((adj = getAdjUnvisitedVertex(temp)) != -1) {
            lstVertices[adj]->visited = true;
            displayVertex(adj);
            insert(adj);
        }
    }

    // Reset visited
    for(int i = 0; i < vertexCount; i++)
        lstVertices[i]->visited = false;

    printf("\n");
}

// ---------------- Display Matrix ----------------
void displayMatrix() {
    printf("\nAdjacency Matrix:\n");
    for(int i = 0; i < vertexCount; i++) {
        for(int j = 0; j < vertexCount; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// ---------------- Main Menu ----------------
int main() {
    int choice, v1, v2;
    char label;

    // Initialize matrix
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            adjMatrix[i][j] = 0;

    do {
        printf("\n--- GRAPH MENU ---\n");
        printf("1. Add Vertex\n");
        printf("2. Add Edge\n");
        printf("3. Display Adjacency Matrix\n");
        printf("4. Perform BFS\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter vertex label: ");
                scanf(" %c", &label);
                addVertex(label);
                break;

            case 2:
                printf("Enter edge (start end index): ");
                scanf("%d %d", &v1, &v2);
                addEdge(v1, v2);
                break;

            case 3:
                displayMatrix();
                break;

            case 4:
                printf("BFS Traversal: ");
                BFS();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 5);

    return 0;
}
