/* ----------------------------------------------------------------- */
/*           The Japanese TTS System "Open JTalk"                    */
/*           developed by HTS Working Group                          */
/*           http://open-jtalk.sourceforge.net/                      */
/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2008-2016  Nagoya Institute of Technology          */
/*                           Department of Computer Science          */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the HTS working group nor the names of its  */
/*   contributors may be used to endorse or promote products derived */
/*   from this software without specific prior written permission.   */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef NJD2JPCOMMON_C
#define NJD2JPCOMMON_C

#ifdef __cplusplus
#define NJD2JPCOMMON_C_START extern "C" {
#define NJD2JPCOMMON_C_END   }
#else
#define NJD2JPCOMMON_C_START
#define NJD2JPCOMMON_C_END
#endif                          /* __CPLUSPLUS */

NJD2JPCOMMON_C_START;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "njd.h"
#include "jpcommon.h"

#ifdef ASCII_HEADER
#if defined(CHARSET_EUC_JP)
#include "njd2jpcommon_rule_ascii_for_euc_jp.h"
#elif defined(CHARSET_SHIFT_JIS)
#include "njd2jpcommon_rule_ascii_for_shift_jis.h"
#elif defined(CHARSET_UTF_8)
#include "njd2jpcommon_rule_ascii_for_utf_8.h"
#else
#error CHARSET is not specified
#endif
#else
#if defined(CHARSET_EUC_JP)
#include "njd2jpcommon_rule_euc_jp.h"
#elif defined(CHARSET_SHIFT_JIS)
#include "njd2jpcommon_rule_shift_jis.h"
#elif defined(CHARSET_UTF_8)
#include "njd2jpcommon_rule_utf_8.h"
#else
#error CHARSET is not specified
#endif
#endif

#define MAXBUFLEN 1024

/* 漢字数字を整数に変換する関数 (1-40対応) */
static int kanji_to_int(const char *str)
{
   if (!str) return 0;
   
   /* 1-9 */
   if (strcmp(str, "一") == 0 || strcmp(str, "1") == 0) return 1;
   if (strcmp(str, "二") == 0 || strcmp(str, "2") == 0) return 2;
   if (strcmp(str, "三") == 0 || strcmp(str, "3") == 0) return 3;
   if (strcmp(str, "四") == 0 || strcmp(str, "4") == 0) return 4;
   if (strcmp(str, "五") == 0 || strcmp(str, "5") == 0) return 5;
   if (strcmp(str, "六") == 0 || strcmp(str, "6") == 0) return 6;
   if (strcmp(str, "七") == 0 || strcmp(str, "7") == 0) return 7;
   if (strcmp(str, "八") == 0 || strcmp(str, "8") == 0) return 8;
   if (strcmp(str, "九") == 0 || strcmp(str, "9") == 0) return 9;
   
   /* 10-19 */
   if (strcmp(str, "十") == 0 || strcmp(str, "10") == 0) return 10;
   if (strcmp(str, "十一") == 0 || strcmp(str, "11") == 0) return 11;
   if (strcmp(str, "十二") == 0 || strcmp(str, "12") == 0) return 12;
   if (strcmp(str, "十三") == 0 || strcmp(str, "13") == 0) return 13;
   if (strcmp(str, "十四") == 0 || strcmp(str, "14") == 0) return 14;
   if (strcmp(str, "十五") == 0 || strcmp(str, "15") == 0) return 15;
   if (strcmp(str, "十六") == 0 || strcmp(str, "16") == 0) return 16;
   if (strcmp(str, "十七") == 0 || strcmp(str, "17") == 0) return 17;
   if (strcmp(str, "十八") == 0 || strcmp(str, "18") == 0) return 18;
   if (strcmp(str, "十九") == 0 || strcmp(str, "19") == 0) return 19;
   
   /* 20-29 */
   if (strcmp(str, "二十") == 0 || strcmp(str, "20") == 0) return 20;
   if (strcmp(str, "二十一") == 0 || strcmp(str, "21") == 0) return 21;
   if (strcmp(str, "二十二") == 0 || strcmp(str, "22") == 0) return 22;
   if (strcmp(str, "二十三") == 0 || strcmp(str, "23") == 0) return 23;
   if (strcmp(str, "二十四") == 0 || strcmp(str, "24") == 0) return 24;
   if (strcmp(str, "二十五") == 0 || strcmp(str, "25") == 0) return 25;
   if (strcmp(str, "二十六") == 0 || strcmp(str, "26") == 0) return 26;
   if (strcmp(str, "二十七") == 0 || strcmp(str, "27") == 0) return 27;
   if (strcmp(str, "二十八") == 0 || strcmp(str, "28") == 0) return 28;
   if (strcmp(str, "二十九") == 0 || strcmp(str, "29") == 0) return 29;
   
   /* 30-39 */
   if (strcmp(str, "三十") == 0 || strcmp(str, "30") == 0) return 30;
   if (strcmp(str, "三十一") == 0 || strcmp(str, "31") == 0) return 31;
   if (strcmp(str, "三十二") == 0 || strcmp(str, "32") == 0) return 32;
   if (strcmp(str, "三十三") == 0 || strcmp(str, "33") == 0) return 33;
   if (strcmp(str, "三十四") == 0 || strcmp(str, "34") == 0) return 34;
   if (strcmp(str, "三十五") == 0 || strcmp(str, "35") == 0) return 35;
   if (strcmp(str, "三十六") == 0 || strcmp(str, "36") == 0) return 36;
   if (strcmp(str, "三十七") == 0 || strcmp(str, "37") == 0) return 37;
   if (strcmp(str, "三十八") == 0 || strcmp(str, "38") == 0) return 38;
   if (strcmp(str, "三十九") == 0 || strcmp(str, "39") == 0) return 39;
   
   /* 40 */
   if (strcmp(str, "四十") == 0 || strcmp(str, "40") == 0) return 40;
   
   /* その他の場合 */
   return atoi(str);
}

/* 数字の各桁に3を含むかチェック */
static int contains_digit_3(int val)
{
   while (val > 0) {
      if (val % 10 == 3) return 1;
      val /= 10;
   }
   return 0;
}

static void convert_pos(char *buff, const char *pos, const char *pos_group1, const char *pos_group2,
                        const char *pos_group3)
{
   int i;

   for (i = 0; njd2jpcommon_pos_list[i] != NULL; i += 5) {
      if (strcmp(njd2jpcommon_pos_list[i], pos) == 0 &&
          strcmp(njd2jpcommon_pos_list[i + 1], pos_group1) == 0 &&
          strcmp(njd2jpcommon_pos_list[i + 2], pos_group2) == 0 &&
          strcmp(njd2jpcommon_pos_list[i + 3], pos_group3) == 0) {
         strcpy(buff, njd2jpcommon_pos_list[i + 4]);
         return;
      }
   }
   fprintf(stderr,
           "WARNING: convert_pos() in njd2jpcommon.c: %s %s %s %s are not appropriate POS.\n", pos,
           pos_group1, pos_group2, pos_group3);
   strcpy(buff, njd2jpcommon_pos_list[4]);
}

static void convert_ctype(char *buff, const char *ctype)
{
   int i;

   for (i = 0; njd2jpcommon_ctype_list[i] != NULL; i += 2) {
      if (strcmp(njd2jpcommon_ctype_list[i], ctype) == 0) {
         strcpy(buff, njd2jpcommon_ctype_list[i + 1]);
         return;
      }
   }
   fprintf(stderr,
           "WARNING: convert_ctype() in njd2jpcommon.c: %s is not appropriate conjugation type.\n",
           ctype);
   strcpy(buff, njd2jpcommon_ctype_list[1]);
}

static void convert_cform(char *buff, const char *cform)
{
   int i;

   for (i = 0; njd2jpcommon_cform_list[i] != NULL; i += 2) {
      if (strcmp(njd2jpcommon_cform_list[i], cform) == 0) {
         strcpy(buff, njd2jpcommon_cform_list[i + 1]);
         return;
      }
   }
   fprintf(stderr,
           "WARNING: convert_cform() in njd2jpcommon.c: %s is not appropriate conjugation form.\n",
           cform);
   strcpy(buff, njd2jpcommon_cform_list[1]);
}
/* 数字が連続している場合、そのカタマリ全体の数値を計算する関数 */
static int get_full_number_value(NJDNode *node) {
    NJDNode *start = node;
    // 1. 数字のカタマリの先頭まで戻る
    while (start->prev && ( (NJDNode_get_pos(start->prev) && strcmp(NJDNode_get_pos(start->prev), "数") == 0) || 
                            (NJDNode_get_pos_group1(start->prev) && strcmp(NJDNode_get_pos_group1(start->prev), "数") == 0) )) {
        start = start->prev;
    }

    int total = 0;
    NJDNode *curr = start;
    // 2. 先頭から順に数値を合体させる
    while (curr) {
        const char *p = NJDNode_get_pos(curr);
        const char *p1 = NJDNode_get_pos_group1(curr);
        if (!( (p && strcmp(p, "数") == 0) || (p1 && strcmp(p1, "数") == 0) )) break;

        int v = (NJDNode_get_string(curr) != NULL) ? kanji_to_int(NJDNode_get_string(curr)) : 0;
        if (v == 10 || v == 100 || v == 1000) {
            if (total == 0) total = v;
            else if (total < v) total *= v; // 三 + 十 = 30
            else total += v;                // 十 + 三 = 13
        } else {
            total += v;
        }
        if (!curr->next) break;
        curr = curr->next;
    }
    return total;
}
void njd2jpcommon(JPCommon * jpcommon, NJD * njd)
{
   char buff[MAXBUFLEN];
   NJDNode *inode;
   JPCommonNode *jnode;

   for (inode = njd->head; inode != NULL; inode = inode->next) {
      jnode = (JPCommonNode *) calloc(1, sizeof(JPCommonNode));
      JPCommonNode_initialize(jnode);
      JPCommonNode_set_pron(jnode, NJDNode_get_pron(inode));
      
      /* 基本情報のセット */
      convert_pos(buff, NJDNode_get_pos(inode), NJDNode_get_pos_group1(inode),
                  NJDNode_get_pos_group2(inode), NJDNode_get_pos_group3(inode));
      JPCommonNode_set_pos(jnode, buff);
      convert_ctype(buff, NJDNode_get_ctype(inode));
      JPCommonNode_set_ctype(jnode, buff);
      convert_cform(buff, NJDNode_get_cform(inode));
      JPCommonNode_set_cform(jnode, buff);
      JPCommonNode_set_acc(jnode, NJDNode_get_acc(inode));
      JPCommonNode_set_chain_flag(jnode, NJDNode_get_chain_flag(inode));

/* --- アホ判定ロジック開始 --- */
      int is_aho = 0;
      const char *pos = NJDNode_get_pos(inode);
      const char *pos1 = NJDNode_get_pos_group1(inode);
      const char *pron = NJDNode_get_pron(inode);

      // 1. 読みが「サン」ならアホ
      if (pron != NULL && strcmp(pron, "サン") == 0) {
         is_aho = 1;
      } 
      // 2. 数字の場合
      else if ((pos != NULL && strcmp(pos, "数") == 0) || (pos1 != NULL && strcmp(pos1, "数") == 0)) {
         // さっき作った関数を使って「数全体の合計」を出す
         int full_val = get_full_number_value(inode);
         
         if (full_val > 0 && (full_val % 3 == 0 || contains_digit_3(full_val))) {
            is_aho = 1;
         }
         
         printf("DEBUG: AhoCheck - str:%s, full_val:%d, aho:%d\n", 
                NJDNode_get_string(inode) ? NJDNode_get_string(inode) : "NULL", full_val, is_aho);
      }

      JPCommonNode_set_aho(jnode, is_aho);
      /* --- アホ判定ロジック終了 --- */


      JPCommon_push(jpcommon, jnode);
   }
}

NJD2JPCOMMON_C_END;

#endif                          /* !NJD2JPCOMMON_C */
