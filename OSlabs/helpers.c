#include "helpers.h"

void calc_waiting_time(process *proc_queue, int *wtime, int *comptime, int qsize) {
  char check = 0;
  int i, finish_time;
  int complete = 0, shortest = 0;
  int timelap = 0;
  int min_time = INT_MAX;
  int rtime[qsize];


  for (i = 0; i < qsize; ++i) 
    rtime[i] = proc_queue[i].burst_time;

  // Process until all work gets done
  while (complete != qsize) {
    for (i = 0; i < qsize; ++i) {
      if ((proc_queue[i].arrival_time <= timelap)
      && (rtime[i] < min_time) && (rtime[i] > 0)) {
        shortest = i;
        min_time = rtime[i];
        check = 1;
      }
    }

    if (!check) {
      timelap++;
      continue;
    }

    rtime[shortest]--;
    min_time = (rtime[shortest] == 0) ? INT_MAX : rtime[shortest];
    if (rtime[shortest] == 0) {
      complete++;
      finish_time = timelap + 1;
      comptime[shortest] = finish_time;
      wtime[shortest] = finish_time - proc_queue[shortest].burst_time 
                                    - proc_queue[shortest].arrival_time;


      if (wtime[shortest] < 0)
        wtime[shortest] = 0;
    }

    timelap++;
  }
}

void calc_turn_around_time(process *proc_queue, int qsize, int *wtime, int *trtime) {
  int i;
  for (i = 0; i < qsize; ++i)
    trtime[i] = proc_queue[i].burst_time + wtime[i];
  
}

void calc_average_time(process *proc_queue, int qsize) {
  int i, total_wtime = 0, total_trtime = 0;
  int wtime[qsize];
  int trtime[qsize];
  int comptime[qsize];

  calc_waiting_time(proc_queue, wtime, comptime, qsize);
  calc_turn_around_time(proc_queue, qsize, wtime, trtime);

  printf("\nProcesses  Burst time  Waiting time  Turn around time  Arrival time  Finish time\n");
  for (i = 0; i < qsize; ++i) {
    total_wtime = total_wtime + wtime[i];
    total_trtime = total_trtime + trtime[i];
    printf(" %i\t\t%i\t\t%i\t\t%i\t\t%i\t%i\n", proc_queue[i].process_id, 
                                    proc_queue[i].burst_time,
                                    wtime[i], trtime[i], proc_queue[i].arrival_time,
                                    comptime[i]);
  }
  printf("\nAvr. waiting time: %.2f\n", (float)total_wtime / qsize);
  printf("Avr. turn around time: %.2f\n\n", (float)total_trtime / qsize);

}