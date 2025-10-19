#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10

typedef struct {
    char name[50];
    int weight;
    int utility;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(Item items[], int n, int W, int dp[MAX_ITEMS+1][MAX_ITEMS+1]) {

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i-1].weight <= w) {
                dp[i][w] = max(dp[i-1][w],
                               dp[i-1][w - items[i-1].weight] + items[i-1].utility);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][W];
}

void findSelectedItems(Item items[], int n, int W, int dp[MAX_ITEMS+1][MAX_ITEMS+1]) {
    int w = W;
    printf("\nItems Selected for the Truck:\n");
    printf("------------------------------\n");
    int total_weight = 0;
    
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("- %s (Weight: %d kg, Utility: %d)\n", 
                   items[i-1].name, items[i-1].weight, items[i-1].utility);
            
            w -= items[i-1].weight;
            total_weight += items[i-1].weight;
        }
    }
    printf("------------------------------\n");
    printf("Total Weight Carried: %d kg\n", total_weight);
    printf("Remaining Truck Capacity: %d kg\n", W - total_weight);
}

int main() {
    int n, W;
    Item items[MAX_ITEMS];
    
    int dp[MAX_ITEMS+1][MAX_ITEMS+1]; 

    printf("--- Disaster Relief Resource Allocation ---\n\n");
    
    printf("Enter number of item types (max %d): ", MAX_ITEMS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_ITEMS) {
        printf("Invalid number of items.\n"); return 1;
    }

    printf("Enter truck capacity (W in kg, max %d): ", MAX_ITEMS);
    if (scanf("%d", &W) != 1 || W < 1 || W > MAX_ITEMS) {
        printf("Invalid capacity W. Max is %d for this simulation.\n", MAX_ITEMS); return 1;
    }

    while (getchar() != '\n'); 

    for (int i = 0; i < n; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("  Name: ");
        if (fgets(items[i].name, sizeof(items[i].name), stdin) == NULL) {
            printf("Error reading name.\n"); return 1;
        }
        items[i].name[strcspn(items[i].name, "\n")] = 0; 

        printf("  Weight (kg): ");
        scanf("%d", &items[i].weight);

        printf("  Utility value: ");
        scanf("%d", &items[i].utility);

        while (getchar() != '\n'); 
    }
    
    int maxUtility = knapsack(items, n, W, dp);

    printf("\n============================================\n");
    printf("Maximum Utility achieved: %d\n", maxUtility);
    printf("============================================\n");
    
    findSelectedItems(items, n, W, dp);

    return 0;
}