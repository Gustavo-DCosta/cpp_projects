#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateNumbers(int min, int max, int count) {
    printf("Generating %d random numbers between %d and %d\n", count, min, max);

    FILE *ptr = fopen("guessingNumbers.txt", "w");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        int die = min + rand() % (max - min + 1);
        fprintf(ptr, "%d\n", die);
    }

    fclose(ptr);
    printf("Numbers generated successfully\n");
}

void analyzeFrequency() {
    FILE *fptr = fopen("guessingNumbers.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file for analysis!\n");
        exit(1);
    }

    // Array to store frequencies (index 0 will be unused)
    int frequencies[7] = {0};  // Size 7 for numbers 1-6
    int number;

    // Read numbers one by one and count frequencies
    while (fscanf(fptr, "%d", &number) == 1) {
        if (number >= 1 && number <= 6) {
            frequencies[number]++;
        }
    }

    fclose(fptr);

    // Print frequency analysis
    printf("\nFrequency Analysis:\n");
    printf("------------------\n");
    for (int i = 1; i <= 6; i++) {
        printf("Number %d: %d times (%.2f%%)\n",
               i, frequencies[i],
               (float)frequencies[i] / 100.0);
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    int min = 1, max = 6, count = 10000;
    generateNumbers(min, max, count);
    analyzeFrequency();

    return 0;
}