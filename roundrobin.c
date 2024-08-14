#include <stdio.h>
struct process{
    int name;
    int burstTime;
    int completionTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
}p[20];
int q[100], rear = -1, front = -1;
void enqueue(int item){
	if (front == -1 && rear == -1)
		front++;
	q[++rear] = item;
}
int dequeue(){
	int item;
	if (front == -1)
		return -1;
	else if (front == rear){
		item = q[front];
		front = rear = -1;
	}
	else
		item = q[front++];
    return item;
}
void main(){
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    for(int i = 0; i < n; i++){
        printf("Enter process details (burst time):\n");
        printf("P%d: ", i);
        scanf("%d", &p[i].burstTime);
        p[i].name = i;
        p[i].remainingTime = p[i].burstTime;
        enqueue(p[i].name);
    }
    int time = 0, i = 0;
    float wait = 0, turnaround = 0.0;
    printf("P\tBT\tCT\tTAT\tWT\n");
    while(front != -1){
        i = dequeue();
        if(p[i].remainingTime <= quantum){
            time += p[i].remainingTime;
            p[i].completionTime = time;
            p[i].turnaroundTime = p[i].completionTime;
            p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
            wait += p[i].waitingTime;
            turnaround += p[i].turnaroundTime;
            printf("P%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].burstTime, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
        }
        else{
            time += quantum;
            p[i].remainingTime -= quantum;
            enqueue(p[i].name);
        }
    }
    printf("Average Waiting Time=%f\n",wait/n);
    printf("Average turnaround Time=%f\n",turnaround/n);
}
