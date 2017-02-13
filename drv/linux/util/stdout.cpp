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
 * Standard output handling, using printf()
 *
 * ***************************************************************************/

#include "util/stdout.h"

#include <stdio.h>
#include <stdarg.h>

void
stderr_print ( const char *fmt, ... )
{
  va_list va;
  va_start(va, fmt);
  vprintf(fmt, va);
  va_end(va);
}

void
stdout_print ( const char *fmt, ... )
{
  va_list va;
  va_start(va, fmt);
  vprintf(fmt, va);
  va_end(va);
}

void
stdout_init ( void )
{
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
