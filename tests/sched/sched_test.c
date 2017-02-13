#include "sched/sched.h"

#include <stdio.h>
#include <unistd.h>

void a_cb ( void ) { printf("%s 0\n", __func__); };
void b_cb ( void ) { printf("%s 0\n", __func__); };
void c_cb ( void ) { printf("%s 1\n", __func__); };
void d_cb ( void ) { printf("%s 1\n", __func__); };
void e_cb ( void ) { printf("%s 2\n", __func__); };
void f_cb ( void ) { printf("%s 2\n", __func__); };

int main ( int argc, char **argv )
{
  task_t a = TASK_INIT(a_cb),
         b = TASK_INIT(b_cb),
         c = TASK_INIT(c_cb),
         d = TASK_INIT(d_cb),
         e = TASK_INIT(e_cb),
         f = TASK_INIT(f_cb);
  printf("add\n");

  sched_init();

  sched_add(&a, 0, true);
  sched_add(&b, 0, true);
  sched_add(&c, 1, true);
  sched_add(&d, 1, true);
  sched_add(&e, 2, true);
  sched_add(&f, 2, true);

  while (1) {
    usleep(100000);
    sched_step();
  }
}
