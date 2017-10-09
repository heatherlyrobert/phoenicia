#include    "font.h"

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

#define        WIDE       8
#define        TALL       6
char        s_wide [TALL][WIDE] = {
   { NONE, NONE, NONE, NONE , NONE, NONE, NONE, NONE},
   { NONE, NONE, BR  , LA   , RA  , BL  , NONE, NONE},
   { NONE, BR  , TBLR, LA   , RA  , TBLR, BL  , NONE},
   { NONE, TB  , TR  , LA   , RA  , TL  , TB  , NONE},
   { LR  , TBLR, LR  , LA   , RA  , LR  , TBLR, LR  },
   { NONE, TR  , LR  , LA   , RA  , LR  , TL  , NONE},
   { NONE, NONE, NONE, NONE , NONE, NONE, NONE, NONE},
};

char        s_tall [WIDE][TALL] = {
   { NONE, NONE, NONE, TB  , NONE, NONE },
   { NONE, BR  , LR  , TBLR, BL  , NONE },
   { BR  , TBLR, BL  , TB  , TB  , NONE },
   { TA  , TA  , TA  , TA  , TA  , NONE },
   { BA  , BA  , BA  , BA  , BA  , NONE },
   { TR  , TBLR, TL  , TB  , TB  , NONE },
   { NONE, TR  , LR  , TBLR, TL  , NONE },
   { NONE, NONE, NONE, TB  , NONE, NONE },
};

typedef struct cGREEK  tGREEK;
struct cGREEK {
   char        upper;
   char        lower;
   char        name        [10];
   char        sound       [ 5];
   char        abbr;
   char        order;
};
tGREEK    s_greek [30] =  {
   { 'Ğ', 'è', "alpha"    , "a"   , 'A'  ,  0},
   { 'Ñ', 'é', "beta"     , "b"   , 'B'  ,  0},
   { 'Ò', 'ê', "gamma"    , "c"   , 'G'  ,  0},
   { 'Ó', 'ë', "delta"    , "d"   , 'D'  ,  0},
   { 'Ô', 'ì', "epsilon"  , "e"   , 'E'  ,  0},
   { 'Õ', 'í', "zeta"     , "z"   , 'Z'  ,  0},
   { 'Ö', 'î', "eta"      , "e"   , 'H'  ,  0},
   { '×', 'ï', "theta"    , "th"  , 'Y'  ,  0},
   { 'Ø', 'ğ', "iota"     , "i"   , 'I'  ,  0},
   { 'Ù', 'ñ', "kappa"    , "k"   , 'K'  ,  0},
   { 'Ú', 'ò', "lambda"   , "l"   , 'L'  ,  0},
   { 'Û', 'ó', "mu"       , "m"   , 'M'  ,  0},
   { 'Ü', 'ô', "nu"       , "n"   , 'N'  ,  0},
   { 'İ', 'õ', "xi"       , "x"   , 'X'  ,  0},
   { 'Ş', 'ö', "omicron"  , "o"   , 'O'  ,  0},
   { 'ß', '÷', "pi"       , "p"   , 'P'  ,  0},
   { 'à', 'ø', "rho"      , "r"   , 'R'  ,  0},
   { 'á', 'ù', "sigma"    , "s"   , 'S'  ,  0},
   { 'â', 'ú', "tau"      , "t"   , 'T'  ,  0},
   { 'ã', 'û', "upsilon"  , "u"   , 'U'  ,  0},
   { 'ä', 'ü', "phi"      , "ph"  , 'F'  ,  0},
   { 'å', 'ı', "chi"      , "ch"  , 'C'  ,  0},
   { 'æ', 'ş', "psi"      , "ps"  , 'Q'  ,  0},
   { 'ç', 'ÿ', "omega"    , "o"   , 'W'  ,  0},
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
main (void)
{
   int i, j;
   char        x_hex       =    0;
   int         x_val       =    0;
   srand (0);
   printf ("-", x_hex);
   for (i = 0; i < 16; ++i) {
      if ((i % 4) == 0)  printf  ("    ---");
      x_hex = hexify (i);
      printf ("  %c", x_hex);
   }
   printf ("\n");
   for (i = 0; i < 16; ++i) {
      if ((i % 2) == 0)  printf  ("\n");
      x_hex = hexify (i);
      printf ("%c", x_hex);
      for (j = 0; j < 16; ++j) {
         if ((j % 4) == 0)  printf  ("    %03d", (i * 16) + j);
         if      ((i * 16) + j  <  32)  printf ("  %c", 189);
         else if ((i * 16) + j == 127)  printf ("  %c", 189);
         else printf ("  %c", (i * 16) + j);
      }
      printf ("\n");
   }
   printf ("\n");
   printf ("0%c%c%c%c%c%c\n", 64, 79, 188, 215, 222, 231);
   printf ("o%c%c%c%c\n", 99, 101, 239, 246);
   printf ("1IiLl|¦%c\n", 240);
   printf ("E%c%c\n", 212, 225);
   printf ("5Ss\n");
   printf ("2Z%cz\n", 213);
   printf ("({[]})\n");
   printf ("Illegal1 = O0\n");
   printf ("\n");
   printf ("\n");
   for (i = 0; i < 16; ++i) {
      printf ("  ");
      for (j = 0; j < 16; ++j) {
         x_val = rand () % 16;
         printf ("%c", 128 + x_val);
         x_val = rand () %  8;
         printf ("%c ", 144 + x_val);
      }
      printf ("\n");
   }
   printf ("\n");
   for (i = 0; i < 8; ++i)   printf ("  %c", 152 + i);
   for (i = 0; i < 7; ++i)   printf ("  %c", 200 + i);
   for (i = 0; i < 8; ++i)   printf ("  %c", 192 + i);
   printf ("\n");
   for (i = 0; i < TALL; ++i) {
      for (j = 0; j < WIDE; ++j) {
         printf ("%c", s_wide [i][j]);
      }
      printf ("\n");
   }
   for (i = 0; i < WIDE; ++i) {
      for (j = 0; j < TALL; ++j) {
         printf ("%c", s_tall [i][j]);
      }
      printf ("\n");
   }
   printf ("\n");
   printf ("è é ê ë ï ò ÷ ù ú ü ş ÿ\n");
   printf ("\n");
   for (i = 0; i < 24; ++i) {
      printf (" %c %c   %-2s  %c  %s\n",
            s_greek [i].upper, s_greek [i].lower,
            s_greek [i].sound, s_greek [i].abbr ,
            s_greek [i].name);
   }
   return 0;
}
