
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
 * Log to stdout
 *
 * ***************************************************************************/

#include "log/log.h"
#include "util/stdout.h"
#include "util/clock.h"

#include <stdio.h>

static void
lso_log
 ( const log_level_t level, const char *file, const size_t line,
   const char *buf, const size_t len )
{
  const char lvlpre[] = " EWIDT";
  unsigned long tm  = mono_millis();
  char tmp[128];
  int n;

  n = snprintf(tmp, sizeof(tmp), "%c %6ld.%03ld - %s\n",
               lvlpre[level], tm / 1000, tm % 1000, buf);
  if (0 <= n) {
    tmp[n] = '\0';
    stdout_print(tmp);
  }
}

void
log_stdout_init ( void )
{
  static log_handler_t h = LOG_HANDLER_INIT(lso_log);
  log_add_handler(&h);
  stdout_init();
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
