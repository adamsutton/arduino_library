#include "core/hwtimer.h"
#include "core/sched.h"
#include "core/clock.h"
#include "core/log/log_stdout.h"

void
hwt_cb ( void *p )
{
  l_info("tick");
}

void
setup ( void )
{
  static timer_s hwt = TIMER_INIT(hwt_cb, NULL);
  hwtimer_init();
  hwtimer_arm(&hwt, 200000, false);
  log_stdout_init();
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
