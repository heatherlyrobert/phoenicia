#include    "font.h"



char        s_map       [16][5] = {
   "----",
   "---X",
   "--X-",
   "--XX",
   "-X--",
   "-X-X",
   "-XX-",
   "-XXX",
   "X---",
   "X--X",
   "X-X-",
   "X-XX",
   "XX--",
   "XX-X",
   "XXX-",
   "XXXX",
};

char
conv_row             (void)
{
   int         i           =    0;
   char        x_ch        =  '-';
   int         x_val       =    0;
   for (i = 0; i < 2; ++i) {
      x_ch   = g_recd [i];
      if      (x_ch >= '0' && x_ch <= '9')  x_val = x_ch - '0';
      else if (x_ch >= 'A' && x_ch <= 'F')  x_val = x_ch - 'A' + 10;
      else                                  x_val = 0;
      printf ("%s", s_map [x_val]);
   }
   printf ("\n");
   return 0;
}

int
main                 (int a_argc, char *a_argv[])
{
   char        x_conv      =  '-';
   int         x_line      =    0;
   int         x_len       =    0;
   g_file = fopen (g_name, "r");
   if (g_file == NULL) {
      return -1;
   }
   while (1) {
      fgets (g_recd, 2000, g_file);
      if (feof (g_file)) {
         /*> printf ("   -- end of file\n");                                          <*/
         break;
      }
      ++x_line;
      if (strchr ("\0\n# ", g_recd [0]) != NULL) {
         /*> printf ("   -- blank line\n");                                           <*/
         continue;
      }
      if (g_recd [0] == '#') {
         /*> printf ("   -- comment line\n");                                         <*/
         continue;
      }
      /*> printf ("   LINE %3d\n", x_line);                                           <*/
      x_len = strlen (g_recd);
      g_recd [--x_len] = '\0';
      /*> printf ("   len  %d\n" , x_len);                                            <*/
      /*> printf ("   recd %s\n" , g_recd);                                           <*/
      if (strncmp ("BITMAP", g_recd, 6) == 0) {
         x_conv = 'y';
         /*> printf ("   -- something else\n");                                       <*/
         continue;
      }
      if (strncmp ("ENDCHAR", g_recd, 7) == 0) {
         x_conv = '-';
         /*> printf ("   -- something else\n");                                       <*/
         continue;
      }
      if (x_conv != 'y') {
         printf ("%s\n", g_recd);
         continue;
      }
      conv_row ();
   }
   fclose (g_file);
   return 0;
}
