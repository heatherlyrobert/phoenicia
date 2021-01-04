#include    "font.h"



/*---(file)---------------------------*/
char        g_name      [100]         = "";
FILE       *g_file      = NULL;
char        g_recd      [2000];

tCH         g_char      [LEN_CHARSET];

/*---(glyph)--------------------------*/
int         g_map       [16];               /* map 16 glyphs into charset pos */

char        g_font       [LEN_LABEL] = "Shrike";  /* font name                */
char        g_pointsz    [LEN_LABEL] = "100";     /* full top-to-bottom       */
char        g_pixelsz    [LEN_LABEL] = "10";      /* full top-to-bottom       */
int         g_tall                   = 10;        /* full top-to-bottom       */
int         g_ascent                 =  8;        /* space between letters    */
int         g_descent                =  2;        /* space between letters    */
int         g_upper                  =  7;        /* capital ascend           */
int         g_lower                  =  5;        /* lower ascend             */
int         g_wide                   =  6;        /* width of characters      */
int         g_space                  =  2;        /* space between letters    */



/*====================------------------------------------====================*/
/*===----                         file level                           ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

char
inpt__begin          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         k           =    0;
   /*---(open)---------------------------*/
   /*> strlcpy (g_name, FILE_SHRIKE, 100);                                            <*/
   g_file = fopen (g_name, "r");
   if (g_file == NULL) {
      return -1;
   }
   /*---(initialize g_char)--------------*/
   for (i = 0; i < 256; ++i) {
      strcpy (g_char [i].name, "");
      g_char [i].abbr = '\0';
      g_char [i].key  = '-';
      for (j = 0; j < 10; ++j) {
        g_char [i].bytes [j] = 0;
        for (k = 0; k < 8; ++k) {
           g_char [i].image [j][k] = '-';
        }
      }
   }
   /*---(initialize map)-----------------*/
   for (i = 0; i < 16; ++i) {
      g_map [i] = 0;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
share_shrike         (void)
{
   strcpy  (g_name, FILE_SHRIKE);
   sprintf (g_font, "%s", "Shrike");
   g_tall      = 10;
   sprintf (g_pointsz , "%d", g_tall * 10);
   sprintf (g_pixelsz , "%d", g_tall);
   g_ascent    =  8;
   g_descent   =  2;
   g_upper     =  7;
   g_lower     =  5;
   g_wide      =  6;
   g_space     =  2;
   return 0;
}

char
share_square         (void)
{
   strcpy  (g_name, FILE_SQUARE);
   sprintf (g_font, "%s", "Square");
   g_tall      =  6;
   sprintf (g_pointsz , "%d", g_tall * 10);
   sprintf (g_pixelsz , "%d", g_tall);
   g_ascent    =  5;
   g_descent   =  1;
   g_upper     =  5;
   g_lower     =  3;
   g_wide      =  6;
   g_space     =  2;
   return 0;
}

char
inpt__end            (void)
{
   fclose (g_file);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       row handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLERS________________o (void) {;}

char
inpt__hex            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        x_hex       [LEN_LABEL];
   int         x_pos       =    0;
   /*> printf ("\n");                                                                 <*/
   for (i = 0; i < 16; ++i) {
      x_pos = 0;
      strlcpy  (x_hex, g_recd + 14 + i * 8,  8);
      strltrim (x_hex, ySTR_BOTH, LEN_LABEL);
      sscanf (x_hex, "%x", &x_pos);
      /*> printf ("%3d ", x_pos);                                                     <*/
      g_map [i] = x_pos;
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__names          (int a_offset)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        x_name      [30];
   int         n           = 0;
   /*---(walk names)---------------------*/
   /*> printf ("   -- bytes        :  ");                                             <*/
   for (i = 0; i < 16; i += 2) {
      /*---(get name)--------------------*/
      strlcpy  (x_name, g_recd + 14 + (i + a_offset) * 8, 16);
      strltrim (x_name, ySTR_BOTH, 2000);
      /*---(store it)--------------------*/
      n = g_map [i + a_offset];
      if (strcmp ("-", x_name) == 0)  sprintf (x_name, "char%d", n);
      /*> printf ("%-2d  [%s]\n", i + a_offset, x_name);                              <*/
      strlcpy  (g_char [n].name, x_name, 16);
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__abbr           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         n           =    0;
   uchar       x_short     =    0;
   /*> printf ("%s\n", g_recd);                                                       <*/
   for (i = 0; i < 16; ++i) {
      n = g_map [i];
      x_short = g_recd [14 + (i * 8)];
      /*> printf ("%c ", x_short);                                                    <*/
      switch (x_short) {
      case 172  : g_char [n].abbr = '\0';     break;
      default   : g_char [n].abbr = x_short;  break;
      }
      /*> if (g_char [n].abbr > 0)  printf ("%c ", g_char [n].abbr);                  <* 
       *> else                      printf ("  ");                                    <*/
      x_short = g_recd [14 + (i * 8) + 2];
      if (x_short == (uchar) '´')  g_char [n].key = 'y';
      /*> printf ("%c ", x_short);                                                    <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__char           (int a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         x_val       =    0;
   int         x_byte      =    0;
   int         n           =    0;
   /*> printf ("   -- bytes        :  ");                                             <*/
   for (i = 0; i < 16; ++i) {
      n = g_map [i];
      x_byte = 0;
      for (j = 7; j >= 0; --j) {
         x_val = pow (2, j);
         g_char [n].image [a_row][7 - j] =  ' ';
         if (g_recd [14 + (i * 8) + (7 - j)] == '#') {
            x_byte += x_val;
            g_char [n].image [a_row][7 - j] = '#';
         }
      }
      g_char [n].bytes [a_row] = x_byte;
      /*> printf ("%-2d/%-2d:%-4d  ", i, a_row, g_char [i].bytes [a_row]);                  <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       main driver                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
SHARE_read_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         i, j;
   int         x_line      =    0;
   int         x_row       =    0;
   /*---(file open)----------------------*/
   rc = inpt__begin ();
   --rce;  if (rc < 0) return rce;
   /*---(read file)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (g_recd, 2000, g_file);
      if (feof (g_file)) return -1;
      ++x_line;
      /*---(fix)-------------------------*/
      x_len = strlen (g_recd);
      if (x_len <= 0)  continue;
      g_recd [--x_len] = '\0';
      /*> printf ("%-2d : [%s]\n", x_row, g_recd);                                    <*/
      /*---(handle)----------------------*/
      switch (g_recd [0]) {
      case '#' : case ' ' : case '\n' : case '\0'  :
         break;
      case 'h' :
         inpt__hex  ();
         x_row = 0;
         break;
      case '1' :
         /*> printf ("found inpt__names (0);\n");                                     <*/
         inpt__names (0);
         break;
      case '2' :
         /*> printf ("found inpt__names (1);\n");                                     <*/
         inpt__names (1);
         break;
      case 's' :
         inpt__abbr  ();
         break;
      case 'c' :
         if (x_row <  0)  break;
         inpt__char (x_row);
         ++x_row;
         if (x_row >= g_tall)   x_row = -1;
         break;
      default  :
         break;
      }
      /*> /+---(display)---------------------+/                                       <* 
       *> for (j = 0; j < 10; ++j) {                                                  <* 
       *>    printf ("%2d :");                                                        <* 
       *>    for (i = 0; i < 16; ++i) {                                               <* 
       *>       printf ("  %-4d", g_char [i].bytes [j]);                              <* 
       *>    }                                                                        <* 
       *>    printf ("\n");                                                           <* 
       *> }                                                                           <*/
      /*---(done)------------------------*/
   }
   /*---(file close)---------------------*/
   rc = inpt__end ();
   /*---(complete)-----------------------*/
   return 0;
}
