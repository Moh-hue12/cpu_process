#include "utils.h"

void print_results(Process p[], int n, char *def) {
  printf("\n================= %s =================\n", def);

  // Table header
  printf("\nP   | AT | BT | CT | TAT | WT | RT\n");
  printf("------------------------------------\n");

  float sum_tat = 0, sum_wt = 0, sum_rt = 0;
  for (int i = 0; i < n; i++) {
    printf("P%-2d | %-2d | %-2d | %-2d | %-3d | %-2d | %-2d\n", p[i].id,
           p[i].at, p[i].et, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    printf("------------------------------------\n");
    sum_tat += p[i].tat;
    sum_wt += p[i].wt;
    sum_rt += p[i].rt;
  }

  printf("Average TAT = %.2f\n", sum_tat / n);
  printf("Average WT  = %.2f\n", sum_wt / n);
  printf("Average RT  = %.2f\n", sum_rt / n);
}
