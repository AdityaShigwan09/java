#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void SSTF(int requests[], int n, int head) {
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int totalHeadMovements = 0;
    int currentHead = head;

    printf("Order of requests served: ");
    for (int i = 0; i < n; i++) {
        int closest = -1;
        int minDistance = __INT_MAX__;

        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - currentHead);
                if (distance < minDistance) {
                    minDistance = distance;
                    closest = j;
                }
            }
        }

        // Serve the closest request
        visited[closest] = true;
        totalHeadMovements += minDistance;
        currentHead = requests[closest];
        printf("%d ", requests[closest]);
    }

    printf("\nTotal head movements: %d\n", totalHeadMovements);
}

int main() {
    int n;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head;
    printf("Enter the starting head position: ");
    scanf("%d", &head);

    SSTF(requests, n, head);

    return 0;
}