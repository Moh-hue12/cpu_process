#include "utils.h"

void print_results(Process p[], int n, const char *def) {
  printf("\n================= %s =================\n", def);
  printf("\nP   | AT | BT | CT | TAT | WT | RT\n");
  printf("------------------------------------\n");
  float sum_tat = 0, sum_wt = 0, sum_rt = 0;
  for (int i = 0; i < n; i++) {
    printf("P%-2d | %-2d | %-2d | %-2d | %-3d | %-2d | %-2d\n",
           p[i].id, p[i].arrival_time, p[i].execution_timet,
           p[i].completion_timet, p[i].turnaroundtime,
           p[i].waiting_timet, p[i].respanse_time);
    printf("------------------------------------\n");
    sum_tat += p[i].turnaroundtime;
    sum_wt  += p[i].waiting_timet;
    sum_rt  += p[i].respanse_time;
  }
  printf("Average TAT = %.2f\n", sum_tat / n);
  printf("Average WT  = %.2f\n", sum_wt / n);
  printf("Average RT  = %.2f\n", sum_rt / n);
}
