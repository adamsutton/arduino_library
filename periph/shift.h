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
 * Provide access to shift register control routines
 *
 * This includes wrapping SPI and/or bit bashing routines and adding extra
 * functionality such as PWM output control.
 *
 * The current implementation only supports upto a maximum of 32-bits
 *
 * LSB is transmitted first (will be furthest register from the source).
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_PERIPH_SHIFT_H
#define APS_ARDUINO_PERIPH_SHIFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/*
 * Initialise shift controller
 *
 * @param hw    Use HW control (in which case clock/data pins are ignored)
 * @param d_pin Data pin
 * @param c_pin Clock pin
 * @param l_pin Latch pin
 * @param bits  The number of bits in the shift register(s)
 */
void     shift_init ( bool hw, uint8_t d_pin, uint8_t c_pin, uint8_t l_pin, 
                      uint8_t bits );

/*
 * Request a pattern is output
 *
 * Duty cycle will be 0 or 100%. The number of bits doesn't need specifying
 * it's provided in init()
 *
 * @param mask The mask to output
 */
void     shift_set_mask ( uint32_t mask );

/*
 * Get the current pattern
 *
 * Note: if PWM control is being used this will return 1 for any bit that's
 *       > 0% duty cycle
 */
uint32_t shift_get_mask ( void );

/*
 * Set the PWM duty cycle of an individual bit
 *
 * @param i   The bit to set (LSB = 0)
 * @param dc  The duty cycle    (0-255)
 */
void     shift_set_pwm  ( uint8_t i, uint8_t dc );

/*
 * Get the PWN duty cycle of an indiviudal bit
 *
 * @param i   The bit to get (LSB = 0)
 */
uint8_t  shift_get_pwm  ( uint8_t i );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_PERIPH_SHIFT_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
