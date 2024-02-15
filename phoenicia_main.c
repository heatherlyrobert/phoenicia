#include    "phoenicia.h"




char
phoenicia_check      (void)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                           <* 
    *> int         x           = 0;                                                                       <* 
    *> int         y           = 0;                                                                       <* 
    *> char       *x_hex       = "0123456789ABCDEF";                                                      <* 
    *> int         v           = 0;                                                                       <* 
    *> int         x_byte      = 0;                                                                       <* 
    *> int         t, m, b, l, c, r;                                                                      <* 
    *> int         a, n;                                                                                  <* 
    *> float       p, q;                                                                                  <* 
    *> for (x = 0; x < MAX_CHARSET; ++x) {                                                                <* 
    *>    printf ("STARTCHAR %s\n"   , g_char [x].name);                                                  <* 
    *>    t = m = b = l = c = r = 0;                                                                      <* 
    *>    p = q = 0.0;                                                                                    <* 
    *>    n = 0;                                                                                          <* 
    *>    for (y = 0; y < g_tall; ++y) {                                                                  <* 
    *>       a = 0;                                                                                       <* 
    *>       v = g_char [x].bytes [y];                                                                    <* 
    *>       printf ("%-3d   ", v);                                                                       <* 
    *>       if (v / 128 == 1) { printf (".");  ++l; ++a;  p += -2;  q += y - 4.5; } else printf ("·");   <* 
    *>       v %= 128;                                                                                    <* 
    *>       if (v /  64 == 1) { printf (".");  ++l; ++a;  p += -2;  q += y - 4.5; } else printf ("·");   <* 
    *>       v %=  64;                                                                                    <* 
    *>       if (v /  32 == 1) { printf (".");  ++c; ++a;  p +=  0;  q += y - 4.5; } else printf ("·");   <* 
    *>       v %=  32;                                                                                    <* 
    *>       if (v /  16 == 1) { printf (".");  ++r; ++a;  p +=  1;  q += y - 4.5; } else printf ("·");   <* 
    *>       v %=  16;                                                                                    <* 
    *>       if (v /   8 == 1) { printf (".");  ++r; ++a;  p +=  2;  q += y - 4.5; } else printf ("·");   <* 
    *>       v %=   8;                                                                                    <* 
    *>       if (v /   4 == 1) { printf (".");       ++a;                          } else printf ("·");   <* 
    *>       printf ("\n");                                                                               <* 
    *>       n += a;                                                                                      <* 
    *>       switch (y) {                                                                                 <* 
    *>       case 0 : case 1 : case 2 : case 3 :   t += a;  break;                                        <* 
    *>       case 4 : case 5 :                     m += a;  break;                                        <* 
    *>       case 6 : case 7 : case 8 : case 9 :   b += a;  break;                                        <* 
    *>       }                                                                                            <* 
    *>    }                                                                                               <* 
    *>    printf ("%2dl  %2dc  %2dr     %5.1f   %2d   %5.1f\n", l, c, r, p, n, p / n);                    <* 
    *>    printf ("%2dt  %2dm  %2db     %5.1f   %2d   %5.1f\n", t, m, b, q, n, q / n);                    <* 
    *>    printf ("\n");                                                                                  <* 
    *> }                                                                                                  <* 
    *> return 0;                                                                                          <*/
}


int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(read source)--------------------*/
   /*> share_shrike ();                                                               <* 
    *> rc = SHARE_read_all ();                                                        <*/
   /*---(write out)----------------------*/
   /*> phoenicia_check ();                                                            <*/
   /*---(complete)-----------------------*/
   return 0;
}
