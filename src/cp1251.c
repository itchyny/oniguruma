/**********************************************************************
  cp1251.c -  Oniguruma (regular expression library)
**********************************************************************/
/*-
 * Copyright (c) 2006-2025  Byte      <byte AT mail DOT kna DOT ru>
 *                          K.Kosako
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "regenc.h"

#define ENC_CP1251_TO_LOWER_CASE(c) EncCP1251_ToLowerCaseTable[c]
#define ENC_IS_CP1251_CTYPE(code,ctype) \
  ((EncCP1251_CtypeTable[code] & CTYPE_TO_BIT(ctype)) != 0)

static const UChar EncCP1251_ToLowerCaseTable[256] = {
  '\000', '\001', '\002', '\003', '\004', '\005', '\006', '\007',
  '\010', '\011', '\012', '\013', '\014', '\015', '\016', '\017',
  '\020', '\021', '\022', '\023', '\024', '\025', '\026', '\027',
  '\030', '\031', '\032', '\033', '\034', '\035', '\036', '\037',
  '\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047',
  '\050', '\051', '\052', '\053', '\054', '\055', '\056', '\057',
  '\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067',
  '\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',
  '\100', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
  '\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
  '\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
  '\170', '\171', '\172', '\133', '\134', '\135', '\136', '\137',
  '\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
  '\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
  '\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
  '\170', '\171', '\172', '\173', '\174', '\175', '\176', '\177',
  '\220', '\203', '\202', '\203', '\204', '\205', '\206', '\207',
  '\210', '\211', '\232', '\213', '\234', '\235', '\236', '\237',
  '\220', '\221', '\222', '\223', '\224', '\225', '\226', '\227',
  '\230', '\231', '\232', '\233', '\234', '\235', '\236', '\237',
  '\240', '\242', '\242', '\274', '\244', '\264', '\246', '\247',
  '\270', '\251', '\272', '\253', '\254', '\255', '\256', '\277',
  '\260', '\261', '\263', '\263', '\264', '\265', '\266', '\267',
  '\270', '\271', '\272', '\273', '\274', '\276', '\276', '\277',
  '\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
  '\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
  '\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
  '\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377',
  '\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
  '\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
  '\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
  '\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377'
};

static const unsigned short EncCP1251_CtypeTable[256] = {
  0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008,
  0x4008, 0x428c, 0x4209, 0x4208, 0x4208, 0x4208, 0x4008, 0x4008,
  0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008,
  0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008,
  0x4284, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0,
  0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0,
  0x78b0, 0x78b0, 0x78b0, 0x78b0, 0x78b0, 0x78b0, 0x78b0, 0x78b0,
  0x78b0, 0x78b0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x41a0,
  0x41a0, 0x7ca2, 0x7ca2, 0x7ca2, 0x7ca2, 0x7ca2, 0x7ca2, 0x74a2,
  0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2,
  0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2, 0x74a2,
  0x74a2, 0x74a2, 0x74a2, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x51a0,
  0x41a0, 0x78e2, 0x78e2, 0x78e2, 0x78e2, 0x78e2, 0x78e2, 0x70e2,
  0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2,
  0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2, 0x70e2,
  0x70e2, 0x70e2, 0x70e2, 0x41a0, 0x41a0, 0x41a0, 0x41a0, 0x4008,
  0x34a2, 0x34a2, 0x01a0, 0x30e2, 0x01a0, 0x01a0, 0x01a0, 0x01a0,
  0x0000, 0x01a0, 0x34a2, 0x01a0, 0x34a2, 0x34a2, 0x34a2, 0x34a2,
  0x30e2, 0x01a0, 0x01a0, 0x01a0, 0x01a0, 0x01a0, 0x01a0, 0x01a0,
  0x0008, 0x0000, 0x30e2, 0x01a0, 0x30e2, 0x30e2, 0x30e2, 0x30e2,
  0x0280, 0x34a2, 0x30e2, 0x34a2, 0x01a0, 0x34a2, 0x01a0, 0x01a0,
  0x34a2, 0x01a0, 0x34a2, 0x01a0, 0x01a0, 0x01a0, 0x01a0, 0x34a2,
  0x01a0, 0x01a0, 0x34a2, 0x30e2, 0x30e2, 0x31e2, 0x01a0, 0x01a0,
  0x30e2, 0x0000, 0x30e2, 0x01a0, 0x30e2, 0x34a2, 0x30e2, 0x30e2,
  0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2,
  0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2,
  0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2,
  0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2, 0x34a2,
  0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2,
  0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2,
  0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2,
  0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2, 0x30e2
};

static int
cp1251_mbc_case_fold(OnigCaseFoldType flag,
             const UChar** pp, const UChar* end ARG_UNUSED, UChar* lower)
{
  const UChar* p = *pp;

  if (CASE_FOLD_IS_NOT_ASCII_ONLY(flag) || ONIGENC_IS_ASCII_CODE(*p))
    *lower = ENC_CP1251_TO_LOWER_CASE(*p);
  else
    *lower = *p;

  (*pp)++;
  return 1;
}

static int
cp1251_is_code_ctype(OnigCodePoint code, unsigned int ctype)
{
  if (code < 256) {
    if (ctype > ONIGENC_MAX_STD_CTYPE)
      return FALSE;
    else
      return ENC_IS_CP1251_CTYPE(code, ctype);
  }
  else
    return FALSE;
}

static const OnigPairCaseFoldCodes CaseFoldMap[] = {
  { 0xb8, 0xa8 },

  { 0xe0, 0xc0 },
  { 0xe1, 0xc1 },
  { 0xe2, 0xc2 },
  { 0xe3, 0xc3 },
  { 0xe4, 0xc4 },
  { 0xe5, 0xc5 },
  { 0xe6, 0xc6 },
  { 0xe7, 0xc7 },
  { 0xe8, 0xc8 },
  { 0xe9, 0xc9 },
  { 0xea, 0xca },
  { 0xeb, 0xcb },
  { 0xec, 0xcc },
  { 0xed, 0xcd },
  { 0xee, 0xce },
  { 0xef, 0xcf },

  { 0xf0, 0xd0 },
  { 0xf1, 0xd1 },
  { 0xf2, 0xd2 },
  { 0xf3, 0xd3 },
  { 0xf4, 0xd4 },
  { 0xf5, 0xd5 },
  { 0xf6, 0xd6 },
  { 0xf7, 0xd7 },
  { 0xf8, 0xd8 },
  { 0xf9, 0xd9 },
  { 0xfa, 0xda },
  { 0xfb, 0xdb },
  { 0xfc, 0xdc },
  { 0xfd, 0xdd },
  { 0xfe, 0xde },
  { 0xff, 0xdf }
};

static int
cp1251_apply_all_case_fold(OnigCaseFoldType flag,
                           OnigApplyAllCaseFoldFunc f, void* arg)
{
  return onigenc_apply_all_case_fold_with_map(
             sizeof(CaseFoldMap)/sizeof(OnigPairCaseFoldCodes), CaseFoldMap, 0,
             flag, f, arg);
}

static int
cp1251_get_case_fold_codes_by_str(OnigCaseFoldType flag,
    const OnigUChar* p, const OnigUChar* end, OnigCaseFoldCodeItem items[])
{
  return onigenc_get_case_fold_codes_by_str_with_map(
                 sizeof(CaseFoldMap)/sizeof(OnigPairCaseFoldCodes), CaseFoldMap, 0,
                 flag, p, end, items);
}

OnigEncodingType OnigEncodingCP1251 = {
  onigenc_single_byte_mbc_enc_len,
  "CP1251",      /* name */
  1,             /* max enc length */
  1,             /* min enc length */
  onigenc_is_mbc_newline_0x0a,
  onigenc_single_byte_mbc_to_code,
  onigenc_single_byte_code_to_mbclen,
  onigenc_single_byte_code_to_mbc,
  cp1251_mbc_case_fold,
  cp1251_apply_all_case_fold,
  cp1251_get_case_fold_codes_by_str,
  onigenc_minimum_property_name_to_ctype,
  cp1251_is_code_ctype,
  onigenc_not_support_get_ctype_code_range,
  onigenc_single_byte_left_adjust_char_head,
  onigenc_always_true_is_allowed_reverse_match,
  NULL, /* init */
  NULL, /* is_initialized */
  onigenc_always_true_is_valid_mbc_string,
  ENC_FLAG_ASCII_COMPATIBLE|ENC_FLAG_SKIP_OFFSET_1,
  0, 0
};
