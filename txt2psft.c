#include    "font.h"



char        s_map       [16][5] = {
   "----",
   "---#",
   "--#-",
   "--##",
   "-#--",
   "-#-#",
   "-##-",
   "-###",
   "#---",
   "#--#",
   "#-#-",
   "#-##",
   "##--",
   "##-#",
   "###-",
   "####",
};



char
PSFT_header          (void)
{
   printf ("%%PSF2\n");
   printf ("Version: 0\n");
   printf ("Flags: 0\n");
   printf ("Length: 256\n");
   printf ("Width: 6\n");
   printf ("Height: 10\n");
   return 0;
}

char
PSFT_footer          (void)
{
   printf ("\n");
   return 0;
}

char
PSFT_row             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   int         j           = 0;
   int         x_val       = 0;
   int         x_byte      = 0;
   float       x_pixel     = 0.0;
   float       x_res       = 0.0;
   float       x_respx     = 0.0;
   int         x_swidth    =   0;
   /*> for (i = 0; i < 16; ++i) {                                                               <* 
    *>    /+> printf ("\n");                                                              <+/   <* 
    *>    printf ("%%\n");                                                                      <* 
    *>    printf ("// Character %d\n"    , g_char);                                             <* 
    *>    printf ("Bitmap: ");                                                                  <* 
    *>    for (j = 0; j < 10; ++j) {                                                            <* 
    *>       x_val = g_char [i].bytes [j];                                                      <* 
    *>       x_byte = x_val / 16;                                                               <* 
    *>       printf ("%s", s_map [x_byte]);                                                     <* 
    *>       x_byte = x_val % 16;                                                               <* 
    *>       printf ("%c%c", s_map [x_byte][0], s_map [x_byte][1]);                             <* 
    *>       if (j < 9) printf (" ");                                                           <* 
    *>    }                                                                                     <* 
    *>    printf ("\n");                                                                        <* 
    *>    /+> printf ("Unicode: [00000000];\n");                                          <+/   <* 
    *>    ++g_char;                                                                             <* 
    *> }                                                                                        <*/
   return 0;
}

int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          = 0;
   /*---(file open)----------------------*/
   /*> rc = INPT_begin ();                                                            <* 
    *> if (rc < 0) return rc;                                                         <* 
    *> /+---(read lines)---------------------+/                                       <* 
    *> PSFT_header ();                                                                <* 
    *> while (1) {                                                                    <* 
    *>    rc = INPT_driver ();                                                        <* 
    *>    if (rc < 0)  break;                                                         <* 
    *>    PSFT_row ();                                                                <* 
    *> }                                                                              <* 
    *> PSFT_footer   ();                                                              <* 
    *> /+---(file open)----------------------+/                                       <* 
    *> INPT_end ();                                                                   <*/
   return 0;
}

