#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

void calculateNeed(int m, int n, int max[m][n], int alloc[m][n], int need[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isRequestGrantable(int m, int n, int available[n], int need[m][n], int alloc[m][n], int process, int request[n]) {

    for (int i = 0; i < n; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

 
    for (int i = 0; i < n; i++) {
        if (request[i] > available[i]) {
            printf("Resources are not available.\n");
            return false;
        }
    }


    for (int i = 0; i < n; i++) {
        available[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }


    bool finish[m];
    for (int i = 0; i < m; i++) finish[i] = false;

    int work[n];
    for (int i = 0; i < n; i++) work[i] = available[i];

    int count = 0;
    while (count < m) {
        bool found = false;
        for (int p = 0; p < m; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < n; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < n; j++) {
                        work[j] += alloc[p][j];
                    }
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
        
            for (int i = 0; i < n; i++) {
                available[i] += request[i];
                alloc[process][i] -= request[i];
                need[process][i] += request[i];
            }
            printf("The system is not in a safe state after granting the request.\n");
            return false;
        }
    }

    printf("The request can be granted immediately.\n");
    return true;
}

int main() {
    int m, n;

    printf("Enter the number of processes: ");
    scanf("%d", &m);
    printf("Enter the number of resource types: ");
    scanf("%d", &n);

    int available[n];
    printf("Enter the number of available instances for each resource type:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &available[i]);
    }

    int max[m][n], alloc[m][n], need[m][n];
    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    calculateNeed(m, n, max, alloc, need);

    printf("The Need matrix is:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int process;
    printf("Enter the process number making the request: ");
    scanf("%d", &process);

    int request[n];
    printf("Enter the request for resources:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    isRequestGrantable(m, n, available, need, alloc, process, request);

    return 0;   
}