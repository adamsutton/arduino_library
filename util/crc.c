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
 * CRC generator
 *
 * ***************************************************************************/

#include "crc.h"

/*
 * Arbitrary function (upto 32-bit)
 */
uint32_t
crcgen ( const void *buf, const size_t len, const uint32_t seed,
         const uint32_t poly, const uint32_t mask )
{
  uint32_t crc, i, j;
  const uint8_t *data = buf;

  /* Init (invert) */
  crc = ~seed;

  /* Shift */
  for (i = 0; i < len; i++) {
    crc = (crc ^ data[i]) & mask;
    for (j = 0; j < 8; j++) {
      crc = ((crc >> 1) ^ (poly & -(crc & 0x1))) & mask;
    }
  }

  /* End (invert) */
  return (~crc) & mask;
}

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
