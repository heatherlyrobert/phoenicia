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
   char        tsae        [ 5];
};
tGREEK    s_greek [30] =  {
   { 'è', "alpha"    , "a"   , 'A'  , "-" },
   { 'é', "beta"     , "b"   , 'B'  , "-" },
   { 'ê', "gamma"    , "c"   , 'G'  , "g" },
   { 'ë', "delta"    , "d"   , 'D'  , "d" },
   { 'ì', "epsilon"  , "e"   , 'E'  , "ts"},
   { 'í', "zeta"     , "z"   , 'Z'  , "-" },
   { 'î', "eta"      , "e"   , 'H'  , "h" },
   { 'ï', "theta"    , "th"  , 'Y'  , "-" },
   { 'ð', "iota"     , "i"   , 'I'  , "-" },
   { 'ñ', "kappa"    , "k"   , 'K'  , "k" },
   { 'ò', "lambda"   , "l"   , 'L'  , "hl"},
   { 'ó', "mu"       , "m"   , 'M'  , "m" },
   { 'ô', "nu"       , "n"   , 'N'  , "n" },
   { 'õ', "xi"       , "x"   , 'X'  , "hy"},
   { 'ö', "omicron"  , "o"   , 'O'  , "-" },
   { '÷', "pi"       , "p"   , 'P'  , "-" },
   { 'ø', "rho"      , "r"   , 'R'  , "pn"},
   { 'ù', "sigma"    , "s"   , 'S'  , "s" },
   { 'ú', "tau"      , "t"   , 'T'  , "t" },
   { 'û', "upsilon"  , "u"   , 'U'  , "-" },
   { 'ü', "phi"      , "ph"  , 'F'  , "-" },
   { 'ý', "chi"      , "ch"  , 'C'  , "c" },
   { 'þ', "psi"      , "ps"  , 'Q'  , "qu"},
   { 'ÿ', "omega"    , "o"   , 'W'  , "w" },
};


char   s_rows  [16][20] = {
   "ctrl" , "ctrl",
   "punc" , "nums",
   "upper", "upper",
   "lower", "lower",
   "ctrl" , "ctrl",
   "macro", "group",
   "math" , "logic",
   "greek", "greek",
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
   int         x_pos       =    0;
   int         x_ch        =    0;
   /*------------------------------ abcdefghijklmnopqrstuvwxyz"  */
   /*---(titles)-------------------------*/
   printf ("#!/usr/local/bin/charmap\n");
   printf ("#   %s\n", P_ONELINE);
   /*> printf ("#   %s : %s\n", P_VERNUM, P_VERTXT);                                  <*/
   printf ("\n");
   printf ("       -");
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
      if (a_argc > 1 && i >= 8 && i <= 9)  printf ("%5s  ", "tsae");
      else                                 printf ("%5s  ", s_rows [i]);
      printf ("%c", x_hex);
      for (j = 0; j < 16; ++j) {
         if ((j % 4) == 0)  printf  ("    %03d", (i * 16) + j);
         x_ch = (i * 16) + j;
         if      (x_ch <   32)                               printf ("  %c", '´');
         else if (a_argc < 2 && x_ch >= 127 && x_ch <= 160)  printf ("  %c", '´');
         else                                                printf ("  %c", x_ch);
      }
      printf ("\n");
   }
   printf ("\n");
   /*---(typical similar letters)--------*/
   printf (" pÐq  µ&  and      TT -- -- --     pØq  µ_r  unlikely       pàq  µ_u  uniques\n");
   printf (" pÔq  µk  nand/con -- TF FT FF     pÙq  µ_l  likely         páq  µ_x  there exists\n");
   printf (" pÑq  µ|  or       TT TF FT --     ê=Ú  µ_i  infinity       pâq  µ_h  subset of\n");
   printf (" pÒq  µv  xor      -- TF FT --     Ûx(  µ_f  function       päq  µ_m  member of\n");
   printf (" pÕq  µj  nor      -- -- -- FF     p´q  µ'   product        påq  µ=   equivalent\n");
   printf (" pÓq  µi  iff/nxor TT -- -- FF     pçq  µu   functor        æp(  µ_a  for each ...\n");
   printf (" pÖq  µl  if/prove TT -- FT FF     pãq  µo   set math       p×q  µh   contributes back\n");
   printf ("\n");
   /*---(new brackets)-------------------*/
   printf ("315Ì  2.461Í  23'49\"  235Ë    ´··+··+··´··+··+··´    =·$g$5²*²g3²+²d7²+²c2²+²$c$4\n");
   printf (" µ0 £  nul    µa 3Ì deg    µr 9Í rad    µ# 4Ë lbs    µ  ² fil    µ! ¡   µ? ¢   µ$ ±\n");
   printf ("\n");
   printf ("macros  ºls<¦··ls<¦··ls<¦··ls<¦··:0a1¦»\n");
   printf (" µe ¥ esc     µn ¦ ret     µf § fld     µg ¨ grp     µ* ¬ msk    µp ¤ plc\n");
   printf (" µq ³ hlt     µ+ © dsp     µ. ª pau     µs · pad     µ' ´ 1key   µ@ Ï 5key   µ, « 0.5s\n");
   printf (" µ: ® sum     µ%% ¯ sys     µ¶ ¶ dqt     µµ µ dbs     µ-  fld   º···» blitz\n");
   printf ("\n");
   printf ("bezier (n=2) : x(t) = (1-t)ÆxÀ + 2t(1-t)xÁ + tÆxÂ\n");
   printf ("cubic  (n=3) : x(t) = (1-t)ÇxÀ + 3t(1-t)ÆxÁ + 3tÆ(1-t)xÂ + tÇxÃ\n");
   printf ("quad   (n=4) : x(t) = (1-t)ÈxÀ + 4t(1-t)ÇxÁ + 6tÆ(1-t)ÆxÂ + 4tÇ(1-t)xÃ + tÈxÄ\n");
   printf (" µ1 xÎ  µ2 xÆ  µ3 xÇ  µ4 xÈ  µx xÉ  µy xÊ  µ5 xÀ  µ6 xÁ  µ7 xÂ  µ8 xÃ  µ9 xÄ  µz xÅ\n");
   printf ("\n");
   printf ("yREGEX  ¸red|white¹   ºnåm»   (&float)   ºnÞm»   ºn[aeiou]»   ¼[abcde]{3,5}½\n");
   printf (" µ[ º   µ] »   µ( ¸   µ) ¹   µ{ ¼   µ} ½   µd ¾   µb ¿   µ< Ü   µ> Ý   µ/ Þ   µ~ ß\n");
   printf ("\n");
   /*---(greek table)--------------------*/
   for (i = 0; i < 12; ++i) {
      /*> if (i == 6)  printf ("\n");                                                 <*/
      x_pos = i;
      printf ("        %c   %-2s  µ%c  %-7.7s  (%-2s)        ",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name , s_greek [x_pos].tsae);
      x_pos = i + 12;
      printf (" %c   %-2s  µ%c  %-7.7s  (%-2s)        ",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name , s_greek [x_pos].tsae);
      switch (i) {
      case 2  :  printf ("Ç  a");    break;
      case 3  :  printf ("Æ  e");    break;
      case 4  :  printf ("È  f");    break;
      case 5  :  printf ("É  i");    break;
      case 6  :  printf ("Ê  o");    break;
      case 7  :  printf ("Ì  u");    break;
      case 8  :  printf ("Í  v");    break;
      case 9  :  printf ("·  '");    break;
      }
      printf ("\n");
   }
   printf ("\n");
   for (i = 0; i < 24; ++i)  printf ("%c ", s_greek [i].lower);
   printf ("    ");
   for (i = 0; i < 24; ++i)  printf ("%c" , s_greek [i].lower);
   printf ("\n");
   printf ("\n");
   printf ("   sihyo'wina ùÉõÊ·ÿÉôÇ   kama ñÇóÇ   zetu'nvgf ìÆúÌ·ôÍêÈ   pna'quatse øÇ·þÇìÆ\n");
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper [Ï´···\n");
   /*---(complete)-----------------------*/
   return 0;
}


