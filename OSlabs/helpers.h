#pragma once
#include <stdio.h>
#include <limits.h>

typedef struct {
  int process_id;
  int burst_time;
  int arrival_time;
} process;


void calc_waiting_time(process *proc_queue, int *wtime, int *comptime, int qsize);
void calc_turn_around_time(process *proc_queue, int qsize, int *wtime, int *trtime);
void calc_average_time(process *proc_queue, int qsize);