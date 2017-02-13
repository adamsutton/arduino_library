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
 * Generic timer routines
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_TMR_H
#define APS_ARDUINO_TMR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "util/queue.h"

/**
 * Timer object
 *
 * Note: none of the values in this structure should be set directly, they
 *       are to be setup via the arm / disarm calls etc...
 */
typedef struct timer {
  SLIST_ENTRY(timer) t_link;        ///< List linkage
  void              (*t_cb)(void*); ///< Timer callback
  void               *t_arg;        ///< Argument to pass to callback
  uint32_t            t_load;       ///< The load value for the counter
  int32_t             t_tick;       ///< Current tick counter (can be negative to handle "missed" events)
  union {
    uint32_t          f_all;        ///< All flags, quick clear
    struct {
      bool            rearm : 1;    ///< Auto re-arm
    }                 f;
  }                   t_flags;      ///< Control flags
} timer_s;

/*
 * Initialise timer
 */
#define TIMER_INIT(cb, arg) {\
  .t_link        = { NULL },\
  .t_cb          = cb,\
  .t_arg         = arg,\
  .t_load        = 0,\
  .t_tick        = 0,\
  .t_flags.f_all = 0,\
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_TMR_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
