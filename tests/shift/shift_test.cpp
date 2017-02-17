#include "tmr/swtimer.h"
#include "tmr/hwtimer.h"
#include "sched/sched.h"
#include "log/log_stdout.h"
#include "util/clock.h"
#include "periph/shift.h"

#include "Arduino.h"
#include <SPI.h>

#define LED_PIN   (7)
#define DATA_PIN  (11)
#define CLOCK_PIN (13)
#define LATCH_PIN (4)

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

int8_t dc = 0;

static void
swt_cb ( void *p )
{
  uint8_t i, d;
  dc = (dc + 1) & 0x3F;
  d  = ABS(dc - 32);
  for (i = 0; i < 8; i++) {
    shift_set_pwm(i, d);
  }
  l_info("dc = %d", (int)d);
}

void
setup ( void )
{
  static timer_s swt = TIMER_INIT(swt_cb, NULL);
  sched_init();
  hwtimer_init();
  swtimer_init();
  log_stdout_init();
  shift_init(true, DATA_PIN, CLOCK_PIN, LATCH_PIN, 8);

  swtimer_arm(&swt, 100, true);
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
