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
 * Scheduler definitions
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_SCHED_H
#define APS_ARDUINO_SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "util/queue.h"

/*
 * Configuration
 */
#ifndef SCHED_MAX_PRIO
#define SCHED_MAX_PRIO (3) ///< Max priority levels
#endif

/*
 * Useful markers for HIGH / MEDIUM / LOW
 */
#define SCHED_PRIO_LOW  (0)
#define SCHED_PRIO_NORM (SCHED_MAX_PRIO/2)
#define SCHED_PRIO_HIGH (SCHED_MAX_PRIO-1)

/**
 * Task states
 */
typedef enum task_state
{
  T_IDLE = 0, ///< Not in use
  T_PEND = 1, ///< Pending execution (scheduled)
  T_EXEC = 2, ///< Executing
} task_state_t;

/**
 * Task definition
 */
typedef struct task
{
  STAILQ_ENTRY(task)    t_link;           ///< List linkage
  task_state_t          t_state;          ///< Task state
  void                (*t_func) ( void ); ///< Task callback
  uint8_t               t_prio;           ///< Task priority
  struct {
    bool f_auto : 1; ///< Auto re-schedule (same prio)
  }                     t_flags;
} task_t;

/*
 * Initialise
 */
#define TASK_INIT(cb) {\
  .t_link  = { NULL },\
  .t_state = T_IDLE,\
  .t_func  = cb,\
  .t_prio  = 0,\
  .t_flags = {\
    .f_auto = false,\
  },\
}

/**
 * Task Q
 */
typedef STAILQ_HEAD(,task)   task_queue_t;

/**
 * Schedule task
 *
 * @param t       The task to schedule
 * @param prio    The priority to schedule at
 * @param resched Auto re-sched after each execution
 */
void          sched_add    ( task_t *t, uint8_t prio, bool resched );

/**
 * De-scheule task completely
 */
void          sched_del    ( task_t *t );

/**
 * Pause a task
 */
void          sched_pause  ( task_t *t );

/**
 * Resume task
 */
void          sched_resume ( task_t *t );

/**
 * Get the currently executing task
 */
const task_t *sched_self ( void );

/**
 * Initialise the scheduler
 */
void          sched_init ( void );

/**
 * Run the scheduler (in a loop)
 */
void          sched_run ( void );

/**
 * Single step the scheduler
 */
void          sched_step ( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_SCHED_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
