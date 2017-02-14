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

#ifndef APS_ARDUINO_LOG_H
#define APS_ARDUINO_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util/queue.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

/* ***************************************************************************
 * Structure / Enums
 * **************************************************************************/

/*
 * Logging level
 */
typedef enum log_level
{
  LOG_NONE  = 0,
  LOG_ERROR = 1,
  LOG_WARN  = 2,
  LOG_INFO  = 3,
  LOG_DEBUG = 4,
  LOG_TRACE = 5,
} log_level_t;

/*
 * logging handler
 */
typedef struct log_handler
{
  SLIST_ENTRY(log_handler) lh_link; ///< List linkage
  void                   (*lh_log)  ///< Log it 
    ( const log_level_t level, const char *file, const size_t line,
      const char *buf, const size_t len );
} log_handler_t;

#define LOG_HANDLER_INIT(cb) {\
  .lh_link = { NULL },\
  .lh_log  = cb,\
}

/* ***************************************************************************
 * Functions
 * **************************************************************************/

/*
 * Set the logging level
 */
void log_set_level ( log_level_t level );

/*
 * Add logging handler
 */
void log_add_handler ( log_handler_t *lh );

/*
 * Variadic logging function for extensions
 */
void l_logv ( const log_level_t level, const char *file, const size_t line,
              const char *fmt, va_list args );

/*
 * Standard logging function
 */
void l_log  ( const log_level_t level, const char *file, const size_t line,
              const char *fmt, ... )
  __attribute__((format(printf,4,5)));

/* ***************************************************************************
 * Macro wrappers
 *
 * Allow build-time levels
 * **************************************************************************/

#if LOG_LEVEL >= LOG_ERROR
#define l_error(...) l_log(LOG_ERROR, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define l_error(...) ((void)0)
#endif

#if LOG_LEVEL >= LOG_WARN
#define l_warn(...)  l_log(LOG_WARN,  __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define l_warn(...)  ((void)0)
#endif

#if LOG_LEVEL >= LOG_INFO
#define l_info(...)  l_log(LOG_INFO,  __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define l_info(...)  ((void)0)
#endif

#if LOG_LEVEL >= LOG_DEBUG
#define l_debug(...) l_log(LOG_DEBUG, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define l_debug(...) ((void)0)
#endif

#if LOG_LEVEL >= LOG_TRACE
#define l_trace(...) l_log(LOG_TRACE, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define l_trace(...) ((void)0)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_LOG_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
