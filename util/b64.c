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

#include "util/b64.h"

#include <string.h>

/*
 * Alphabet
 */
static const char *b64_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "0123456789+/=";

/*
 * Encode 3 byte block to 4
 */
static ssize_t
b64_enc_block ( const uint8_t *src, const size_t srclen,
                char          *dst, const size_t dstlen )
{
  uint8_t i, out[] = { 64, 64, 64, 64 };
  
  /* No space */
  if (dstlen < 4) return -1;

  /* Build output in 6-bit chunks */
  out[0] = (src[0] >> 2) & 0x3F;
  out[1] = (src[0] & 0x03) << 4;
  if (srclen > 1) {
    out[1] |= ((src[1] >> 4) & 0x0F);
    out[2]  = ((src[1] << 2) & 0x3C);
  }
  if (srclen > 2) {
    out[2] |= ((src[2] >> 6) & 0x03);
    out[3]  = (src[2] & 0x3F);
  }

  /* Fill in output (add padding as required) */
  for (i = 0; i < 4; i++) {
    dst[i] = b64_alphabet[out[i]];
  }

  return 4;
}

/*
 * Decode 4 char block to 3
 */
static ssize_t
b64_dec_block ( const char *src, const size_t srclen,
                uint8_t    *dst, const size_t dstlen )
{
  uint8_t i, in[] = { 0, 0, 0, 0 };

  /* Validate */
  if (0 != (srclen % 4)) return -1;

  /* Convert alpha chars to 6-bit numbers */
  for (i = 0; i < 4; i++) {
    switch (src[i]) {
      case '=':
        break;
      case '/':
        in[i] = 63;
        break;
      case '+':
        in[i] = 62;
        break;
      case '0'...'9':
        in[i] = (src[i] - '0') + 52;
        break;
      case 'a'...'z':
        in[i] = (src[i] - 'a') + 26;
        break;
      default:
        in[i] = (src[i] - 'A');
        break;
    }
  }

  /* Decode 6-bit values */
  dst[0] = (in[0] << 2)          | ((in[1] >> 4) & 0x03);
  dst[1] = ((in[1] & 0x0F) << 4) | ((in[2] >> 2) & 0x0F);
  dst[2] = (in[2] << 6)          | in[3];

  return 3;
}

/*
 * Encode binary blob
 */
ssize_t
b64_encode
  ( const void *src, const size_t srclen, char *dst, const size_t dstlen )
{
  uint8_t i;
  ssize_t c, len = 0;

  /* Encode 3-byte blocks */
  for (i = 0; i < srclen; i += 3) {
    c = b64_enc_block(src + i, srclen - i, dst + len, dstlen - len);
    if (0 > c) return -1;
    len += c;
  }

  /* NUL terminate */
  if (len >= dstlen) return -1;
  dst[len] = '\0';
  
  return len;
}

/*
 * Decode base64 data
 */
ssize_t
b64_decode
  ( const char *src, const size_t srclen, void *dst, const size_t dstlen )
{
  uint8_t i;
  ssize_t c, len = 0;

  /* Decode 4-byte blocks */
  for (i = 0; i < srclen; i += 4) {
    c = b64_dec_block(src + i, srclen - i, dst + len, dstlen - len);
    if (0 > c) return -1;
    len += c;
  }

  return len;
}

/* ****************************************************************************
 * Editor Configuration#ifndef __ssize_t_defined
 *
 * vim:sts=2:ts=2:sw=2:et
 * ***************************************************************************/
