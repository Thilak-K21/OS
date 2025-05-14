#include <stdio.h>

int search(int key, int frame[], int size) {
    for (int i = 0; i < size; i++) {
        if (frame[i] == key)
            return 1;
    }
    return 0;
}

void simulateFIFO(int pages[], int n, int frameSize) {
    int frame[frameSize], front = 0, faults = 0, hits = 0;

    for (int i = 0; i < frameSize; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, frameSize)) {
            frame[front] = pages[i];
            front = (front + 1) % frameSize;
            faults++;
        } else {
            hits++;
        }
    }

    printf("FIFO Page Faults: %d, Page Hits: %d\n", faults, hits);
}

int main() {
    int n, frameSize;

    printf("Enter the size of the pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page strings: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the no of page frames: ");
    scanf("%d", &frameSize);

    simulateFIFO(pages, n, frameSize);

    return 0;
}
