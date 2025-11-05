// Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer 
// orders based on their timestamps. The solution should handle a large dataset (up to 1 million 
// orders) with minimal computational overhead. Additionally, analyze the time complexity and 
// compare it with traditional sorting techniques.

//Shreedhar Bargaje- 123B1F006 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long order_id;
    time_t timestamp; 
    double amount;
} Order;

void merge(Order arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Order *L = (Order *)malloc(n1 * sizeof(Order));
    Order *R = (Order *)malloc(n2 * sizeof(Order));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Order arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void printOrders(Order arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %ld, Time: %ld, Amount: %.2f\n", arr[i].order_id, arr[i].timestamp, arr[i].amount);
    }
}

#define MAX_ORDERS 10 

int main() {
    Order orders[MAX_ORDERS] = {
        {101, 1635724800, 45.50}, // Nov 1, 2021
        {105, 1635728400, 20.00}, // Nov 1, 2021 + 1hr
        {103, 1635811200, 100.25},// Nov 2, 2021
        {102, 1635725400, 60.00}, // Nov 1, 2021 + 10min
        {104, 1635811000, 75.99} // Nov 2, 2021 - 200s
    };
    int n = 5; 

    printf("--- Unsorted Orders ---\n");
    printOrders(orders, n);

    mergeSort(orders, 0, n - 1);

    printf("\n--- Sorted Orders by Timestamp ---\n");
    printOrders(orders, n);

    return 0;

}
