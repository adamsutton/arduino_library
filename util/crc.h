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

#ifndef APS_ARDUINO_CRC_H
#define APS_ARDUINO_CRC_H

#include "types.h"

/**
 * Generic (upto) 32-bit CRC generator
 *
 * Note: this doesn't always produce "standard" compliant results as some
 * CRC's require inverting on input/output, some don't, some require additional
 * steps pre/post, others don't. But the results should be good enough for
 * most practical purposes.
 *
 * @param buf  The data buffer to calculate over
 * @param len  The length of the data buffer
 * @param seed The initialisation value
 * @param poly The CRC polynomial
 * @param mask Mask representing the size of the CRC
 * 
 * @return The calculated CRC (can be fed back in as seed for next
 */
uint32_t crcgen
  ( const void *buf, const size_t len, const uint32_t seed,
    const uint32_t poly, const uint32_t mask );

/* ****************************************************************************
 * Standard polynomials
 * ***************************************************************************/

#define CRC_8_POLY        (0x000000AB)
#define CRC_8_MASK        (0x000000FF)

#define CRC_16_POLY       (0x00008408)
#define CRC_16_MASK       (0x0000FFFF)

#define CRC_32_POLY       (0xEDB88320)
#define CRC_32_MASK       (0xFFFFFFFF)

/* ****************************************************************************
 * Wrappers for standard functions
 * ***************************************************************************/

/*
 * Re-entrant 8-bit
 */
#define crc8_r(b, l, s) crcgen((b), (l), (s), CRC_8_POLY, CRC_8_MASK)

/*
 * Standard 8-bit
 */
#define crc8(b, l)      crc8_r((b), (l), 0)

/*
 * Re-entrant 16-bit
 */
#define crc16_r(b, l, s) crcgen((b), (l), (s), CRC_16_POLY, CRC_16_MASK)

/*
 * Standard 16-bit
 */
#define crc16(b, l)      crc16_r((b), (l), 0)

/*
 * Re-entrant 32-bit
 */
#define crc32_r(b, l, s) crcgen((b), (l), (s), CRC_32_POLY, CRC_32_MASK)

/*
 * Standard 32-bit
 */
#define crc32(b, l)      crc32_r((b), (l), 0)

#endif /* APS_ARDUINO_CRC_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
