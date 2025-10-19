#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int dest;  
    int weight; 
} Edge;

typedef struct AdjNode {
    Edge edge;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    int V; 
    AdjNode* adj[MAX_NODES];
} Graph;

AdjNode* newAdjNode(int dest, int weight) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->edge.dest = dest;
    newNode->edge.weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph (S to D)
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* newNode = newAdjNode(dest, weight);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

// Function to update an edge weight (for dynamic traffic)
void updateWeight(Graph* graph, int src, int dest, int newWeight) {
    AdjNode* temp = graph->adj[src];
    while (temp) {
        if (temp->edge.dest == dest) {
            temp->edge.weight = newWeight;
            printf("--- Dynamic Update: Edge (%d -> %d) updated to %d min ---\n", src, dest, newWeight);
            return;
        }
        temp = temp->next;
    }
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Dijkstra's Algorithm implementation
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX_NODES];
    bool sptSet[MAX_NODES];
    int parent[MAX_NODES];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
\
        int u = minDistance(dist, sptSet, V);

        sptSet[u] = true;

        AdjNode* pCrawl = graph->adj[u];
        while (pCrawl != NULL) {
            int v = pCrawl->edge.dest;
            int weight = pCrawl->edge.weight;

            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; 
            }
            pCrawl = pCrawl->next;
        }
    }
    
    printf("\nShortest Travel Times from Source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] != INT_MAX) {
            printf("  Hospital %d: %d minutes\n", i, dist[i]);
            printf("  Optimal Path: ");
            int curr = i;
            int path[V], path_index = 0;
            while (curr != -1) {
                path[path_index++] = curr;
                curr = parent[curr];
            }
            for (int j = path_index - 1; j >= 0; j--) {
                printf("%d%s", path[j], (j > 0) ? " -> " : "");
            }
            printf("\n");
        } else {
            printf("  Hospital %d: Not Reachable\n", i);
        }
    }
}

int main() {
    int V = 6; // 6 Intersections (Nodes 0 to 5), say Node 5 is the hospital.
    Graph graph = { .V = V };
    for (int i = 0; i < V; i++) graph.adj[i] = NULL;

    // Initial road network (travel times in minutes)
    addEdge(&graph, 0, 1, 4); addEdge(&graph, 0, 2, 2);
    addEdge(&graph, 1, 3, 5); addEdge(&graph, 2, 4, 3);
    addEdge(&graph, 3, 5, 2); addEdge(&graph, 4, 3, 1);
    addEdge(&graph, 4, 5, 6);

    int ambulance_start = 0; // Source (S)
    int hospital_dest = 5;   // Destination (D)

    printf("--- Initial Shortest Path Calculation ---\n");
    dijkstra(&graph, ambulance_start);
    
    // Dynamic Weight Update (Simulating a traffic jam on road 2->4)
    updateWeight(&graph, 2, 4, 15); // Congestion! Time increases from 3 to 15 mins

    printf("\n\n--- Recalculated Shortest Path After Traffic Update ---\n");
    dijkstra(&graph, ambulance_start);

    return 0;
}