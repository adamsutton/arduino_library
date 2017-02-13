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
 * Base64 encoder/decoder
 *
 * ***************************************************************************/

#ifndef APS_ARDUINO_B64_H
#define APS_ARDUINO_B64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
 * Encode binary blob
 *
 * This routine will encode the final NUL byte and therefore enough space
 * must be provided (in dstlen).
 *
 * @param src    Binary data to encode
 * @param srclen Length (bytes) of the binary data
 * @param dst    The destination string to write to
 * @param dstlen The maximum length of the string
 *
 * @return -1 if the data cannot be fully encoded, else number of chars written
 *            (excluding the NUL byte)
 */
ssize_t b64_encode
  ( const void *src, const size_t srclen,
    char *dst, const size_t dstlen );

/**
 * Decode base64 data
 *
 * This will NOT handle strings that cannot be properly decoded, so the srclen
 * must be a multiple of 4 bytes with necessary padding. No indication of the
 * exact length of the src data will be given, as the padding will be present.
 *
 * @param src    String to decode
 * @param srclen Length (bytes) of the binary data, must be multiple of 4
 * @param dst    The destination buffer to write to
 * @param dstlen The maximum length of the output buffer
 *
 * @return -1 if the data cannot be properly decoded,
 *            else number of bytes (including padding) decoded
 */
ssize_t b64_decode
  ( const char *src, const size_t srclen,
    void *dst, const size_t dstlen );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APS_ARDUINO_B64_H */

/* ****************************************************************************
 * Editor Configuration
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
