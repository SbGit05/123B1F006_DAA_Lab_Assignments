// Movie Recommendation System Optimization 
// A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies 
// based on user preferences, such as IMDB rating, release year, or watch time popularity. 
// However, during peak hours, sorting large datasets slows down the system. 
// As a backend engineer, you must: 
// ● Implement Quicksort to efficiently sort movies based on various user-selected 
// parameters. 
// ● Handle large datasets containing of  movies while maintaining fast response times 

//Shreedhar Bargaje- 123B1F006 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[50];
    float imdb_rating; 
    int release_year;  
    long watch_count;  
} Movie;

int sort_param = 1;

void swap(Movie* a, Movie* b) {
    Movie t = *a;
    *a = *b;
    *b = t;
}

int compareMovies(Movie a, Movie b) {
    if (sort_param == 1) { // Sort by IMDB Rating (Descending)
        return (a.imdb_rating < b.imdb_rating);
    } else if (sort_param == 2) { // Sort by Release Year (Descending)
        return (a.release_year < b.release_year);
    } else if (sort_param == 3) { // Sort by Watch Count (Descending)
        return (a.watch_count < b.watch_count);
    }
    return 0; // Default: no swap
}

int partition(Movie arr[], int low, int high) {
    Movie pivot = arr[high]; 
    int i = (low - 1);       

    for (int j = low; j <= high - 1; j++) {
        if (compareMovies(arr[j], pivot)) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Movie arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printMovies(Movie arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%-30s | Rating: %.1f | Year: %d | Watched: %ld\n", 
               arr[i].title, arr[i].imdb_rating, arr[i].release_year, arr[i].watch_count);
    }
}

#define MAX_MOVIES 5

int main() {
    Movie movies[MAX_MOVIES] = {
        {1, "The Great Movie", 8.5, 2020, 500000},
        {2, "Comedy Hit", 7.2, 2023, 1200000},
        {3, "Old Classic", 9.0, 1995, 300000},
        {4, "Sci-Fi Saga", 8.8, 2018, 800000},
        {5, "Recent Flop", 6.5, 2024, 100000}
    };
    int n = MAX_MOVIES;

    sort_param = 1;
    printf("--- Sorted by IMDB Rating (Descending) ---\n");
    quickSort(movies, 0, n - 1);
    printMovies(movies, n);

    printf("\n" "------------------------------------------------------" "\n");

    sort_param = 2;
    printf("--- Sorted by Release Year (Descending) ---\n");

    quickSort(movies, 0, n - 1);
    printMovies(movies, n);

    return 0;

}

//--- Sorted by IMDB Rating (Descending) ---
//Recent Flop                    | Rating: 6.5 | Year: 2024 | Watched: 100000
//Comedy Hit                     | Rating: 7.2 | Year: 2023 | Watched: 1200000
//The Great Movie                | Rating: 8.5 | Year: 2020 | Watched: 500000
//Sci-Fi Saga                    | Rating: 8.8 | Year: 2018 | Watched: 800000
//Old Classic                    | Rating: 9.0 | Year: 1995 | Watched: 300000

//------------------------------------------------------
//--- Sorted by Release Year (Descending) ---
//Old Classic                    | Rating: 9.0 | Year: 1995 | Watched: 300000
//Sci-Fi Saga                    | Rating: 8.8 | Year: 2018 | Watched: 800000
//The Great Movie                | Rating: 8.5 | Year: 2020 | Watched: 500000
//Comedy Hit                     | Rating: 7.2 | Year: 2023 | Watched: 1200000
//Recent Flop                    | Rating: 6.5 | Year: 2024 | Watched: 100000
