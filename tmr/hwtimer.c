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
 * HW timer implementation
 *
 * ***************************************************************************/

#include "tmr/hwtimer_private.h"
#include "util/irq.h"

/*
 * State
 */
SLIST_HEAD(,timer) ht_list; ///< Active timers

/*
 * Interrupt
 */
void
hwtimer_tick ( void )
{
  timer_s *t;
  SLIST_FOREACH(t, &ht_list, t_link) {
    --t->t_tick;
    if (0 == t->t_tick) {
      t->t_cb(t->t_arg);
      t->t_tick = t->t_load;
    }
  }
}

/*
 * Add HW timer callback
 *
 * @param t  The timer to arm
 * @param us The interval (in microseconds) between calls
 */
void
hwtimer_arm
  ( timer_s *t, uint32_t us, bool tick )
{
  ENTER_CRITICAL_REGION();
  t->t_load        = tick ? us : HWTIMER_MICROSEC_TO_TICK(us);
  t->t_tick        = tick ? us : HWTIMER_MICROSEC_TO_TICK(us);
  t->t_flags.f_all = 0;
  SLIST_INSERT_HEAD(&ht_list, t, t_link);
  LEAVE_CRITICAL_REGION();
}

/**
 * Disarm a timer
 *
 * @parma t  The timer to disarm
 */
void
hwtimer_disarm ( timer_s *t )
{
  ENTER_CRITICAL_REGION();
  SLIST_REMOVE(&ht_list, t, timer, t_link);
  LEAVE_CRITICAL_REGION();
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
