#include "core/sched.h"
#include "core/stdout.h"
#include "core/clock.h"
#include "core/log/log_stdout.h"

void a_cb ( void ) { l_info("%s 0", __func__); };
void b_cb ( void ) { l_info("%s 0", __func__); };
void c_cb ( void ) { l_info("%s 1", __func__); };
void d_cb ( void ) { l_info("%s 1", __func__); };
void e_cb ( void ) { l_info("%s 2", __func__); };
void f_cb ( void ) { l_info("%s 2", __func__); };

void
setup ( void )
{
  static task_t a = TASK_INIT(a_cb),
                b = TASK_INIT(b_cb),
                c = TASK_INIT(c_cb),
                d = TASK_INIT(d_cb),
                e = TASK_INIT(e_cb),
                f = TASK_INIT(f_cb);

  sched_init();
  stdout_init();
  log_stdout_init();

  l_info("setup...");

  sched_add(&a, 0, true);
  sched_add(&b, 0, true);
  sched_add(&c, 1, true);
  sched_add(&d, 1, true);
  sched_add(&e, 2, true);
  sched_add(&f, 2, true);
}

void
loop ( void )
{
  l_info("run...");
  while (1) {
    wait_millis(200);
    sched_step();
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
