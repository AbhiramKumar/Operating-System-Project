#include <iostream>
#include <stdio.h>
#include <Windows.h>

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, queue;
} * process;

short int total_time = 0, time_quantum = 2, processes_count, queue_count;

int get_max_queue()
{
    int max = 0;
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].queue > max)
        {
            max = process[index].queue;
        }
    }

    return max;
}

bool all_arrived_processes_completed()
{
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 && total_time >= process[index].arrival)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool all_processes_completed()
{
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

int main()
{
    printf("Enter Processes Count : ");
    scanf("%d", &processes_count);
    process = new processes[processes_count];
    printf("\nEnter Foramt AT BT QN (Starts from 0)\n");

    for (short int index = 0; index < processes_count; index++)
    {
        printf("\nP%d details : ", index);
        scanf("%d %d %d", &process[index].arrival, &process[index].burst, &process[index].queue);
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    queue_count = get_max_queue();
    system("pause");
}
