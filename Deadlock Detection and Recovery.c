#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Example data (change as necessary)
int available[NUM_RESOURCES] = {3, 3, 2};
int maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[NUM_PROCESSES][NUM_RESOURCES];

// Calculate the Need matrix: need[i][j] = maximum[i][j] - allocation[i][j]
void calculateNeed() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Check if the system is in a safe state using Banker's Algorithm
bool isSafe() {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES] = {false};

    // Initialize work to available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++) {
            if (!finish[p]) {
                bool canProceed = true;
                // Check if the process can finish with available resources
                for (int r = 0; r < NUM_RESOURCES; r++) {
                    if (need[p][r] > work[r]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    // Release allocated resources and mark process as finished
                    for (int r = 0; r < NUM_RESOURCES; r++) {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break; // No process found that can proceed with available resources
        }
    }

    // If all processes are finished, system is in a safe state
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false; // System is not in a safe state
        }
    }
    return true; // System is in a safe state
}

// Attempt to recover from deadlock by terminating processes
void recoverFromDeadlock() {
    bool deadlockDetected = false;
    for (int p = 0; p < NUM_PROCESSES; p++) {
        if (!isSafe()) {
            // Detected deadlock, terminate process p and reclaim its resources
            printf("Deadlock detected. Terminating process %d to recover.\n", p);
            for (int r = 0; r < NUM_RESOURCES; r++) {
                available[r] += allocation[p][r];
                allocation[p][r] = 0;
                need[p][r] = maximum[p][r];
            }
            deadlockDetected = true;
        }
    }
    if (deadlockDetected) {
        printf("Deadlock recovered.\n");
    } else {
        printf("No deadlock detected.\n");
    }
}

int main() {
    calculateNeed();

    if (!isSafe()) {
        printf("System is not in a safe state. Attempting to recover...\n");
        recoverFromDeadlock();
    } else {
        printf("System is in a safe state.\n");
    }

    return 0;
}


