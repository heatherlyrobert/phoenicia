/*===============================[[ beg-code ]]===============================*/

/*===[[ HEADER ]]=============================================================*/
/*
 *   focus         : ((tbd))
 *   heritage      : phoenicia (originators of the modern greek alphabet)
 *   purpose       : design and maintenance of my personal terminal font
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : none
 *   size          : small       (approximately 2,000 slocL)
 * 
 *   author        : rsheatherly
 *   created       : 2018-10
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, traceable
 */

/*===[[ GREEK HERITAGE ]]=====================================================*/
/*
 *   the earliest written greek was developed by the the minoans (linear a)
 *   then the mycenaeans (linear b).  after the mycenaean culture fell around
 *   1200bce and before ancient greek started around 800bce, the greek writing
 *   system changed radically.
 *   
 *   it is commonly believed that the ancient greek letters are derivations of
 *   the phoenician alphabet, which in turn came from syrian.  the historian 
 *   herodotus wrote that a phoenician named cadmus first introduced the
 *   phoenician alphabet to greece.  it is estimated the was around 1000bce.
 *
 *   the phoenicians were likely the canaanites from the bible.
 *
 */


/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (string handling)"
#define     P_PURPOSE   "provide secure and useful string handling capabilities"

#define     P_NAMESAKE  "phoenicia (the phoenicians)"
#define     P_HERITAGE  "country that gave greece its modern alphabet"
#define     P_IMAGERY   "mighty ancient seafaring empire"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2018-10"
#define     P_DEPENDS   "none"

#define     P_VERNUM    "0.6b"
#define     P_VERTXT    "updated txt2bdf to handle full charset read and new data structure"


#include    <stdio.h>
#include    <math.h>
#include    <ySTR.h>


typedef     unsigned char        uchar;

extern char        g_name      [100];
extern FILE       *g_file;
extern char        g_recd      [2000];
extern int         g_line;
extern int         g_row;

#define        LEN_CHARSET      256
typedef     struct      cCH        tCH;
struct cCH {
   char        name        [LEN_LABEL];
   int         image       [10][8];
   int         bytes       [10];
   char        abbr;
   char        key;
};
extern       tCH        g_char     [LEN_CHARSET];


char        SHARE_read_all        (void);

#define    FILE_SOURCE    "/home/system/phoenicia.custom_terminal_font/shrike.txt"
/*
 *
 *  pcf   = x11 font (portable compiled format)
 *  bdf   = adobe human-readable bitmap distribution format (latest in 2013)
 *  psf   = kernel/terminal font
 *
 *  pcf2bdf
 *  bdftopcf
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
