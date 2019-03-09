#include    "font.h"



int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   int         k           =    0;
   char        x_upper     [LEN_LABEL];
   char        t           [LEN_LABEL];
   /*---(read source)--------------------*/
   rc = SHARE_read_all ();
   for (k = 0; k < 3; ++k) {
      printf ("\n\n\n");
      if (k == 0)   printf ("/*---(normal txt2ystr)----------------*/\n");
      if (k == 1)   printf ("/*---(extended txt2ystr)--------------*/\n");
      if (k == 2) {
         strcpy (t, "   ");
         printf ("%s/*--- phoenicia/shrike mapping -------------*/\n", t);
         printf ("%sswitch (x_ch) {\n", t);
      }
      for (i = 0; i < LEN_CHARSET; ++i) {
         /*---(comments)-----------------*/
         if (k > 0)  {
            switch (i) {
            case 0x00:  printf ("%s/*---(notes)---------------------*/\n", t);  break;
            case 0xa3:  printf ("%s/*---(hidden)--------------------*/\n", t);  break;
            case 0xa9:  printf ("%s/*---(macro)---------------------*/\n", t);  break;
            case 0xb0:  printf ("%s/*---(special)-------------------*/\n", t);  break;
            case 0xb5:  printf ("%s/*---(delayed)-------------------*/\n", t);  break;
            case 0xb8:  printf ("%s/*---(grouping)------------------*/\n", t);  break;
            case 0xc0:  printf ("%s/*---(super/sub)-----------------*/\n", t);  break;
            case 0xd0:  printf ("%s/*---(logic)---------------------*/\n", t);  break;
            case 0xe8:  printf ("%s/*---(greek)---------------------*/\n", t);  break;
            }
         }
         /*---(make upper)---------------*/
         strcpy (x_upper, g_char [i].name);
         for (j = 0; j < strlen (x_upper); ++j)  x_upper [j] = toupper (x_upper [j]);
         /*---(keys)---------------------*/
         if (k == 0) {
            if (g_char [i].key == 'y') {
               printf ("#define     G_KEY_%-10.10s    %3d\n", x_upper, i);

            }
         }
         /*---(abbrevs)------------------*/
         /*> printf ("x_len %2d[%s]\n", strlen (x_upper), x_upper);                   <*/
         if (k > 0);
         if (g_char [i].abbr == 0) continue;
         if (i < 160) {
            if (k == 2) printf ("   case '%c'  : x_ch = G_KEY_%-10.10s ;  break;    /*   %3d %c = %3d %c   */\n", g_char [i].abbr, x_upper, g_char [i].abbr, g_char [i].abbr, i, i);
         } else {
            switch (g_char [i].abbr) {
            case '\\' : case '\'' :
               if (k == 1) printf ("#define     G_CHAR_%-10.10s   %3d   /*  %c  */\n", x_upper, i, i);
               if (k == 2) printf ("   case '\\%c' : x_ch = G_CHAR_%-10.10s;  break;    /*   %3d %c = %3d %c   */\n", g_char [i].abbr, x_upper, g_char [i].abbr, g_char [i].abbr, i, i);
               break;
            default :
               if (k == 1) printf ("#define     G_CHAR_%-10.10s   %3d   /*  %c  */\n", x_upper, i, i);
               if (k == 2) printf ("   case '%c'  : x_ch = G_CHAR_%-10.10s;  break;    /*   %3d %c = %3d %c   */\n", g_char [i].abbr, x_upper, g_char [i].abbr, g_char [i].abbr, i, i);
               break;
            }
         }
      }
      /*---(footer)----------------------*/
      if (k == 2)  printf ("   }\n");
      printf ("%s/*---(complete)-----------------------*/\n", t);
      /*---(done)------------------------*/
   }
   return 0;
}
