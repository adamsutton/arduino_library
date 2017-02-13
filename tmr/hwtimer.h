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
 * Provides access to the HW timers
 *
 * These are intended to be high accuracy events run under interrupt
 * the necessary precautions must be taken when using.
 *
 * For reasons of simplicity and because thus far my requirements have
 * been basic, this only gives very simple access.
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_HWTIMER_H
#define APS_ARDUINO_HWTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tmr/tmr.h"

/**
 * Arm HW timer callback
 *
 * @param t  The timer to arm
 * @param us The interval (in microseconds) between calls
 */
void hwtimer_arm
  ( timer_s *t, uint32_t us );

/**
 * Disarm a timer
 *
 * @parma t  The timer to disarm
 */
void hwtimer_disarm ( timer_s *t );

/**
 * Initialise
 */
void hwtimer_init   ( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_HWTIMER_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
