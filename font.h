#include    <stdio.h>
#include    <math.h>
#include    <ySTR.h>



extern char        g_name      [100];
extern FILE       *g_file;
extern char        g_recd      [2000];
extern int         g_bytes     [16][10];
extern int         g_char;
extern char        g_charname  [256][30];
extern int         g_line;
extern int         g_row;

extern int         g_image     [16][10][8];

char        INPT_begin           (void);
char        INPT_names           (int a_offset);
char        INPT_row             (int a_row);
int         INPT_driver          (void);
char        INPT_end             (void);


#define     VER_NUM     "0.5m"
#define     VER_TXT     "updated chapmap with latest shrike symbols"
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
