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

#include "SPI.h"

#define CEIL(x, y) (((x) + (y) - 1)/ (y))

static uint8_t  shift_pwm[32];
static uint8_t  shift_bits  = 0;
static uint8_t  shift_data  = 0;
static uint8_t  shift_clock = 0;
static uint8_t  shift_latch = 0;
static uint8_t  shift_count = 0;

/*
 * Request a pattern is output
 */
void
shift_set_mask ( uint32_t mask )
{
  uint8_t i;
  for (i = 0; i < shift_bits; i++) {
    shift_pwm[i] = (mask & 0x1) ? 31 : 0;
    mask >>= 1;
  }
}

/*
 * Get the current pattern
 */
uint32_t
shift_get_mask ( void )
{
  uint8_t  i;
  uint32_t mask = 0;
  for (i = 0; i < shift_bits; i++) {
    mask <<= 1;
    shift_pwm[i] |= 0x1;
  }
  return mask;
}

/*
 * Set the PWM duty cycle of an individual bit
 */
void
shift_set_pwm  ( uint8_t i, uint8_t dc )
{
  shift_pwm[i] = (dc < 32) ? dc : 31;
}

/*
 * Get the PWN duty cycle of an indiviudal bit
 *
 * @param i   The bit to get (LSB = 0)
 */
uint8_t
shift_get_pwm  ( uint8_t i )
{
  return shift_pwm[i];
}

/*
 * HW timer callback
 */
static void
shift_hwt_cb ( void *p )
{
  uint8_t  i;
  uint32_t mask = 0;

  /* Latch OFF */
  digitalWrite(shift_latch, 0);

  /* Update */
  shift_count = (shift_count + 1) & 0x1F;
  
  /* Build the mask */
  for (i = 0; i < shift_bits; i++) {
    mask <<= 1;
    if (shift_count < shift_pwm[i]) mask |= 0x1;
  }

  /* HW */
  if (0 == shift_clock) {
    SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));
    SPI.transfer(&mask, CEIL(shift_bits, 8));
    SPI.endTransaction();
  
  /* SW */
  } else {
    for (i = 0; i < CEIL(shift_bits, 8); i++) {
      shiftOut(shift_data, shift_clock, LSBFIRST, mask & 0xFF);
      mask >>= 8;
    }
  }

  /* Latch it */
  digitalWrite(shift_latch, 1);
  digitalWrite(shift_latch, 0);
}

/*
 * Initialise
 */
void
shift_init
  ( bool hw, uint8_t d_pin, uint8_t c_pin, uint8_t l_pin, uint8_t bits )
{
  static timer_s hwt = TIMER_INIT(shift_hwt_cb, NULL);

  /* Allocate data */
  memset(shift_pwm, 0, sizeof(shift_pwm));
  shift_bits = bits;

  /* SPI */
  if (hw) {
    SPI.begin();

  /* Bit-bash */
  } else {
    shift_data  = d_pin;
    shift_clock = c_pin;

    pinMode(d_pin, OUTPUT);
    pinMode(c_pin, OUTPUT);

    digitalWrite(d_pin, 0);
    digitalWrite(c_pin, 0);
  }

  /* Latch */
  shift_latch = l_pin;
  pinMode(l_pin, OUTPUT);
  digitalWrite(l_pin, 0);

  /* Enable the HW timer */
  hwtimer_arm(&hwt, 1, true);
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
