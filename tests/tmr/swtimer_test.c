#include "tmr/swtimer.h"
#include "tmr/hwtimer.h"
#include "sched/sched.h"
#include "log/log_stdout.h"
#include "util/clock.h"

void
swt_cb ( void *p )
{
  l_info("tick");
}

void
setup ( void )
{
  static timer_s swt = TIMER_INIT(swt_cb, NULL);
  sched_init();
  hwtimer_init();
  swtimer_init();
  log_stdout_init();
  swtimer_arm(&swt, 500, true);
}

void
loop ( void )
{
  while (1) {
    sched_step();
    wait_micros(10);
  }
}

#ifdef TARGET_linux
void
main ( void )
{
  setup();
  loop();
}
#endif
