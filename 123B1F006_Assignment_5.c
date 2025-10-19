#include <stdio.h>
#include <limits.h>

#define N 12
#define STAGES 4 
#define INF INT_MAX

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to solve the Multistage Graph shortest path problem using DP
void multistageGraphShortestPath(int cost[N][N], int num_nodes) {
    
    int dist[N]; 
    int d[N];    

    dist[num_nodes - 1] = 0;
    d[num_nodes - 1] = num_nodes - 1;

    for (int i = num_nodes - 2; i >= 0; i--) {
        dist[i] = INF;
        
        for (int j = 0; j < num_nodes; j++) {
            if (cost[i][j] != 0 && cost[i][j] != INF) {

                if (cost[i][j] + dist[j] < dist[i]) {
                    dist[i] = cost[i][j] + dist[j];
                    d[i] = j; 
                }
            }
        }
    }

    printf("Optimal Cost/Time from Source (0) to Destination (%d): %d\n", num_nodes - 1, dist[0]);
    printf("Optimal Route: ");
    int curr = 0;
    while (curr != num_nodes - 1) {
        printf("%d -> ", curr);
        curr = d[curr];
    }
    printf("%d\n", num_nodes - 1);
}

int main() {
    int cost[N][N] = {
        // Stage 1 -> Stage 2
        {0, 9, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0}, // 0 (Source)
        // Stage 2 -> Stage 3
        {INF, 0, 0, 0, 4, 2, 1, 0, 0, 0, 0, 0}, // 1
        {INF, 0, 0, 0, 0, 3, 0, 5, 0, 0, 0, 0}, // 2
        {INF, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0}, // 3
        // Stage 3 -> Stage 4
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0}, // 4
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0}, // 5
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0}, // 6
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0}, // 7
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0}, // 8
        // Final Stage -> Destination
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}, // 9
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, // 10
        // Destination (Node 11)
        {INF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 11
    };

    multistageGraphShortestPath(cost, N);

    return 0;
}