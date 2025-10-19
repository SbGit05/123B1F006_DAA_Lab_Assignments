#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    double weight; 
    double value; 
    double ratio;
} Item;

int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

double fractionalKnapsack(Item items[], int n, double W) {
    for (int i = 0; i < n; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }

    qsort(items, n, sizeof(Item), compareItems);

    double current_weight = 0.0;
    double total_utility = 0.0; 
    double remaining_capacity = W;

    printf("Item Selection Process:\n");
    for (int i = 0; i < n; i++) {
        if (remaining_capacity <= 0) {
            break; // Boat is full
        }

        Item current = items[i];
        
        // If the entire item fits in the boat
        if (current.weight <= remaining_capacity) {
            remaining_capacity -= current.weight;
            total_utility += current.value;
            printf("  - Took all of %s (Weight: %.2f, Utility: %.2f)\n", 
                   current.name, current.weight, current.value);
        } 
        // If only a fraction of the item fits
        else {
            double fraction = remaining_capacity / current.weight;
            double utility_gain = current.value * fraction;

            total_utility += utility_gain;
            remaining_capacity = 0; // Boat is now full
            printf("  - Took %.2f%% of %s (Weight: %.2f, Utility: %.2f)\n", 
                   fraction * 100, current.name, current.weight * fraction, utility_gain);
            break; // Stop here as the boat is full
        }
    }

    return total_utility;
}


#define MAX_ITEMS 5
#define MAX_CAPACITY 50.0

int main() {
    Item supplies[MAX_ITEMS] = {
        {"Medicine Kit",     10.0,      100.0},
        {"Drinking Water",   30.0,      150.0}, 
        {"Protein Bars",     20.0,       80.0}, 
        {"Blankets",         15.0,       30.0}, 
        {"Tents",            25.0,      100.0}
    };
    int n = MAX_ITEMS;
    double capacity = MAX_CAPACITY;

    printf("Boat Capacity (W): %.2f kg\n\n", capacity);

    double max_utility = fractionalKnapsack(supplies, n, capacity);

    printf("\nTotal Maximum Utility Achieved: %.2f\n", max_utility);

    return 0;
}