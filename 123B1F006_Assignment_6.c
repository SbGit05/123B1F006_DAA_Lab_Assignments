// Scenario: Disaster Relief Resource Allocation 
// A massive earthquake has struck a remote region, and a relief organization is transporting 
// essential supplies to the affected area. The organization has a limited-capacity relief truck that 
// can carry a maximum weight of W kg. They have N different types of essential items, each 
// with a specific weight and an associated utility value (importance in saving lives and meeting 
// urgent needs). 
// Since the truck has limited capacity, you must decide which items to include to maximize the 
// total utility value while ensuring the total weight does not exceed the truck's limit. 
// Your Task as a Logistics Coordinator: 
// 1. Model this problem using the 0/1 Knapsack approach, where each item can either be 
// included in the truck (1) or not (0). 
// 2. Implement an algorithm to find the optimal set of items that maximizes utility while 
// staying within the weight constraint. 
// 3. Analyze the performance of different approaches (e.g., Brute Force, Dynamic 
// Programming, and Greedy Algorithms) for solving this problem efficiently. 
// 4. Optimize for real-world constraints, such as perishable items (medicines, food) having 
// priority over less critical supplies. 
// Extend the model to consider multiple trucks or real-time decision-making for dynamic supply 
// chain management. 

//Shreedhar Bargaje- 123B1F006

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
