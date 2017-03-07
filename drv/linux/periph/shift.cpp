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
 * Shift register control
 *
 * ***************************************************************************/

#include "periph/shift.h"
#include "core/hwtimer.h"
#include "core/log.h"

/*
 * Request a pattern is output
 */
void
shift_set_mask ( uint32_t mask )
{
}

/*
 * Get the current pattern
 */
uint32_t
shift_get_mask ( void )
{
}

/*
 * Set the PWM duty cycle of an individual bit
 */
void
shift_set_pwm  ( uint8_t i, uint8_t dc )
{
}

/*
 * Initialise
 */
void
shift_init
  ( bool hw, uint8_t d_pin, uint8_t c_pin, uint8_t l_pin, uint8_t bits )
{
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
