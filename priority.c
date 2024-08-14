#include <stdio.h>
#include <stdbool.h>

struct Process {
    int name;
    int burstTime;
    int arrivalTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int priority;
    bool executed;
}p[20], temp;
void main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
     for(int i = 0; i < n; i++){
        printf("Enter process details (priority, arrival time, burst time):\n");
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &p[i].priority, &p[i].arrivalTime, &p[i].burstTime);
        p[i].executed = false;
        p[i].name = i + 1;
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if((p[j].arrivalTime > p[j + 1].arrivalTime) || (p[j].arrivalTime == p[j + 1].arrivalTime && p[j].priority > p[j + 1].priority)) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int time = 0, executedCount = 0;
    float wait = 0.0, turnaround = 0.0;
    printf("P\tPR\tAT\tBT\tCT\tTAT\tWT\n");
    while (executedCount < n) {
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].executed && p[i].arrivalTime <= time) {
                if (minIndex == -1 || p[i].priority < p[minIndex].priority) 
                    minIndex = i;
            }
        }

        if (minIndex != -1) {
            if (p[minIndex].arrivalTime > time)
                time = p[minIndex].arrivalTime;
            p[minIndex].executed = true;
            time += p[minIndex].burstTime;
            p[minIndex].completionTime = time;
            p[minIndex].turnaroundTime = p[minIndex].completionTime - p[minIndex].arrivalTime;
            p[minIndex].waitingTime = p[minIndex].turnaroundTime - p[minIndex].burstTime;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[minIndex].name, p[minIndex].priority, p[minIndex].arrivalTime, p[minIndex].burstTime, p[minIndex].completionTime, p[minIndex].turnaroundTime, p[minIndex].waitingTime);
            wait += p[minIndex].waitingTime;
            turnaround += p[minIndex].turnaroundTime;
            executedCount++;
        }
        else
            time++;
    }
    printf("Average Waiting Time=%f\n",wait/n);
    printf("Average turnaround Time=%f\n",turnaround/n);
}
