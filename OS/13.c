#include <stdio.h>

void lruPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity], lastUsed[capacity];
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                pageFound = 1;
                lastUsed[j] = time;
                break;
            }
        }

        if (!pageFound) {
            int lruIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            frame[lruIndex] = page;
            lastUsed[lruIndex] = time;
            pageFaults++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");

        time++;
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of page references: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page references: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames (capacity): ");
    scanf("%d", &capacity);

    lruPageReplacement(pages, n, capacity);
    return 0;
}


// Enter the number of page references: 10
// Enter the page references: 7 0 1 2 0 3 0 4 2 3
// Enter the number of frames (capacity): 3
// Step 1: 7 
// Step 2: 7 0 
// Step 3: 7 0 1 
// Step 4: 2 0 1 
// Step 5: 2 0 1 
// Step 6: 2 0 3 
// Step 7: 0 3 1 
// Step 8: 0 3 4 
// Step 9: 0 4 2 
// Step 10: 3 4 2 
// Total page faults: 8
