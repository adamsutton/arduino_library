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
 * HW timer private definitions
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_HWTIMER_PRIVATE_H
#define APS_ARDUINO_HWTIMER_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/hwtimer.h"

/*
 * Define the tick rate
 */
#ifndef HWTIMER_HZ
#define HWTIMER_HZ (8000) // hardware timer rate
#endif

/*
 * Convert microseconds to ticks @ HWTIMER_HZ
 */
#define HWTIMER_MICROSEC_TO_TICK(_x)\
  ((_x * (uint32_t)HWTIMER_HZ) / 1000000LL)

/*
 * Timer list
 */
extern SLIST_HEAD(,timer) hwtimer_list;

/*
 * Tick
 */
void hwtimer_tick ( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_HWTIMER_PRIVATE_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
