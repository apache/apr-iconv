/*-
 * Copyright (c) 2000, Boris Popov.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Boris Popov
 *	and its contributors.
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
 *
 */

#define ICONV_INTERNAL

#include "iconv.h"
#include "apr_file_io.h"
#include "apr_file_info.h"
#include "apr_pools.h"
#include "apr_dso.h"
#include "apr_env.h"
#include "apr_strings.h"
#include "apr_tables.h"
#include "apr_lib.h"
#include "api_version.h"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef API_USE_BUILTIN_ALIASES
#include "charset_alias.h"
#endif

#define APR_ICONV_PATH "APR_ICONV" API_STRINGIFY(API_MAJOR_VERSION) "_PATH"

API_IMPORT_MODULE(_tbl_simple);
API_IMPORT_MODULE(adobe_stdenc);
API_IMPORT_MODULE(adobe_symbol);
API_IMPORT_MODULE(adobe_zdingbats);
API_IMPORT_MODULE(big5);
API_IMPORT_MODULE(cns11643_plane1);
API_IMPORT_MODULE(cns11643_plane14);
API_IMPORT_MODULE(cns11643_plane2);
API_IMPORT_MODULE(cp037);
API_IMPORT_MODULE(cp038);
API_IMPORT_MODULE(cp10000);
API_IMPORT_MODULE(cp10006);
API_IMPORT_MODULE(cp10007);
API_IMPORT_MODULE(cp10029);
API_IMPORT_MODULE(cp1006);
API_IMPORT_MODULE(cp10079);
API_IMPORT_MODULE(cp10081);
API_IMPORT_MODULE(cp1026);
API_IMPORT_MODULE(cp273);
API_IMPORT_MODULE(cp274);
API_IMPORT_MODULE(cp275);
API_IMPORT_MODULE(cp277);
API_IMPORT_MODULE(cp278);
API_IMPORT_MODULE(cp280);
API_IMPORT_MODULE(cp281);
API_IMPORT_MODULE(cp284);
API_IMPORT_MODULE(cp285);
API_IMPORT_MODULE(cp290);
API_IMPORT_MODULE(cp297);
API_IMPORT_MODULE(cp420);
API_IMPORT_MODULE(cp423);
API_IMPORT_MODULE(cp424);
API_IMPORT_MODULE(cp437);
API_IMPORT_MODULE(cp500);
API_IMPORT_MODULE(cp737);
API_IMPORT_MODULE(cp775);
API_IMPORT_MODULE(cp850);
API_IMPORT_MODULE(cp851);
API_IMPORT_MODULE(cp852);
API_IMPORT_MODULE(cp855);
API_IMPORT_MODULE(cp856);
API_IMPORT_MODULE(cp857);
API_IMPORT_MODULE(cp860);
API_IMPORT_MODULE(cp861);
API_IMPORT_MODULE(cp862);
API_IMPORT_MODULE(cp863);
API_IMPORT_MODULE(cp864);
API_IMPORT_MODULE(cp865);
API_IMPORT_MODULE(cp866);
API_IMPORT_MODULE(cp868);
API_IMPORT_MODULE(cp869);
API_IMPORT_MODULE(cp870);
API_IMPORT_MODULE(cp871);
API_IMPORT_MODULE(cp874);
API_IMPORT_MODULE(cp875);
API_IMPORT_MODULE(cp880);
API_IMPORT_MODULE(cp891);
API_IMPORT_MODULE(cp903);
API_IMPORT_MODULE(cp904);
API_IMPORT_MODULE(cp905);
API_IMPORT_MODULE(cp918);
API_IMPORT_MODULE(cp932);
API_IMPORT_MODULE(cp936);
API_IMPORT_MODULE(cp949);
API_IMPORT_MODULE(cp950);
API_IMPORT_MODULE(dec_mcs);
API_IMPORT_MODULE(ebcdic_at_de);
API_IMPORT_MODULE(ebcdic_at_de_a);
API_IMPORT_MODULE(ebcdic_ca_fr);
API_IMPORT_MODULE(ebcdic_dk_no);
API_IMPORT_MODULE(ebcdic_dk_no_a);
API_IMPORT_MODULE(ebcdic_es);
API_IMPORT_MODULE(ebcdic_es_a);
API_IMPORT_MODULE(ebcdic_es_s);
API_IMPORT_MODULE(ebcdic_fi_se);
API_IMPORT_MODULE(ebcdic_fi_se_a);
API_IMPORT_MODULE(ebcdic_fr);
API_IMPORT_MODULE(ebcdic_it);
API_IMPORT_MODULE(ebcdic_pt);
API_IMPORT_MODULE(ebcdic_uk);
API_IMPORT_MODULE(ebcdic_us);
API_IMPORT_MODULE(euc_jp);
API_IMPORT_MODULE(euc_kr);
API_IMPORT_MODULE(euc_tw);
API_IMPORT_MODULE(gb12345);
API_IMPORT_MODULE(gb2312);
API_IMPORT_MODULE(gb_2312_80);
API_IMPORT_MODULE(hp_roman8);
API_IMPORT_MODULE(iso646_dk);
API_IMPORT_MODULE(iso646_kr);
API_IMPORT_MODULE(iso_10646_ucs_2);
API_IMPORT_MODULE(iso_10646_ucs_4);
API_IMPORT_MODULE(iso_2022_cn);
API_IMPORT_MODULE(iso_2022_jp);
API_IMPORT_MODULE(iso_2022_jp_2);
API_IMPORT_MODULE(iso_2022_kr);
API_IMPORT_MODULE(iso_8859_1);
API_IMPORT_MODULE(iso_8859_10);
API_IMPORT_MODULE(iso_8859_13);
API_IMPORT_MODULE(iso_8859_14);
API_IMPORT_MODULE(iso_8859_15);
API_IMPORT_MODULE(iso_8859_2);
API_IMPORT_MODULE(iso_8859_3);
API_IMPORT_MODULE(iso_8859_4);
API_IMPORT_MODULE(iso_8859_5);
API_IMPORT_MODULE(iso_8859_6);
API_IMPORT_MODULE(iso_8859_7);
API_IMPORT_MODULE(iso_8859_8);
API_IMPORT_MODULE(iso_8859_9);
API_IMPORT_MODULE(iso_ir_10);
API_IMPORT_MODULE(iso_ir_102);
API_IMPORT_MODULE(iso_ir_103);
API_IMPORT_MODULE(iso_ir_11);
API_IMPORT_MODULE(iso_ir_111);
API_IMPORT_MODULE(iso_ir_121);
API_IMPORT_MODULE(iso_ir_122);
API_IMPORT_MODULE(iso_ir_123);
API_IMPORT_MODULE(iso_ir_128);
API_IMPORT_MODULE(iso_ir_13);
API_IMPORT_MODULE(iso_ir_139);
API_IMPORT_MODULE(iso_ir_14);
API_IMPORT_MODULE(iso_ir_141);
API_IMPORT_MODULE(iso_ir_142);
API_IMPORT_MODULE(iso_ir_143);
API_IMPORT_MODULE(iso_ir_146);
API_IMPORT_MODULE(iso_ir_147);
API_IMPORT_MODULE(iso_ir_15);
API_IMPORT_MODULE(iso_ir_150);
API_IMPORT_MODULE(iso_ir_151);
API_IMPORT_MODULE(iso_ir_152);
API_IMPORT_MODULE(iso_ir_153);
API_IMPORT_MODULE(iso_ir_154);
API_IMPORT_MODULE(iso_ir_155);
API_IMPORT_MODULE(iso_ir_158);
API_IMPORT_MODULE(iso_ir_16);
API_IMPORT_MODULE(iso_ir_17);
API_IMPORT_MODULE(iso_ir_18);
API_IMPORT_MODULE(iso_ir_19);
API_IMPORT_MODULE(iso_ir_2);
API_IMPORT_MODULE(iso_ir_21);
API_IMPORT_MODULE(iso_ir_25);
API_IMPORT_MODULE(iso_ir_27);
API_IMPORT_MODULE(iso_ir_37);
API_IMPORT_MODULE(iso_ir_4);
API_IMPORT_MODULE(iso_ir_47);
API_IMPORT_MODULE(iso_ir_49);
API_IMPORT_MODULE(iso_ir_50);
API_IMPORT_MODULE(iso_ir_51);
API_IMPORT_MODULE(iso_ir_54);
API_IMPORT_MODULE(iso_ir_55);
API_IMPORT_MODULE(iso_ir_57);
API_IMPORT_MODULE(iso_ir_60);
API_IMPORT_MODULE(iso_ir_61);
API_IMPORT_MODULE(iso_ir_69);
API_IMPORT_MODULE(iso_ir_70);
API_IMPORT_MODULE(iso_ir_84);
API_IMPORT_MODULE(iso_ir_85);
API_IMPORT_MODULE(iso_ir_86);
API_IMPORT_MODULE(iso_ir_88);
API_IMPORT_MODULE(iso_ir_89);
API_IMPORT_MODULE(iso_ir_8_1);
API_IMPORT_MODULE(iso_ir_8_2);
API_IMPORT_MODULE(iso_ir_90);
API_IMPORT_MODULE(iso_ir_91);
API_IMPORT_MODULE(iso_ir_92);
API_IMPORT_MODULE(iso_ir_93);
API_IMPORT_MODULE(iso_ir_94);
API_IMPORT_MODULE(iso_ir_95);
API_IMPORT_MODULE(iso_ir_96);
API_IMPORT_MODULE(iso_ir_98);
API_IMPORT_MODULE(iso_ir_99);
API_IMPORT_MODULE(iso_ir_9_1);
API_IMPORT_MODULE(iso_ir_9_2);
API_IMPORT_MODULE(jis_x0201);
API_IMPORT_MODULE(jis_x0208_1983);
API_IMPORT_MODULE(jis_x0212_1990);
API_IMPORT_MODULE(johab);
API_IMPORT_MODULE(koi8_r);
API_IMPORT_MODULE(koi8_ru);
API_IMPORT_MODULE(koi8_u);
API_IMPORT_MODULE(ksx1001);
API_IMPORT_MODULE(mac_ce);
API_IMPORT_MODULE(mac_croatian);
API_IMPORT_MODULE(mac_cyrillic);
API_IMPORT_MODULE(mac_dingbats);
API_IMPORT_MODULE(mac_greek);
API_IMPORT_MODULE(mac_iceland);
API_IMPORT_MODULE(mac_japan);
API_IMPORT_MODULE(mac_roman);
API_IMPORT_MODULE(mac_romania);
API_IMPORT_MODULE(mac_thai);
API_IMPORT_MODULE(mac_turkish);
API_IMPORT_MODULE(mac_ukraine);
API_IMPORT_MODULE(macintosh);
API_IMPORT_MODULE(osd_ebcdic_df04_1);
API_IMPORT_MODULE(osd_ebcdic_df04_15);
API_IMPORT_MODULE(shift_jis);
API_IMPORT_MODULE(ucs2_internal);
API_IMPORT_MODULE(ucs4_internal);
API_IMPORT_MODULE(unicode_1_1_utf_7);
API_IMPORT_MODULE(us_ascii);
API_IMPORT_MODULE(utf_16);
API_IMPORT_MODULE(utf_8);
API_IMPORT_MODULE(windows_1250);
API_IMPORT_MODULE(windows_1251);
API_IMPORT_MODULE(windows_1252);
API_IMPORT_MODULE(windows_1253);
API_IMPORT_MODULE(windows_1254);
API_IMPORT_MODULE(windows_1255);
API_IMPORT_MODULE(windows_1256);
API_IMPORT_MODULE(windows_1257);
API_IMPORT_MODULE(windows_1258);

static struct static_iconv_module {
    const char *name;
    int        present;
    iconv_module_desc_t *module;
} const static_iconv_modules[] = {
    { "_tbl_simple", API_USE_MODULE(_tbl_simple) },
    { "adobe-stdenc", API_USE_MODULE(adobe_stdenc) },
    { "adobe-symbol", API_USE_MODULE(adobe_symbol) },
    { "adobe-zdingbats", API_USE_MODULE(adobe_zdingbats) },
    { "big5", API_USE_MODULE(big5) },
    { "cns11643-plane1", API_USE_MODULE(cns11643_plane1) },
    { "cns11643-plane14", API_USE_MODULE(cns11643_plane14) },
    { "cns11643-plane2", API_USE_MODULE(cns11643_plane2) },
    { "cp037", API_USE_MODULE(cp037) },
    { "cp038", API_USE_MODULE(cp038) },
    { "cp10000", API_USE_MODULE(cp10000) },
    { "cp10006", API_USE_MODULE(cp10006) },
    { "cp10007", API_USE_MODULE(cp10007) },
    { "cp10029", API_USE_MODULE(cp10029) },
    { "cp1006", API_USE_MODULE(cp1006) },
    { "cp10079", API_USE_MODULE(cp10079) },
    { "cp10081", API_USE_MODULE(cp10081) },
    { "cp1026", API_USE_MODULE(cp1026) },
    { "cp273", API_USE_MODULE(cp273) },
    { "cp274", API_USE_MODULE(cp274) },
    { "cp275", API_USE_MODULE(cp275) },
    { "cp277", API_USE_MODULE(cp277) },
    { "cp278", API_USE_MODULE(cp278) },
    { "cp280", API_USE_MODULE(cp280) },
    { "cp281", API_USE_MODULE(cp281) },
    { "cp284", API_USE_MODULE(cp284) },
    { "cp285", API_USE_MODULE(cp285) },
    { "cp290", API_USE_MODULE(cp290) },
    { "cp297", API_USE_MODULE(cp297) },
    { "cp420", API_USE_MODULE(cp420) },
    { "cp423", API_USE_MODULE(cp423) },
    { "cp424", API_USE_MODULE(cp424) },
    { "cp437", API_USE_MODULE(cp437) },
    { "cp500", API_USE_MODULE(cp500) },
    { "cp737", API_USE_MODULE(cp737) },
    { "cp775", API_USE_MODULE(cp775) },
    { "cp850", API_USE_MODULE(cp850) },
    { "cp851", API_USE_MODULE(cp851) },
    { "cp852", API_USE_MODULE(cp852) },
    { "cp855", API_USE_MODULE(cp855) },
    { "cp856", API_USE_MODULE(cp856) },
    { "cp857", API_USE_MODULE(cp857) },
    { "cp860", API_USE_MODULE(cp860) },
    { "cp861", API_USE_MODULE(cp861) },
    { "cp862", API_USE_MODULE(cp862) },
    { "cp863", API_USE_MODULE(cp863) },
    { "cp864", API_USE_MODULE(cp864) },
    { "cp865", API_USE_MODULE(cp865) },
    { "cp866", API_USE_MODULE(cp866) },
    { "cp868", API_USE_MODULE(cp868) },
    { "cp869", API_USE_MODULE(cp869) },
    { "cp870", API_USE_MODULE(cp870) },
    { "cp871", API_USE_MODULE(cp871) },
    { "cp874", API_USE_MODULE(cp874) },
    { "cp875", API_USE_MODULE(cp875) },
    { "cp880", API_USE_MODULE(cp880) },
    { "cp891", API_USE_MODULE(cp891) },
    { "cp903", API_USE_MODULE(cp903) },
    { "cp904", API_USE_MODULE(cp904) },
    { "cp905", API_USE_MODULE(cp905) },
    { "cp918", API_USE_MODULE(cp918) },
    { "cp932", API_USE_MODULE(cp932) },
    { "cp936", API_USE_MODULE(cp936) },
    { "cp949", API_USE_MODULE(cp949) },
    { "cp950", API_USE_MODULE(cp950) },
    { "dec-mcs", API_USE_MODULE(dec_mcs) },
    { "ebcdic-at-de", API_USE_MODULE(ebcdic_at_de) },
    { "ebcdic-at-de-a", API_USE_MODULE(ebcdic_at_de_a) },
    { "ebcdic-ca-fr", API_USE_MODULE(ebcdic_ca_fr) },
    { "ebcdic-dk-no", API_USE_MODULE(ebcdic_dk_no) },
    { "ebcdic-dk-no-a", API_USE_MODULE(ebcdic_dk_no_a) },
    { "ebcdic-es", API_USE_MODULE(ebcdic_es) },
    { "ebcdic-es-a", API_USE_MODULE(ebcdic_es_a) },
    { "ebcdic-es-s", API_USE_MODULE(ebcdic_es_s) },
    { "ebcdic-fi-se", API_USE_MODULE(ebcdic_fi_se) },
    { "ebcdic-fi-se-a", API_USE_MODULE(ebcdic_fi_se_a) },
    { "ebcdic-fr", API_USE_MODULE(ebcdic_fr) },
    { "ebcdic-it", API_USE_MODULE(ebcdic_it) },
    { "ebcdic-pt", API_USE_MODULE(ebcdic_pt) },
    { "ebcdic-uk", API_USE_MODULE(ebcdic_uk) },
    { "ebcdic-us", API_USE_MODULE(ebcdic_us) },
    { "euc-jp", API_USE_MODULE(euc_jp) },
    { "euc-kr", API_USE_MODULE(euc_kr) },
    { "euc-tw", API_USE_MODULE(euc_tw) },
    { "gb12345", API_USE_MODULE(gb12345) },
    { "gb2312", API_USE_MODULE(gb2312) },
    { "gb_2312-80", API_USE_MODULE(gb_2312_80) },
    { "hp-roman8", API_USE_MODULE(hp_roman8) },
    { "iso646-dk", API_USE_MODULE(iso646_dk) },
    { "iso646-kr", API_USE_MODULE(iso646_kr) },
    { "iso-10646-ucs-2", API_USE_MODULE(iso_10646_ucs_2) },
    { "iso-10646-ucs-4", API_USE_MODULE(iso_10646_ucs_4) },
    { "iso-2022-cn", API_USE_MODULE(iso_2022_cn) },
    { "iso-2022-jp", API_USE_MODULE(iso_2022_jp) },
    { "iso-2022-jp-2", API_USE_MODULE(iso_2022_jp_2) },
    { "iso-2022-kr", API_USE_MODULE(iso_2022_kr) },
    { "iso-8859-1", API_USE_MODULE(iso_8859_1) },
    { "iso-8859-10", API_USE_MODULE(iso_8859_10) },
    { "iso-8859-13", API_USE_MODULE(iso_8859_13) },
    { "iso-8859-14", API_USE_MODULE(iso_8859_14) },
    { "iso-8859-15", API_USE_MODULE(iso_8859_15) },
    { "iso-8859-2", API_USE_MODULE(iso_8859_2) },
    { "iso-8859-3", API_USE_MODULE(iso_8859_3) },
    { "iso-8859-4", API_USE_MODULE(iso_8859_4) },
    { "iso-8859-5", API_USE_MODULE(iso_8859_5) },
    { "iso-8859-6", API_USE_MODULE(iso_8859_6) },
    { "iso-8859-7", API_USE_MODULE(iso_8859_7) },
    { "iso-8859-8", API_USE_MODULE(iso_8859_8) },
    { "iso-8859-9", API_USE_MODULE(iso_8859_9) },
    { "iso-ir-10", API_USE_MODULE(iso_ir_10) },
    { "iso-ir-102", API_USE_MODULE(iso_ir_102) },
    { "iso-ir-103", API_USE_MODULE(iso_ir_103) },
    { "iso-ir-11", API_USE_MODULE(iso_ir_11) },
    { "iso-ir-111", API_USE_MODULE(iso_ir_111) },
    { "iso-ir-121", API_USE_MODULE(iso_ir_121) },
    { "iso-ir-122", API_USE_MODULE(iso_ir_122) },
    { "iso-ir-123", API_USE_MODULE(iso_ir_123) },
    { "iso-ir-128", API_USE_MODULE(iso_ir_128) },
    { "iso-ir-13", API_USE_MODULE(iso_ir_13) },
    { "iso-ir-139", API_USE_MODULE(iso_ir_139) },
    { "iso-ir-14", API_USE_MODULE(iso_ir_14) },
    { "iso-ir-141", API_USE_MODULE(iso_ir_141) },
    { "iso-ir-142", API_USE_MODULE(iso_ir_142) },
    { "iso-ir-143", API_USE_MODULE(iso_ir_143) },
    { "iso-ir-146", API_USE_MODULE(iso_ir_146) },
    { "iso-ir-147", API_USE_MODULE(iso_ir_147) },
    { "iso-ir-15", API_USE_MODULE(iso_ir_15) },
    { "iso-ir-150", API_USE_MODULE(iso_ir_150) },
    { "iso-ir-151", API_USE_MODULE(iso_ir_151) },
    { "iso-ir-152", API_USE_MODULE(iso_ir_152) },
    { "iso-ir-153", API_USE_MODULE(iso_ir_153) },
    { "iso-ir-154", API_USE_MODULE(iso_ir_154) },
    { "iso-ir-155", API_USE_MODULE(iso_ir_155) },
    { "iso-ir-158", API_USE_MODULE(iso_ir_158) },
    { "iso-ir-16", API_USE_MODULE(iso_ir_16) },
    { "iso-ir-17", API_USE_MODULE(iso_ir_17) },
    { "iso-ir-18", API_USE_MODULE(iso_ir_18) },
    { "iso-ir-19", API_USE_MODULE(iso_ir_19) },
    { "iso-ir-2", API_USE_MODULE(iso_ir_2) },
    { "iso-ir-21", API_USE_MODULE(iso_ir_21) },
    { "iso-ir-25", API_USE_MODULE(iso_ir_25) },
    { "iso-ir-27", API_USE_MODULE(iso_ir_27) },
    { "iso-ir-37", API_USE_MODULE(iso_ir_37) },
    { "iso-ir-4", API_USE_MODULE(iso_ir_4) },
    { "iso-ir-47", API_USE_MODULE(iso_ir_47) },
    { "iso-ir-49", API_USE_MODULE(iso_ir_49) },
    { "iso-ir-50", API_USE_MODULE(iso_ir_50) },
    { "iso-ir-51", API_USE_MODULE(iso_ir_51) },
    { "iso-ir-54", API_USE_MODULE(iso_ir_54) },
    { "iso-ir-55", API_USE_MODULE(iso_ir_55) },
    { "iso-ir-57", API_USE_MODULE(iso_ir_57) },
    { "iso-ir-60", API_USE_MODULE(iso_ir_60) },
    { "iso-ir-61", API_USE_MODULE(iso_ir_61) },
    { "iso-ir-69", API_USE_MODULE(iso_ir_69) },
    { "iso-ir-70", API_USE_MODULE(iso_ir_70) },
    { "iso-ir-84", API_USE_MODULE(iso_ir_84) },
    { "iso-ir-85", API_USE_MODULE(iso_ir_85) },
    { "iso-ir-86", API_USE_MODULE(iso_ir_86) },
    { "iso-ir-88", API_USE_MODULE(iso_ir_88) },
    { "iso-ir-89", API_USE_MODULE(iso_ir_89) },
    { "iso-ir-8-1", API_USE_MODULE(iso_ir_8_1) },
    { "iso-ir-8-2", API_USE_MODULE(iso_ir_8_2) },
    { "iso-ir-90", API_USE_MODULE(iso_ir_90) },
    { "iso-ir-91", API_USE_MODULE(iso_ir_91) },
    { "iso-ir-92", API_USE_MODULE(iso_ir_92) },
    { "iso-ir-93", API_USE_MODULE(iso_ir_93) },
    { "iso-ir-94", API_USE_MODULE(iso_ir_94) },
    { "iso-ir-95", API_USE_MODULE(iso_ir_95) },
    { "iso-ir-96", API_USE_MODULE(iso_ir_96) },
    { "iso-ir-98", API_USE_MODULE(iso_ir_98) },
    { "iso-ir-99", API_USE_MODULE(iso_ir_99) },
    { "iso-ir-9-1", API_USE_MODULE(iso_ir_9_1) },
    { "iso-ir-9-2", API_USE_MODULE(iso_ir_9_2) },
    { "jis_x0201", API_USE_MODULE(jis_x0201) },
    { "jis_x0208-1983", API_USE_MODULE(jis_x0208_1983) },
    { "jis_x0212-1990", API_USE_MODULE(jis_x0212_1990) },
    { "johab", API_USE_MODULE(johab) },
    { "koi8-r", API_USE_MODULE(koi8_r) },
    { "koi8-ru", API_USE_MODULE(koi8_ru) },
    { "koi8-u", API_USE_MODULE(koi8_u) },
    { "ksx1001", API_USE_MODULE(ksx1001) },
    { "mac-ce", API_USE_MODULE(mac_ce) },
    { "mac-croatian", API_USE_MODULE(mac_croatian) },
    { "mac-cyrillic", API_USE_MODULE(mac_cyrillic) },
    { "mac-dingbats", API_USE_MODULE(mac_dingbats) },
    { "mac-greek", API_USE_MODULE(mac_greek) },
    { "mac-iceland", API_USE_MODULE(mac_iceland) },
    { "mac-japan", API_USE_MODULE(mac_japan) },
    { "mac-roman", API_USE_MODULE(mac_roman) },
    { "mac-romania", API_USE_MODULE(mac_romania) },
    { "mac-thai", API_USE_MODULE(mac_thai) },
    { "mac-turkish", API_USE_MODULE(mac_turkish) },
    { "mac-ukraine", API_USE_MODULE(mac_ukraine) },
    { "macintosh", API_USE_MODULE(macintosh) },
    { "osd_ebcdic_df04_1", API_USE_MODULE(osd_ebcdic_df04_1) },
    { "osd_ebcdic_df04_15", API_USE_MODULE(osd_ebcdic_df04_15) },
    { "shift_jis", API_USE_MODULE(shift_jis) },
    { "ucs2-internal", API_USE_MODULE(ucs2_internal) },
    { "ucs4-internal", API_USE_MODULE(ucs4_internal) },
    { "unicode-1-1-utf-7", API_USE_MODULE(unicode_1_1_utf_7) },
    { "us-ascii", API_USE_MODULE(us_ascii) },
    { "utf-16", API_USE_MODULE(utf_16) },
    { "utf-8", API_USE_MODULE(utf_8) },
    { "windows-1250", API_USE_MODULE(windows_1250) },
    { "windows-1251", API_USE_MODULE(windows_1251) },
    { "windows-1252", API_USE_MODULE(windows_1252) },
    { "windows-1253", API_USE_MODULE(windows_1253) },
    { "windows-1254", API_USE_MODULE(windows_1254) },
    { "windows-1255", API_USE_MODULE(windows_1255) },
    { "windows-1256", API_USE_MODULE(windows_1256) },
    { "windows-1257", API_USE_MODULE(windows_1257) },
    { "windows-1258", API_USE_MODULE(windows_1258) },

    { NULL, 0, NULL}
};

static const size_t static_iconv_modules_count =
    sizeof(static_iconv_modules)/sizeof(static_iconv_modules[0]) - 1;


/* Compare two static modules. */
static int static_iconv_module_compare (const void *u, const void *v)
{
    const struct static_iconv_module *const a = u;
    const struct static_iconv_module *const b = v;
    return strcmp(a->name, b->name);
}

static iconv_module_desc_t *static_iconv_module_find(const char *name)
{
    struct static_iconv_module key;
    struct static_iconv_module *val;
#if 'A' == '\xC1' /* if EBCDIC host */
    /* The table is sorted in ASCII collation order, not in EBCDIC order.
     * At the first access, we sort it automatically
     * Criterion for the 1st time initialization is the fact that the
     * 1st name in the list starts with a digit (in ASCII, numbers
     * have a lower ordinal value than alphabetic characters; while
     * in EBCDIC, their ordinal value is higher)
     */
    if (isdigit(static_iconv_modules[0].name[0]))  {
        qsort((void *)static_iconv_modules, static_iconv_modules_count,
              sizeof(static_iconv_modules[0]),
              static_iconv_module_compare);
    }
#endif
    key.name = name;
    val = bsearch(&key, static_iconv_modules, static_iconv_modules_count,
                  sizeof(static_iconv_modules[0]),
                  static_iconv_module_compare);
    if (val)
        return val->module;
    else
        return NULL;
}


static int
iconv_smopen(const char *name, void **dpp)
{

    iconv_module_desc_t *module = static_iconv_module_find(name);
    if (!module) {
        const char *alias = charset_alias_find(name);
        if (alias) {
            if ((module = static_iconv_module_find(alias))) {
                *dpp = module;
                return 0;
            }
        }
    }
    else {
        *dpp = module;
        return 0;
    }
    return EINVAL;
}

static apr_status_t
iconv_getpathname(char *buffer, const char *dir, const char *name, apr_pool_t *ctx)
{
        apr_status_t rv;
	apr_finfo_t sb;

	apr_snprintf(buffer, APR_PATH_MAX, "%s/%s.so", dir, name);
        rv = apr_stat(&sb, buffer, APR_FINFO_TYPE, ctx);
#ifdef API_HAVE_CHARSET_ALIAS_TABLE
        /* If we didn't find the file, try again after looking in
           the charset alias mapping table. */
        if (rv || sb.filetype != APR_REG) {
            const char *alias = charset_alias_find(name);
            if (alias) {
                apr_snprintf(buffer, APR_PATH_MAX, "%s/%s.so", dir, alias);
                rv = apr_stat(&sb, buffer, APR_FINFO_TYPE, ctx);
            }
        }
#endif /* API_HAVE_CHARSET_ALIAS_TABLE */
        if (!rv && sb.filetype != APR_REG)
            rv = APR_EINVAL;

        return rv;
}

static apr_status_t
iconv_getpath(char *buf, const char *name, apr_pool_t *ctx)
{
	char buffer[APR_PATH_MAX];
        apr_array_header_t *pathelts;
        apr_pool_t *subpool;
        apr_status_t status;
	char *ptr;

        status = apr_pool_create(&subpool, ctx);
        if (status)
            return status;

	if (apr_tolower(name[0]) == 'x' && name[1] == '-')
		name += 2;
        ptr = buffer;
        while (0 != (*ptr++ = apr_tolower(*name++)))
            ;

        /* Fall back on APR_ICONV_PATH if APR_ICONVn_PATH isn't set...
         * TODO: Drop support for "APR_ICONV_PATH" in apr-iconv 2.0
         */
        if ((!apr_env_get(&ptr, APR_ICONV_PATH, subpool)
             || (!apr_env_get(&ptr, "APR_ICONV_PATH", subpool)))
            && !apr_filepath_list_split(&pathelts, ptr, subpool))
        {
            int i;
            char **elts = (char **)pathelts->elts;
            for (i = 0; i < pathelts->nelts; ++i)
            {
                if (iconv_getpathname(buf, elts[i], buffer, subpool) == 0)
                {
                    apr_pool_destroy(subpool);
                    return APR_SUCCESS;
                }
            }
        }

        status = iconv_getpathname(buf, ICONV_DEFAULT_PATH, buffer, subpool);
        apr_pool_destroy(subpool);
        return status;
}

static int
iconv_dlopen(const char *name, const char *symbol, void **hpp, void **dpp, apr_pool_t *ctx)
{
	apr_dso_handle_t *handle;
	void *data;

	/* dlopen */
	if (apr_dso_load(&handle, name, ctx) != APR_SUCCESS) {
		return EINVAL;
	}
	/* dlsym */
	if ( apr_dso_sym(&data, handle, symbol) == APR_SUCCESS) {
		*hpp = handle;
		*dpp = data;
		return 0;
	}
	apr_dso_unload(handle);
	return EINVAL;
}


API_DECLARE_NONSTD(int)
apr_iconv_mod_load(const char *modname, int modtype, const void *args,
	struct iconv_module **modpp, apr_pool_t *ctx)
{
	struct iconv_module_desc *mdesc;
	struct iconv_module *mod, *depmod;
	const struct iconv_module_depend *depend;
	char buffer[APR_PATH_MAX];
	void *handle = NULL;
	int error;
	
	/* Try to load the built-in modules first */
	error = iconv_smopen(buffer, (void**)&mdesc);
	if (error) {
		if (iconv_getpath(buffer, modname, ctx) != 0)
			return EINVAL;

		error = iconv_dlopen(buffer, "iconv_module", &handle, (void**)&mdesc, ctx);
	}
	if (error)
		return error;
	if (modtype != ICMOD_ANY && mdesc->imd_type != modtype) {
		if (handle)
			apr_dso_unload(handle);
		return APR_EFTYPE;
	}
	mod = malloc(sizeof(*mod));
	if (mod == NULL) {
		if (handle)
			apr_dso_unload(handle);
		return ENOMEM;
	}
	memset(mod, 0, sizeof(*mod));
	mod->im_handle = handle;
	mod->im_desc = mdesc;
	mod->im_args = args;
	depend = mdesc->imd_depend;
	if (depend) {
		while (depend->md_name) {
			error = apr_iconv_mod_load(depend->md_name, 
			    depend->md_type, NULL, &depmod, ctx);
			if (error)
				goto bad;
			depmod->im_depdata = depend->md_data;
			depmod->im_next = mod->im_deplist;
			mod->im_deplist = depmod;
			depend++;
		}
	}
	error = ICONV_MOD_DYN_LOAD(mod,ctx);
	if (error)
		goto bad;
	depmod = mod->im_deplist;
	while (depmod) {
		mod->im_depcnt++;
		depmod = depmod->im_next;
	}
	error = ICONV_MOD_LOAD(mod,ctx);
	if (error)
		goto bad;
	mod->im_flags |= ICMODF_LOADED;
	*modpp = mod;
	return 0;
bad:
	apr_iconv_mod_unload(mod,ctx);
	return error;
}

API_DECLARE_NONSTD(int)
apr_iconv_mod_unload(struct iconv_module *mod, apr_pool_t *ctx)
{
	struct iconv_module *deplist, *tmp;
	int error = 0;

	if (mod == NULL)
		return -1;
	if (mod->im_flags & ICMODF_LOADED)
		error = ICONV_MOD_UNLOAD(mod,ctx);
	error = ICONV_MOD_DYN_UNLOAD(mod,ctx);
	deplist = mod->im_deplist;
	while (deplist) {
		tmp = deplist->im_next;
		apr_iconv_mod_unload(deplist,ctx);
		deplist = tmp;
	}
	if (mod->im_handle != NULL)
		if (apr_dso_unload(mod->im_handle) != APR_SUCCESS)
			error = APR_EINVAL;
	free(mod);
	return error;
}

API_DECLARE_NONSTD(int)
apr_iconv_mod_noevent(struct iconv_module *mod, int event, apr_pool_t *ctx)
{
	switch (event) {
	    case ICMODEV_LOAD:
	    case ICMODEV_UNLOAD:
	    case ICMODEV_DYN_LOAD:
	    case ICMODEV_DYN_UNLOAD:
		break;
	    default:
		return APR_EINVAL;
	}
	return 0;
}
