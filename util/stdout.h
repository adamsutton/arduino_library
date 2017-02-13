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
 * Standard output handling
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_UTIL_STDOUT_H
#define APS_ARDUINO_UTIL_STDOUT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initialise STDOUT
 */
void stdout_init  ( void );

/*
 * Print to standard out
 */
void stdout_print ( const char *line, ... );

/*
 * Print to stderr
 */
void stderr_print ( const char *line, ... );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_UTIL_STDOUT_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
