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
 * Simple multi-processor round-robin scheduler
 *
 * No pre-emption or anything fancy. All tasks run in the state thread.
 *
 * ***************************************************************************/

#include "sched/sched.h"
#include "util/irq.h"

/*
 * Queue of tasks for priority
 */
typedef struct sched_queue {
  task_queue_t               sq_tasks;
  task_t                    *sq_head;
} sched_queue_t;

/*
 * State
 */
static sched_queue_t s_queues[SCHED_MAX_PRIO];
static uint8_t       s_prio;
static task_t       *s_current;

/*
 * Single step
 */
void
sched_step ( void )
{
  /* Get current queue / task */
  sched_queue_t *sq = s_queues     + s_prio;
  task_queue_t  *tq = &sq->sq_tasks;

  ENTER_CRITICAL_REGION();

  s_current         = STAILQ_FIRST(tq);
  
  /* Lower prio */
  if ((NULL        == s_current) ||
      (sq->sq_head == s_current)) {
    s_prio = (s_prio + (SCHED_MAX_PRIO - 1)) % SCHED_MAX_PRIO;
    sq->sq_head = NULL;
    s_current   = NULL;

  } else {

    /* Init "end" marker */
    if (NULL == sq->sq_head)
      sq->sq_head = s_current;

    /* Remove */
    STAILQ_REMOVE(tq, s_current, task, t_link);
    s_current->t_state = T_EXEC;
  }

  LEAVE_CRITICAL_REGION();

  if (NULL == s_current) return;

  /* Execute */
  s_current->t_func();

  ENTER_CRITICAL_REGION();

  /* State unchanged */
  if (T_EXEC == s_current->t_state) {

    /* Auto re-schedule */
    if (s_current->t_flags.f_auto)
      sched_add(s_current, s_prio, true);

    /* IDLE */
    else
      s_current->t_state = T_IDLE;
  }

  LEAVE_CRITICAL_REGION();

  /* Done */
  s_current = NULL;

  /* Higher prio */
  s_prio = SCHED_MAX_PRIO - 1;
}

/*
 * Run
 */
void
sched_run ( void )
{
  while (1) sched_step();
}

/*
 * Remove task
 */
void
sched_del ( task_t *t )
{
  ENTER_CRITICAL_REGION();

  if (T_PEND == t->t_prio) {
    sched_queue_t *sq = s_queues + t->t_prio;
    task_queue_t  *tq = &sq->sq_tasks;
    STAILQ_REMOVE(tq, t, task, t_link);
    t->t_state = T_IDLE;
  }

  LEAVE_CRITICAL_REGION();
}

/*
 * Add task
 */
void
sched_add ( task_t *t, uint8_t prio, bool resched )
{
  uint8_t i = 0;

  ENTER_CRITICAL_REGION();

  t->t_flags.f_auto = resched;

  /* Already scheduled */
  if (T_PEND == t->t_state) {

    /* Correct prio, leave as is */
    if (prio == t->t_prio) return;

    /* Remove */
    sched_del(t);
  }

  /* Add */
  sched_queue_t *sq = s_queues + prio;
  task_queue_t  *tq = &sq->sq_tasks;
  STAILQ_INSERT_TAIL(tq, t, t_link);

  LEAVE_CRITICAL_REGION();
}

/*
 * Initialise
 */
void
sched_init ( void )
{
  uint8_t i;
  for (i = 0; i < SCHED_MAX_PRIO; i++) {
    STAILQ_INIT(&s_queues[i].sq_tasks);
    s_queues->sq_head = NULL;
  }
  s_prio = SCHED_MAX_PRIO - 1;
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
