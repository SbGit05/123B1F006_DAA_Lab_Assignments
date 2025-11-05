// Scenario: Emergency Relief Supply Distribution 
// A devastating flood has hit multiple villages in a remote area, and the government, along 
// with NGOs, is organizing an emergency relief operation. A rescue team has a limited
// capacity boat that can carry a maximum weight of W kilograms. The boat must transport 
// critical supplies, including food, medicine, and drinking water, from a relief center to the 
// affected villages. 
// Each type of relief item has: 
// ● A weight (wi) in kilograms. 
// ● Utility value (vi) indicating its importance (e.g., medicine has higher value than food). 
// ● Some items can be divided into smaller portions (e.g., food and water), while others must 
// be taken as a whole (e.g., medical kits). 
// As the logistics manager, you must: 
// 1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the 
// supplies transported. 
// 2. Prioritize high-value items while considering weight constraints. 
// 3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets). 
// 4. Ensure that the boat carries the most critical supplies given its weight limit W. 

//Shreedhar Bargaje- 123B1F006

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

//Boat Capacity (W): 50.00 kg

//Item Selection Process:
  //- Took all of Medicine Kit (Weight: 10.00, Utility: 100.00)
  //- Took all of Drinking Water (Weight: 30.00, Utility: 150.00)
  //- Took 50.00% of Protein Bars (Weight: 10.00, Utility: 40.00)

//Total Maximum Utility Achieved: 290.00
