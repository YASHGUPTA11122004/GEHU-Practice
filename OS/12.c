#include <stdio.h>

void fcfsPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }
    
    int pageFaults = 0;
    int pageCount = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;
        
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            frame[pageCount % capacity] = page;
            pageFaults++;
            pageCount++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }
    
    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fcfsPageReplacement(pages, n, capacity);
    return 0;
}


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
