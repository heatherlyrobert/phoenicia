#include    "font.h"



char        g_name      [100]         = "";
FILE       *g_file      = NULL;
char        g_recd      [2000];
int         g_bytes     [16][10];
int         g_char      =    0;
char        g_charname  [256][30];
int         g_line      =    0;
int         g_row       =    0;


char
INPT_begin           (void)
{
   strlcpy (g_name, "shrike.txt", 100);
   g_file = fopen (g_name, "r");
   if (g_file == NULL) {
      return -1;
   }
   return 0;
}

char
INPT_end             (void)
{
   fclose (g_file);
   return 0;
}

char
INPT_names           (int a_offset)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        x_name      [30];
   int         x_byte      = 0;
   /*> printf ("   -- bytes        :  ");                                             <*/
   for (i = 0; i < 16; i += 2) {
      strlcpy  (x_name, g_recd + 14 + (i + a_offset) * 8, 16);
      strltrim (x_name, ySTR_BOTH, 2000);
      if (strcmp ("-", x_name) == 0)  sprintf (x_name, "char%d", g_char + i + a_offset);
      strlcpy  (g_charname [g_char + i + a_offset], x_name, 16);
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
INPT_row             (int a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   int         j           = 0;
   int         x_val       = 0;
   int         x_byte      = 0;
   /*> printf ("   -- bytes        :  ");                                             <*/
   for (i = 0; i < 16; ++i) {
      x_byte = 0;
      for (j = 7; j >= 0; --j) {
         x_val = pow (2, j);
         if (g_recd [14 + (i * 8) + (7 - j)] == '#') x_byte += x_val;
      }
      g_bytes [i][a_row] = x_byte;
      /*> printf ("%-7d ", g_bytes [i][a_row]);                                       <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

int
INPT_driver          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       = 0;
   /*---(file open)----------------------*/
   while (1) {
      fgets (g_recd, 2000, g_file);
      if (feof (g_file)) {
         return -1;
      }
      ++g_line;
      if (g_recd [0] == '\n' || g_recd [0] == '\0' || g_recd [0] == ' ') {
         continue;
      }
      if (g_recd [0] == '#') {
         continue;
      }
      x_len = strlen (g_recd);
      g_recd [--x_len] = '\0';
      if (g_recd [0] == '1') {
         INPT_names (0);
         continue;
      }
      if (g_recd [0] == '2') {
         INPT_names (1);
         continue;
      }
      if (g_recd [0] != 'c') {
         continue;
      }
      INPT_row   (g_row);
      ++g_row;
      if (g_row >= 10) {
         g_row = 0;
         break;
      }
   }
   return 0;
}
