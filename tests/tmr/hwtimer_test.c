#include "tmr/hwtimer.h"
#include <stdio.h>
#include <time.h>
#include <sched.h>

void
hwt_cb ( void *p )
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  printf("%ld.%09ld timer tick\n", ts.tv_sec, ts.tv_nsec);
}

int
main ( int argc, char **argv )
{
  timer_s hwt = TIMER_INIT(hwt_cb, NULL);

  hwtimer_init();
  hwtimer_arm(&hwt, 200000);

  while (true) {
    sched_yield();
  }
  
  return 0;
}
