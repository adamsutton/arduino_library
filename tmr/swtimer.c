/* ****************************************************************************
 *
 * Copyright (C) 2017- Adam Sutton
 *
 * This file is part of ApsArduinoLib
 *
 * ApsArduinoLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ApsArduinoLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ApsArduinoLib.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For more details, including opportunities for alternative licensing,
 * please read the LICENSE file.
 *
 * ***************************************************************************
 *
 * SW timer implementation
 *
 * ***************************************************************************/

#include "tmr/swtimer.h"
#include "tmr/hwtimer.h"
#include "sched/sched.h"
#include "util/irq.h"

/*
 * Callbacks
 */
static void swtimer_hwt_cb  ( void *p );
static void swtimer_task_cb ( void );

/*
 * State
 */
static SLIST_HEAD(,timer) st_list; ///< Active timers
static volatile uint16_t  st_tick; ///< Ticks since last background loop
static timer_s            st_hwt  = TIMER_INIT(swtimer_hwt_cb, NULL);
static task_t             st_task = TASK_INIT(swtimer_task_cb);

/*
 * HW timer callback
 */
static void
swtimer_hwt_cb ( void *p )
{
  ++st_tick;
#if (1 == SWTIMER_DYNAMIC)
  sched_add(&st_task, SCHED_PRIO_HIGH, false);
#endif
}

/*
 * Add HW timer callback
 */
void swtimer_arm
  ( timer_s *t, uint32_t ms, bool ar )
{
  /* Enable the HW timer */
#if (1 == SWTIMER_DYNAMIC)
  if (NULL == SLIST_FIRST(&st_list))
    hwtimer_arm(&st_hwt, 1000, false);
#endif

  /* Load */
  t->t_load          = ms;
  t->t_tick          = ms;
  t->t_flags.f_all   = 0;
  t->t_flags.f.rearm = ar;
  SLIST_INSERT_HEAD(&st_list, t, t_link);
}

/**
 * Disarm a timer
 *
 * @parma t  The timer to disarm
 */
void
swtimer_disarm ( timer_s *t )
{
  /* Remove */
  SLIST_REMOVE(&st_list, t, timer, t_link);

  /* Disarm the timer */
#if (1 == SWTIMER_DYNAMIC)
  if (NULL == SLIST_FIRST(&st_list))
    hwtimer_disarm(&st_hwt);
#endif
}

/*
 * Background task
 */
static void
swtimer_task_cb ( void )
{
  timer_s *t, *n;
  uint16_t ticks;
  bool more = false;

  /* Copy ticks */
  ENTER_CRITICAL_REGION();
  ticks   = st_tick;
  st_tick = 0;
  LEAVE_CRITICAL_REGION();

  /* Skip */
  if (!ticks) return;

  /* Update all counters */
  SLIST_FOREACH(t, &st_list, t_link) {
    t->t_tick -= ticks;
  }

  /* Callbacks */
  do {
    more = false;
    for (t = SLIST_FIRST(&st_list); t != NULL; t = n) {
      n = SLIST_NEXT(t, t_link);
    
      /* Expired */
      if (0 >= t->t_tick) {

        /* Remove */
        if (!t->t_flags.f.rearm)
          SLIST_REMOVE(&st_list, t, timer, t_link);

        /* Callback */
        t->t_cb(t->t_arg);

        /* Update */
        t->t_tick += t->t_load;
        more = true;
      }
    }
  } while (more);
}

/*
 * Initiliase the HW timer API
 */
void
swtimer_init ( void )
{
#if (0 == SWTIMER_DYNAMIC)
  hwtimer_arm(&st_hwt, 1000, false);
  sched_add(&st_task, SCHED_PRIO_HIGH, true);
#endif
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
