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

#include "core/tmr/hwtimer_private.h"

#include <time.h>
#include <pthread.h>
#include <errno.h>

/*
 * State
 */
static pthread_t          ht_thread;
static pthread_cond_t     ht_cond;
static pthread_mutex_t    ht_lock   = PTHREAD_MUTEX_INITIALIZER;

/*
 * Update clock
 */
static inline void
hwtimer_inc_clock ( struct timespec *ts )
{ 
  #define NANOSEC (1000000000LL)
  ts->tv_nsec += (NANOSEC / HWTIMER_HZ);
  if (ts->tv_nsec >= NANOSEC ) {
    ++ts->tv_sec;
    ts->tv_nsec -= NANOSEC;
  }
}

/*
 * Thread for "generating" HW timer replacement
 */
static void*
hwtimer_thread_cb ( void *p )
{
  int r;
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  while (1) {
    hwtimer_inc_clock(&ts);
    pthread_mutex_lock(&ht_lock);
    while (ETIMEDOUT != (r = pthread_cond_timedwait(&ht_cond, &ht_lock, &ts)));
    pthread_mutex_unlock(&ht_lock);
    hwtimer_tick();
  }
}

/*
 * Initiliase the HW timer API
 */
void
hwtimer_init ( void )
{
  pthread_condattr_t attr;
  pthread_condattr_init(&attr);
  pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
  pthread_cond_init(&ht_cond, &attr);
  pthread_create(&ht_thread, NULL, hwtimer_thread_cb, NULL);
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
