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

int get_queue_with_highest_priority_containing_process()
{
    for (int priority = 0; priority <= queue_count; priority++)
    {
        for (int index = 0; index < processes_count; index++)
        {
            if (process[index].queue == priority && (process[index].burst > 0) && total_time >= process[index].arrival)
            {
                return process[index].queue;
            }
        }
    }
}

void execute_processes()
{
    while (!all_processes_completed())
    {
        if (!all_arrived_processes_completed())
        {
            short int queue_id;
            for (short int process_id = 0; process_id < processes_count; process_id++)
            {
                queue_id = get_queue_with_highest_priority_containing_process();
                if ((process[process_id].burst > 0) && (total_time >= process[process_id].arrival) && (process[process_id].queue == queue_id))
                {
                    for (short int time_q = 0; time_q < time_quantum; time_q++)
                    {
                        //execution
                    }
                }
            }
        }
        else
        {
            ++total_time;
        }
    }
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
