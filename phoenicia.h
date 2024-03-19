/*===============================[[ beg-code ]]===============================*/
#ifndef PHOENICIA
#define PHOENICIA  loaded

/*===[[ HEADER ]]=============================================================*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "??"
#define     P_NICHE     "??"
#define     P_SUBJECT   "my shrike terminal font (6x10)"
#define     P_PURPOSE   "design and maintenance of charset and personal font"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "phoenicia-alfavito (letter-givers)"
#define     P_PRONOUNCE "foh·nee·cee·ah ahl·fa·vee·toh"
#define     P_HERITAGE  "country that gave greece its modern alphabet"
#define     P_BRIEFLY   "source of greek alphabet"
#define     P_IMAGERY   "mighty ancient seafaring empire, birthed carthagenian empire"
#define     P_REASON    "letter source"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/phoenicia.custom_terminal_font"
#define     P_BASENAME  "phoenicia"
#define     P_FULLPATH  "/usr/local/bin/phoenicia"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,string,math"
#define     P_DEPPOSIX  ""
#define     P_DEPCORE   "ySTR,yURG"
#define     P_DEPVIKEY  ""
#define     P_DEPGRAPH  ""
#define     P_DEPOTHER  ""                    
#define     P_DEPSOLO   ""
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2018-10"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, bring together into one package"
#define     P_VERMINOR  "2.0-, integrate and test"
#define     P_VERNUM    "2.0b,"
#define     P_VERTXT    "integrated charmap now"
/*········· ··········· ´·····························´········································*/
#define     P_TOPLINE   "structure, standards, limits, auditing, debugging, and tracing"
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
#define     P_HEADERS   P_FOCUS, P_NICHE, P_SUBJECT, P_PURPOSE, P_NAMESAKE, P_PRONOUNCE, P_HERITAGE, P_BRIEFLY, P_IMAGERY, P_REASON, P_ONELINE, P_HOMEDIR, P_BASENAME, P_FULLPATH, P_SUFFIX, P_CONTENT, P_SYSTEM, P_LANGUAGE, P_COMPILER, P_CODESIZE, P_DEPSTRC, P_DEPPOSIX, P_DEPCORE, P_DEPVIKEY, P_DEPOTHER, P_DEPGRAPH, P_DEPSOLO, P_AUTHOR, P_CREATED, P_VERMAJOR, P_VERMINOR, P_VERNUM, P_VERTXT
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

/*
 *   GLOBAL VIEW...
 *   i whole-heartedly support the world using unicode, wchar, etc and its inclusive characters.
 *   why should anyone be forced to distort their language to fit ancient thinking.  i will
 *   gladly use it to build software for more inclusive use.  the world is moving forward.
 *
 *   PERSONAL VIEW...
 *   i seek to use the minimum resources (power, cpu, ram, disk, ...) to accomplish my
 *   task.  as stated everywhere, i do overbuild debugging, transparency, tracing, auditing, and
 *   diagnostics.  save in one place, lose it in another ;)
 *
 *   that way, cheaper, easier to support, never tied to whims of other developers.
 *
 *   i speak and use only one language.  i need a-z, 0-9, and common punctuation.  i sometimes find
 *   use for upper case letters.  i really do use half of the 00-1f control characters.  so i will
 *   keep the 7-bit ASCII standard is sacrosanct.  it is well done.
 *
 *   90% of the second half is just useless to me.  if i break compatibility, i can develop my
 *   own 128 characters for macro control, more math, logic, and greek letters (for variables).  i
 *   also surprised myself with great use of custom line-drawing characters.  who knew?
 *
 *
 *   why???
 *     -- i choose to keep things extremely simple, efficient, and small (emulate computer origins)
 *     -- i choose to use 8-bit fonts only, that allows all basics, plus 128 extra chars
 *     -- if you want 257 characters, everything breaks for chars and strings which requires new libraries
 *     -- i want to adjust things to fit my needs, not 100 decent font options
 *     -- therefore, i will need to design and change characters for size or wholly new
 *     -- this all means ASCII standard, plus my own glyphs in top half (80-FF)
 *     -- i will keep my fonts in txt files, visually laid out
 *     -- this program will create BDF, PCF, PSF, TXF, etc form that text file (one stop)
 *
 *
 *
 *
 *
 */

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
 */


#include    <stdio.h>
#include    <string.h>
#include    <stdint.h>
#include    <math.h>
#include    <ySTR.h>
#include    <yURG.h>


#define     MAX_CHARSET    256
#define     MAX_LINE       16

#define     RUNMODE_CHARMAP  '!'

#define     RUNMODE_QUIET    '-'
#define     RUNMODE_CONFIRM  'c'
#define     RUNMODE_VERBOSE  'v'

#define     RUNMODE_CHECK    'c'
#define     RUNMODE_TXT2BDF  'b'
#define     RUNMODE_TXT2PSF  's'

#define     RUNFILE_SQUARE "/home/system/phoenicia.custom_terminal_font/square.txt"
#define     RUNFILE_SHRIKE "/home/system/phoenicia.custom_terminal_font/shrike.txt"


typedef     unsigned char        uchar;

typedef  struct cMY tMY;
struct  cMY {
   char        run_loud;               /* quiet, confirm, or verbose  */
   char        run_mode;               /* audit, txt2bdf, etc         */
   char        run_file   [LEN_PATH];  /* actual txt file             */
   char        bdf_file   [LEN_PATH];  /* actual bdf file             */
   char        psf_file   [LEN_PATH];  /* actual psf file             */
};
extern  tMY  my;





/*> extern char        g_name       [LEN_LABEL];                                      <*/
/*> extern char        g_font       [LEN_LABEL];                                      <*/
/*> extern char        g_pointsz    [LEN_LABEL];                                      <*/
/*> extern char        g_pixelsz    [LEN_LABEL];                                      <*/

extern char        g_title      [LEN_DESC];

extern int         g_wide;
extern int         g_tall;

extern int         g_ascent;
extern int         g_descent;

extern int         g_upper;
extern int         g_lower;

extern int         g_prefix;
extern int         g_gap;
extern int         g_next;

extern int         g_cen;
extern int         g_mid;

/*> extern FILE       *g_file;                                                        <*/
/*> extern char        g_recd      [2000];                                            <*/
/*> extern int         g_line;                                                        <*/
/*> extern int         g_row;                                                         <*/

typedef     struct      cCH        tCH;
struct cCH {
   /*---(source)-------------------------*/
   int         hexline;                              /* source line           */
   char        hexcol;                               /* source column         */
   /*---(basics)-------------------------*/
   char        name        [LEN_LABEL];              /* internal name         */
   uchar       image       [LEN_LABEL][LEN_LABEL];   /* diagram               */
   char        abbr;                                 /* short-code            */
   /*---(working)------------------------*/
   int         bytes       [LEN_LABEL];              /* byte for line         */
   char        key;
   char        ready;                                /* all data prepared     */
   /*---(statistics)---------------------*/
   int         pixels;
   int         verts       [LEN_LABEL];
   float       vert;
   int         horzs       [LEN_LABEL];
   float       horz;
   int         diags       [LEN_LABEL];
   float       diag;
   /*---(texturn font)-------------------*/
   uchar       yfont       [59][34];
   uchar       pretty      [59][34];
   /*---(done)---------------------------*/
};
extern       tCH        g_char     [MAX_CHARSET];


/*> char        SHARE_read_all        (void);                                         <*/
/*> char        SHARE_read_yfont      (void);                                         <*/
/*> char        share_shrike          (void);                                         <*/
/*> char        share_square          (void);                                         <*/

#define    FILE_SHRIKE    "/home/system/phoenicia.custom_terminal_font/shrike.txt"
#define    FILE_SQUARE    "/home/system/phoenicia.custom_terminal_font/square.txt"

/*===============================*/
/*
 *  8bit character file means...
 *     -- fits in standard c-type char (as designed)
 *     -- does not require ¶wchar¶ type
 *     -- can work on absolutely any processor
 *     -- does not require additional processing or libraries to interpret
 *     -- limited to 256 characters (8-bit)
 *     -- standard 32 control characters are not printable
 *     -- char 127 also not useable (bs/del)
 *     -- 223 printable characters for my use
 *
 *
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





/*===[[ PHOENICIA_PROG.C ]]===================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(support)--------------*/
char        PROG_help               (void);
char*       PROG_version            (void);
/*---(preinit)--------------*/
char        PROG_urgents            (int a_argc, char *a_argv []);
/*---(startup)--------------*/
char        PROG__init              (int a_argc, char *a_argv []);
char        PROG__args              (int a_argc, char *a_argv []);
char        PROG__begin             (void);
char        PROG_startup            (int a_argc, char *a_argv []);
/*---(execute)--------------*/
char        PROG_driver             (char a_mode);
/*---(shutdown)-------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(done)-----------------*/



/*===[[ PHOENICIA_TEST.C ]]===================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);



/*===[[ PHOENICIA_FILE.C ]]===================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        FILE_open               (char a_name [LEN_PATH], char a_access, char r_name [LEN_PATH], char *r_mode, FILE **r_file);
char        FILE_close              (char r_name [LEN_PATH], char *r_mode, FILE **r_file);



/*===[[ PHOENICIA_TXT.C ]]====================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(program)--------------*/
char        TXT__clear              (uchar n);
char        TXT_purge               (void);
/*---(control)--------------*/
char        TXT__title              (int a_line, char a_recd [LEN_RECD], char r_title [LEN_DESC]);
char        TXT__sizing             (int a_line, char a_recd [LEN_RECD], char *r_wide, char *r_tall, char *r_ascent, char *r_descent, char *r_upper, char *r_lower, char *r_prefix, char *r_gap, char *r_next, char *r_center, char *r_middle);
/*---(lines)----------------*/
char        TXT__hex                (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short r_map [MAX_LINE]);
char        TXT__name               (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short a_map [MAX_LINE]);
char        TXT__image              (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short a_tall, short a_map [MAX_LINE]);
/*---(driver)---------------*/
char        TXT__verify             (uchar a_index, char a_wide, char a_tall);
char        TXT__audit              (char a_wide, char a_tall);
char        TXT_get_all             (char a_audit, cchar a_txtfile [LEN_PATH]);
/*---(unittest)-------------*/
char*       TXT__show_map           (short a_map [MAX_LINE]);
char*       TXT__show_charset       (char a_type, char a_wide, char a_tall);
char*       TXT__show_vert          (uchar a_index);
/*---(done)-----------------*/



/*===[[ PHOENICIA_BDF.C ]]====================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        BDF__header             (FILE *f, char a_title [LEN_LABEL], char a_wide, char a_tall, char a_ascent, char a_descent, char a_upper, char a_lower);
char        BDF__glyph              (FILE *f, uchar a_index, char a_wide, char a_tall, char a_descent);
char        BDF__footer             (FILE *f);
char        BDF_make_all            (char a_bdffile [LEN_PATH], char a_title [LEN_DESC], char a_wide, char a_tall, char a_ascent, char a_descent, char a_upper, char a_lower);



/*===[[ PHOENICIA_PSF.C ]]====================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        PSF__header             (FILE *f, char a_wide, char a_tall, char *r_bits);
char*       PSF__show_header        (char a_psffile [LEN_PATH]);
char        PSF__glyph              (FILE *f, uchar a_index, char a_bits, char a_wide, char a_tall);
char*       PSF__show_glyph         (char a_psffile [LEN_PATH], uchar a_index, char a_bytes, char a_wide, char a_tall);
char        PSF_make_all            (char a_psffile [LEN_PATH], char a_wide, char a_tall);


char        charmap_main            (void);


#endif

