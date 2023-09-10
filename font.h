/*===============================[[ beg-code ]]===============================*/

/*===============================*/
/*
 *  a 8bit character set is valuable as it...
 *     -- no additional memory required, as it is already built-in
 *     -- requires no special varables beyond a standard char
 *     -- available in all text interfaces
 *     -- requires absolutely zero overhead/libraries
 *     -- can be implemented even on rudamentary chips
 *     -- helps me standardize MY important symbols (hard process)
 *
 *
 *
 *
 *
 *
 *
 *
 */
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

#define     P_FOCUS     "??"
#define     P_NICHE     "??"
#define     P_SUBJECT   "my shrike terminal font (6x10)"
#define     P_PURPOSE   "design and maintenance of charset and personal font"

#define     P_NAMESAKE  "phoenicia-alfavito (letter-givers)"
#define     P_HERITAGE  "country that gave greece its modern alphabet"
#define     P_IMAGERY   "mighty ancient seafaring empire"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2018-10"

#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "1.0c"
#define     P_VERTXT    "fixes due to changed str functions to ¶ystr¶ in ySTR"


#include    <stdio.h>
#include    <string.h>
#include    <math.h>
#include    <ySTR.h>


typedef     unsigned char        uchar;

extern char        g_name       [100];
extern char        g_font       [LEN_LABEL];
extern char        g_pointsz    [LEN_LABEL];
extern char        g_pixelsz    [LEN_LABEL];
extern int         g_tall;
extern int         g_ascent;
extern int         g_descent;
extern int         g_upper;
extern int         g_lower;
extern int         g_wide;
extern int         g_space;

extern FILE       *g_file;
extern char        g_recd      [2000];
extern int         g_line;
extern int         g_row;

#define        LEN_CHARSET      256
typedef     struct      cCH        tCH;
struct cCH {
   char        name        [LEN_LABEL];
   uchar       image       [10][8];
   int         bytes       [10];
   char        abbr;
   char        key;
   uchar       yfont       [59][34];
   uchar       pretty      [59][34];
};
extern       tCH        g_char     [LEN_CHARSET];


char        SHARE_read_all        (void);
char        SHARE_read_yfont      (void);
char        share_shrike          (void);
char        share_square          (void);

#define    FILE_SHRIKE    "/home/system/phoenicia.custom_terminal_font/shrike.txt"
#define    FILE_SQUARE    "/home/system/phoenicia.custom_terminal_font/square.txt"
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
