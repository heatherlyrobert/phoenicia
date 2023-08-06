#include    "font.h"



int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   int         k           =    0;
   /*---(read source)--------------------*/
   rc = SHARE_read_all ();
   printf ("\"\"please replace in .vimrc\n");
   printf ("\"\"phoenicia/shrike imaps------------------\n");
   for (i = 0; i < LEN_CHARSET; ++i) {
      switch (i) {
      case 0x00:  printf ("\"\"---(editing)-------------------\n");  break;
      case 0xa3:  printf ("\"\"---(hidden)--------------------\n");  break;
      case 0xa9:  printf ("\"\"---(macro)---------------------\n");  break;
      case 0xb0:  printf ("\"\"---(special)-------------------\n");  break;
      case 0xb5:  printf ("\"\"---(delayed)-------------------\n");  break;
      case 0xb8:  printf ("\"\"---(grouping)------------------\n");  break;
      case 0xc0:  printf ("\"\"---(super/sub)-----------------\n");  break;
      case 0xd0:  printf ("\"\"---(logic)---------------------\n");  break;
      case 0xe8:  printf ("\"\"---(greek)---------------------\n");  break;
      }
      if (g_char [i].abbr == 0) continue;
      switch (g_char [i].abbr) {
      case '|' :
         printf ("imap <Leader>\\%c %c\n", g_char [i].abbr, i);
         break;
      case ' ' :
         printf ("imap <Leader><space> %c\n", i);
         break;
      default :
         printf ("imap <Leader>%c %c\n", g_char [i].abbr, i);
         break;
      }
   }
   printf ("\"\"complete--------------------------------\n");
   return 0;
}
