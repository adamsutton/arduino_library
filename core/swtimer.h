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
 * Provides access to SW timers, these are lower performance than the HW
 * timers and the execution is run in the normal background loop rather than
 * under interrupt
 *
 * The timers should be fairly accurate / stable over the long term, but wil
 * likely suffer from jitter
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_SWTIMER_H
#define APS_ARDUINO_SWTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/tmr/tmr.h"

/*
 * Config
 */
#ifndef SWTIMER_DYNAMIC
#define SWTIMER_DYNAMIC (0) ///< Enable dynamic scheduling of tasks / hwt
#endif

/**
 * Arm HW timer callback
 *
 * @param t  The timer to arm
 * @param us The interval (in milliseconds) between calls
 * @param ar Auto reload the timer on expiration
 */
void swtimer_arm
  ( timer_s *t, uint32_t ms, bool ar );

/**
 * Disarm a timer
 *
 * @parma t  The timer to disarm
 */
void swtimer_disarm ( timer_s *t );

/**
 * Initialise
 */
void swtimer_init   ( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_SWTIMER_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
