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
 * IRQ helper routines
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_HAL_IRQ_H
#define APS_ARDUINO_HAL_IRQ_H

/*
 * Linux
 */
#ifdef TARGET_linux

// TODO: could add some sort of global lock

#define ENTER_CRITICAL_REGION() ((void)0)
#define LEAVE_CRITICAL_REGION() ((void)0)

/*
 * Arduino
 */
#else

#define ENTER_CRITICAL_REGION() do { noInterrupts()
#define LEAVE_CRITICAL_REGION() interrupts(); } while (0)

#endif



#endif /* APS_ARDUINO_CRC_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/