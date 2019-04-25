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

void update_waiting_time(short int process_id)
{
    for (short int index = 0; index < processes_count; index++)
    {
        if ((index != process_id) && (total_time > process[index].arrival) && (process[index].burst > 0))
        {
            ++process[index].waiting;
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
                        --process[process_id].burst;
                        ++total_time;
                        printf("\nProcess %d executing...", process_id);
                        Sleep(1000);

                        update_waiting_time(process_id);

                        if (process[process_id].burst == 0)
                        {
                            process[process_id].completion = total_time;
                            process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
                            printf("\nProcess %d executed", process_id);
                            break;
                        }

                        if (get_queue_with_highest_priority_containing_process() < process[process_id].queue)
                        {
                            break;
                        }
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

void display_data()
{
    system("cls");
    printf("\n\nProcess     :  Arival\t Burst\t Queue\t Compt\t Turn\t Waiting\t\n");
    printf("__________________________________________________________________\n");
    for (short int index = 0; index < processes_count; index++)
    {
        printf("Process %d   :  %d\t %d\t %d\t %d\t %d\t %d\n\n", index, process[index].arrival, process[index].burst_backup, process[index].queue, process[index].completion, process[index].turn_around, process[index].waiting);
    }

    printf("\n__________________________________________________________________\n");

    float total_turnaround_time = 0, total_waiting_time = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        total_turnaround_time += process[index].turn_around;
    }
    total_turnaround_time /= processes_count;

    for (short int index = 0; index < processes_count; index++)
    {
        total_waiting_time += process[index].waiting;
    }
    total_waiting_time /= processes_count;

    printf("\nAverage Turn around Time : %.2f\n", total_turnaround_time);
    printf("\nAverage Waiting Time : %.2f\n\n\n", total_waiting_time);
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
    printf("Execution Started : \n");
    execute_processes();
    printf("\n\nAll Processes executed\n\n");
    system("pause");
    display_data();
    system("pause");
}
