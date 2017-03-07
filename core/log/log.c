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
 * Simple debug / logger
 *
 * ***************************************************************************/

#include "core/log.h"

#include <string.h>
#include <stdio.h>

static SLIST_HEAD(,log_handler) l_handlers;

/*
 * Add logging handler
 */
void
log_add_handler ( log_handler_t *lh )
{
  SLIST_INSERT_HEAD(&l_handlers, lh, lh_link);
}

/*
 * Variadic logging function for extensions
 */
void
l_logv ( const log_level_t level, const char *file, const size_t line,
         const char *fmt, va_list args )
{
  char           buf[128];
  log_handler_t *lh;
  size_t         n;

  n = vsnprintf(buf, sizeof(buf)-1, fmt, args);
  if (0 < n) {
    buf[n] = '\0';

    /* Output */
    SLIST_FOREACH(lh, &l_handlers, lh_link) {
      lh->lh_log(level, file, line, buf, n);
    }
  }
}

/*
 * Standard logging function
 */
void
l_log  ( const log_level_t level, const char *file, const size_t line,
         const char *fmt, ... )
{
  va_list args;
  va_start(args, fmt);
  l_logv(level, file, line, fmt, args);
  va_end(args);
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
