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
#include "core/irq.h"

#include "Arduino.h"

/*
 * Interrupt
 */
ISR(TIMER1_COMPA_vect)
{
  hwtimer_tick();
}

/*
 * Initiliase the HW timer API
 */
void
hwtimer_init ( void )
{
  /* Setup the timer */
  ENTER_CRITICAL_REGION();
  TCNT1  = 0;
  TCCR1A = 0;
  TCCR1B = _BV(WGM12) | _BV(CS10); // CTC mode, no pre-scaler
  TIMSK1 = _BV(OCIE1A);            // output compare
  OCR1A  = (F_CPU / (uint32_t)HWTIMER_HZ);
  LEAVE_CRITICAL_REGION();
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
