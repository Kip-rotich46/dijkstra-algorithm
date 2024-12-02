#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Function to initialize the source vertex
void initialize_single_source(int n, int source, int d[], int pi[]) {
    for (int i = 0; i < n; i++) {
        d[i] = INT_MAX;  // Initialize distance as infinity
        pi[i] = -1;  // No parent yet
    }
    d[source] = 0;  // Source has distance 0
}

// Function to relax an edge (u, v)
void relax(int u, int v, int weight[], int d[], int pi[], int n) {
    if (d[v] > d[u] + weight[u * n + v]) {
        d[v] = d[u] + weight[u * n + v];  // Update distance
        pi[v] = u;  // Update parent
    }
}

// Dijkstra's algorithm
void dijkstra(int n, int source, int adjMatrix[], int d[], int pi[]) {
    bool visited[n];  // Track visited vertices
    initialize_single_source(n, source, d, pi);
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (int count = 0; count < n - 1; count++) {
        // Find the vertex with the minimum distance
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || d[i] < d[u])) {
                u = i;
            }
        }

        visited[u] = true;  // Mark the vertex as visited

        // Update the distance of the adjacent vertices
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u * n + v] != 0) {
                relax(u, v, adjMatrix, d, pi, n);
            }
        }
    }
}

// Function to read graph data from a file
void read_graph(const char* filename, int* adjMatrix, int* n) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d", n);  // Read the number of vertices
    for (int i = 0; i < (*n); i++) {
        for (int j = 0; j < (*n); j++) {
            fscanf(file, "%d", &adjMatrix[i * (*n) + j]);  // Read the adjacency matrix
        }
    }
    fclose(file);
}

// Main function to test the algorithm with a given file
int main() {
    int n;
    int* adjMatrix;
    int* d;  // Distance array
    int* pi; // Parent array

    // Reading graph from tinyDG.txt (you can change this to other files)
    adjMatrix = (int*)malloc(n * n * sizeof(int));
    d = (int*)malloc(n * sizeof(int));
    pi = (int*)malloc(n * sizeof(int));

    read_graph("tinyDG.txt", adjMatrix, &n);  // Change filename if needed

    // Run Dijkstra's algorithm from source vertex 0
    dijkstra(n, 0, adjMatrix, d, pi);

    // Output the shortest distances and paths
    printf("Shortest distances from source (0):\n");
    for (int i = 0; i < n; i++) {
        printf("Distance from 0 to %d: %d\n", i, d[i]);
    }

    // Free allocated memory
    free(adjMatrix);
    free(d);
    free(pi);

    return 0;
}
