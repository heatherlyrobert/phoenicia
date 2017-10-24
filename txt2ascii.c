#include    "font.h"

char        s_trow    [ 10];
char        s_tcol    [  6];
char        s_lef;
char        s_rig;
char        s_top;
char        s_bot;
char        s_quad    [  4];


char
ASCII_row            (char a_match)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_char      =    0;
   int         x_row       =    0;
   int         x_col       =    0;
   char        x_val       =    0;
   int         x_filled    =    0;
   static      x_save      =   -1;
   for (x_char = 0; x_char < 16; ++x_char) {
      /*---(cleanse)---------------------*/
      for (i = 0; i <  6; ++i)  s_tcol [i] = 0;
      for (i = 0; i < 10; ++i)  s_trow [i] = 0;
      for (i = 0; i <  4; ++i)  s_quad [i] = 0;
      s_lef = s_rig = s_top = s_bot = 0;
      x_filled = 0;
      for (x_row = 0; x_row < 10; ++x_row) {
         for (x_col = 0; x_col <  6; ++x_col) {
            x_val = g_image [x_char][x_row][x_col];
            if (x_val == '#') {
               ++s_trow [x_row];
               ++s_tcol [x_col];
               ++x_filled;
               if (x_col <= 1)  ++s_lef;
               if (x_col >= 3)  ++s_rig;
               if (x_row <= 3)  ++s_top;
               if (x_row >= 5)  ++s_bot;
               if (x_col <= 1 && x_row <= 3)  ++s_quad [0];
               if (x_col >= 3 && x_row <= 3)  ++s_quad [1];
               if (x_col >= 3 && x_row >= 5)  ++s_quad [2];
               if (x_col <= 1 && x_row >= 5)  ++s_quad [3];
            }
         }
      }
      if (g_char >= 32 && !(g_char > 126 && g_char < 160)) {
         if (x_filled == a_match) {
            if (x_save != a_match) {
               printf ("\n");
               x_save = a_match;
            }
            /*> if (abs (s_top - s_bot) <= 1 && abs (s_lef - s_rig) <= 1) {           <*/
               /*> if ((g_char % 5) == 0)  printf ("\n");                                <*/
               printf ("%3d  %-20.20s  %3d   "   , g_char, g_charname [g_char], x_filled);
               /*> for (i = 0; i <  6; ++i)  printf ("%2d ", s_tcol [i]);                   <*/
               printf ("  %2d %2d   ", s_lef, s_rig);
               /*> for (i = 0; i < 10; ++i)  printf ("%2d ", s_trow [i]);                   <*/
               printf ("  %2d %2d   ", s_top, s_bot);
               printf ("  %2d %2d %2d %2d   ", s_quad [0], s_quad [1], s_quad [2], s_quad [3]);
               printf ("\n");
            /*> }                                                                     <*/
         }
      }
      ++g_char;
   }
   return 0;
}

int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   int         i           =    0;
   /*---(file open)----------------------*/
   for (i = 0; i < 60; ++i) {
      rc = INPT_begin ();
      if (rc < 0) return rc;
      /*---(read lines)---------------------*/
      /*> BDF_header ();                                                                 <*/
      while (1) {
         rc = INPT_driver ();
         if (rc < 0)  break;
         ASCII_row (i);
      }
      /*> BDF_footer   ();                                                               <*/
      /*---(file open)----------------------*/
      INPT_end ();
   }
   return 0;
}
