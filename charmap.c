#include    "font.h"



typedef    unsigned char uchar;


#define        NONE      32
/*---(1-way lines)------------*/
#define        LR       204
#define        TB       200
/*---(ends)-------------------*/
#define        TE       152
#define        BE       153
#define        LE       157
#define        RE       156
/*---(arrows)-----------------*/
#define        LA       197
#define        RA       196
#define        TA       199
#define        BA       198
/*---(2-way corners)----------*/
#define        BR       203
#define        BL       154
#define        TL       155
#define        TR       202
/*---(3-way corners)----------*/
#define        TBL      205
#define        TBR      201
#define        TLR      158
#define        BLR      159
/*---(4-way corners)----------*/
#define        TBLR     206



typedef struct cGREEK  tGREEK;
struct cGREEK {
   char        lower;
   char        name        [10];
   char        sound       [ 5];
   char        abbr;
   char        order;
};
tGREEK    s_greek [30] =  {
   { 'è', "alpha"    , "a"   , 'A'  ,  0},
   { 'é', "beta"     , "b"   , 'B'  ,  0},
   { 'ê', "gamma"    , "c"   , 'G'  ,  0},
   { 'ë', "delta"    , "d"   , 'D'  ,  0},
   { 'ì', "epsilon"  , "e"   , 'E'  ,  0},
   { 'í', "zeta"     , "z"   , 'Z'  ,  0},
   { 'î', "eta"      , "e"   , 'H'  ,  0},
   { 'ï', "theta"    , "th"  , 'Q'  ,  0},
   { 'ğ', "iota"     , "i"   , 'I'  ,  0},
   { 'ñ', "kappa"    , "k"   , 'K'  ,  0},
   { 'ò', "lambda"   , "l"   , 'L'  ,  0},
   { 'ó', "mu"       , "m"   , 'M'  ,  0},
   { 'ô', "nu"       , "n"   , 'N'  ,  0},
   { 'õ', "xi"       , "x"   , 'X'  ,  0},
   { 'ö', "omicron"  , "o"   , 'O'  ,  0},
   { '÷', "pi"       , "p"   , 'P'  ,  0},
   { 'ø', "rho"      , "r"   , 'R'  ,  0},
   { 'ù', "sigma"    , "s"   , 'S'  ,  0},
   { 'ú', "tau"      , "t"   , 'T'  ,  0},
   { 'û', "upsilon"  , "u"   , 'U'  ,  0},
   { 'ü', "phi"      , "ph"  , 'F'  ,  0},
   { 'ı', "chi"      , "ch"  , 'C'  ,  0},
   { 'ş', "psi"      , "ps"  , 'Y'  ,  0},
   { 'ÿ', "omega"    , "o"   , 'W'  ,  0},
};

char
hexify               (int a_num)
{
   char        x_hex       =   0;
   if      (a_num >= 0 && a_num <=  9)   x_hex = a_num + '0';
   else if (a_num >  9 && a_num <  16)   x_hex = a_num + 'a' - 10;
   else                                  x_hex = '?';
   return x_hex;
}

int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   int         i, j;
   char        x_hex       =    0;
   int         x_val       =    0;
   int         x_pos       =    0;
   int         x_ch        =    0;
   /*---(titles)-------------------------*/
   printf ("-", x_hex);
   for (i = 0; i < 16; ++i) {
      if ((i % 4) == 0)  printf  ("    ---");
      x_hex = hexify (i);
      printf ("  %c", x_hex);
   }
   printf ("\n");
   /*---(char table)---------------------*/
   for (i = 0; i < 16; ++i) {
      if ((i % 2) == 0)  printf  ("\n");
      x_hex = hexify (i);
      printf ("%c", x_hex);
      for (j = 0; j < 16; ++j) {
         if ((j % 4) == 0)  printf  ("    %03d", (i * 16) + j);
         x_ch = (i * 16) + j;
         if      (x_ch <   32)                 printf ("  %c", '´');
         else if (x_ch >= 127 && x_ch <= 160)  printf ("  %c", '´');
         else                                  printf ("  %c", x_ch);
      }
      printf ("\n");
   }
   printf ("\n");
   /*---(typical similar letters)--------*/
   printf ("0@O£Qïüÿ\n");
   printf ("oïÿöcü\n");
   printf ("1IiLl!|ğ\n");
   printf ("5Ss\n");
   printf ("2Zzí\n");
   printf ("({[]})\n");
   printf ("Illegal1 = O0\n");
   printf ("\n");
   /*---(new brackets)-------------------*/
   printf ("pre¾red¿suf   preºred»suf   pre¸red¹suf   pre¼red½suf\n");
   printf ("xÊ+y=zÊ   èÆ´éÈ=zÉ   pĞq    pÑq    pÒq    pÔq    pÓq\n");
   printf ("315Ì  2.461Í  23'49\"  235Ë  ²ABC   ±XYZ  æCD\n");
   printf ("\n");
   printf ("h = (xÆ + yÆ)Î    and    3.46Ï\n");
   printf ("\n");
   printf ("bezier curves...\n");
   printf ("\n");
   printf ("quad   (n=2) : x(t) = (1-t)ÆxÀ + 2t(1-t)xÁ + tÆxÂ\n");
   printf ("\n");
   printf ("cubic  (n=3) : x(t) = (1-t)ÇxÀ + 3t(1-t)ÆxÁ + 3tÆ(1-t)xÂ + tÇxÃ\n");
   printf ("\n");
   printf ("higher (n=4) : x(t) = (1-t)ÈxÀ + 4t(1-t)ÇxÁ + 6tÆ(1-t)ÆxÂ + 4tÇ(1-t)xÃ + tÈxÄ\n");
   printf ("\n");
   /*---(greek table)--------------------*/
   for (i = 0; i < 12; ++i) {
      x_pos = i;
      printf (" %c   %-2s  %c  %-10.10s     ",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name);
      x_pos = i + 12;
      printf (" %c   %-2s  %c  %-10.10s\n",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name);
   }
   printf ("\n");
   printf ("all greek      : ");
   for (i = 0; i < 24; ++i)  printf ("%c", s_greek [i].lower);
   printf ("\n");
   printf ("\n");
   printf ("critical greek : è é ê ë ì ï ò ÷ ù ú ü ş ÿ\n");
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}
