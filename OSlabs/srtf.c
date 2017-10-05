#include "helpers.h"

int main() {
  process proc_arr[] = { { 1, 2, 1 }, { 2, 8, 1 },
                         { 3, 7, 2 }, { 4, 3, 3 }, 
                         { 5, 10, 3 },{ 6, 1, 8 } 
                        };
  int arr_size = sizeof(proc_arr) / sizeof(proc_arr[0]);
  calc_average_time(proc_arr, arr_size);
  return 0;
}