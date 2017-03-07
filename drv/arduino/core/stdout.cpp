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
 * Standard output handling, sent via UART
 *
 * ***************************************************************************/

#include "core/stdout.h"

#include <stdarg.h>
#include "Arduino.h"
#include "HardwareSerial.h"

static void
_printf ( const char *fmt, va_list args )
{
  char buf[128];
  size_t n;
  n = vsnprintf(buf, sizeof(buf)-1, fmt, args);
  if (0 < n) {
    buf[n] = '\0';
    Serial.write(buf);
  }
}

void
stderr_print ( const char *fmt, ... )
{
  va_list va;
  va_start(va, fmt);
  _printf(fmt, va);
  va_end(va);
}

void
stdout_print ( const char *fmt, ... )
{
  va_list va;
  va_start(va, fmt);
  _printf(fmt, va);
  va_end(va);
}

void
stdout_init ( void )
{
  Serial.begin(9600);
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
