#include "tmr/swtimer.h"
#include "tmr/hwtimer.h"
#include "sched/sched.h"
#include <stdio.h>
#include <time.h>
#include <sched.h>

void
swt_cb ( void *p )
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  printf("%ld.%09ld timer tick\n", ts.tv_sec, ts.tv_nsec);
}

int
main ( int argc, char **argv )
{
  timer_s swt = TIMER_INIT(swt_cb, NULL);

  sched_init();
  hwtimer_init();
  swtimer_init();

  swtimer_arm(&swt, 500, true);

  sched_run();
  
  return 0;
}
