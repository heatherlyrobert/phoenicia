#include    "phoenicia.h" 


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
   "draw" , "draw",
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

char
charmap_main         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i, j;
   char        x_hex       =    0;
   int         x_pos       =    0;
   int         x_ch        =    0;
   /*------------------------------ abcdefghijklmnopqrstuvwxyz"  */
   /*---(titles)-------------------------*/
   printf ("#!/usr/local/bin/phoenicia --charmap                          (bash alias == charmap)\n");
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
      printf ("%5s  ", s_rows [i]);
      printf ("%c", x_hex);
      for (j = 0; j < 16; ++j) {
         if ((j % 4) == 0)  printf  ("    %03d", (i * 16) + j);
         x_ch = (i * 16) + j;
         if      (x_ch <   32)                 printf ("  %c", '´');
         else if (x_ch == 127)                 printf ("  %c", '´');
         else                                  printf ("  %c", x_ch);
      }
      printf ("\n");
   }
   printf ("\n");
   /*---(typical similar letters)--------*/
   printf (" pÐq  µ&  and       TT -- -- --    pÚq  Úq  µ_c  negate/false       çq  µ_o  local   \n");
   printf (" pÔq  µk  nand/con  -- TF FT FF    pØq  Øq  µ_u  unlikely         p q  µ_e  empty   \n");
   printf (" pÑq  µ|  or        TT TF FT --    pÙq  Ùq  µ_l  likely         d p©q  µ_d  diamond \n");
   printf (" pÕq  µj  nor       -- -- -- FF    pÛq  Ûq  µ_t  forces/true    e p`q       halflong\n");
   printf (" pÒq  µv  xor       -- TF FT --    pàq      µ_q  equivalent     f pq  µ_b  dslash  \n");
   printf (" pÓq  µi  iff/nxor  TT -- -- FF    páq      µ_x  point            p±q  µ_s  suffix\n");
   printf (" pÖq  µl  if/prove  TT -- FT FF    pâq      µ_h  subset of         äp() µ_a  for each\n");
   printf (" p×q  µh  contributes              pãq      µ_m  member of         °°°  µ_!  redacted\n");
   printf ("\n");
   /*---(new brackets)-------------------*/
   printf ("315Ì  2.461Í  23'49\"  235Ë   ´··´··+··´   ´··´··Ï   =·$g$5²*²g3²+²d7²+²c2²+²$c$4\n");
   printf (" µ0 £  nul    µo 3Ì deg    µr 9Í rad    µ# 4Ë5 sci   µ  ² fil    µ! ¡   µ? ¢   µ$ \n");
   printf ("\n");
   printf ("macros  ºls<¦··ls<¦··ls<¦··ls<¦··:0a1¦»              µ_[ å       µ_] æ      µ_r \n");
   printf (" µe ¥ esc     µn ¦ ret     µf § fld     µg ¨ grp     µ* ¬ msk    µp ¤ plc   \n");
   printf (" µq ³ hlt     µ+ ­ dsp     µ. ª pau     µs · pad     µ' ´ 1key   µ@ Ï 5key   µ, « 1key\n");
   printf (" µ: ® sum     µ%% ¯ sys     µ¶ ¶ dqt     µµ µ dbs     µ-  fld     º···» blitz\n");
   printf ("\n");
   printf ("bezier (n=2) : x(t) = (1-t)ÆxÀ + 2t(1-t)xÁ + tÆxÂ     µ_i  inf   µ_f  x()    ` exp\n");
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
      printf ("    %c  %-2s µ%c  %-7.7s %-2s   ",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name , s_greek [x_pos].tsae);
      x_pos = i + 12;
      printf ("    %c  %-2s µ%c  %-7.7s %-2s     ",
            s_greek [x_pos].lower,
            s_greek [x_pos].sound, s_greek [x_pos].abbr ,
            s_greek [x_pos].name , s_greek [x_pos].tsae);
      switch (i) {
      case 0  :  printf ("            ");    break;
      case 1  :  printf ("                   ");    break;
      case 2  :  printf ("              aÇ");    break;
      case 3  :  printf ("                 eÆ");    break;
      case 4  :  printf (" ²²         fÈ");    break;
      case 5  :  printf ("                   iÉ");    break;
      case 6  :  printf ("            oÊ");    break;
      case 7  :  printf ("              uÌ");    break;
      case 8  :  printf ("              vÍ");    break;
      case 9  :  printf ("           '·");    break;
      case 10 :  printf ("                ");    break;
      case 11 :  printf ("                ");    break;
      }
      printf ("\n");
   }
   printf ("                                                                         \n");
   for (i = 0; i < 24; ++i)  printf ("%c ", s_greek [i].lower);
   printf ("    ");
   for (i = 0; i < 24; ++i)  printf ("%c" , s_greek [i].lower);
   printf ("\n");
   printf ("\n");
   /*> printf ("   sihyo'wina ùÉõÊ·ÿÉôÇ   kama ñÇóÇ   zetu'nvgf ìÆúÌ·ôÍêÈ   pna'quatse øÇ·þÇìÆ\n");   <*/
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper [Ï´···\n");
   printf ("\n");
   printf ("\n");
   printf ("base alphabet letter form notes...\n");
   printf ("   -- i needed maximum clarity in letters, even if strange looking\n");
   printf ("   -- ? and ! were given strong dots to make clear\n");
   printf ("   -- i and j were given strong dots to keep i distinct from l and 1\n");
   printf ("   -- l was made distinct to keep away from 1 and |\n");
   printf ("   -- t was made distinct (carolingian) help with l\n");
   printf ("   -- 0 and £ where kept different from O\n");
   printf ("   -- many greek letters have less common shapes to keep unique\n");
   printf ("\n");
   printf ("line drawing (11 core, 6 doors/waves, 4 ends, 4 mayan teeth, and extra dotted)\n");
   printf ("                           µ_2                                         \n");
   printf ("            µ_H     µ_1      µ_3      µ_D  µ_T       µ_M   µ_N   \n");
   printf ("                                                                     \n");
   printf ("            µ_V     µ_4      µ_6  µ_S ²     ² µ_E  µ_W   µ_X   \n");
   printf ("                                      µ_L         µ_R                \n");
   printf ("            µ_0     µ_7      µ_9                   µ_Y   µ_Z   \n");
   printf ("                           µ_8            µ_U  µ_B                     \n");
   printf ("\n");
   printf ("     Õ\n");
   printf ("                      \n");
   printf ("                       \n");
   printf ("                       \n");
   printf ("                       \n");
   printf ("                               \n");
   printf ("                        \n");
   printf ("                          \n");
   printf ("                  \n");
   printf ("                             \n");
   printf ("                        \n");
   printf ("                         \n");
   printf ("                  \n");
   printf ("                          \n");
   printf ("                       \n");
   printf ("                           \n");
   printf ("                          \n");
   printf ("                        \n");
   printf ("                       \n");
   printf ("                             \n");
   printf ("                       \n");
   printf ("                      \n");
   printf ("                   \n");
   printf ("                    \n");
   printf ("                    \n");
   printf ("                    \n");
   printf ("                      \n");
   printf ("                 \n");
   printf ("                     \n");
   printf ("                        \n");
   printf ("                   \n");
   printf ("                         \n");
   printf ("                     \n");
   printf ("                       \n");
   printf ("                   \n");
   printf ("     Õ-\n");
   printf ("\n");
   printf ("\n");
   printf ("   ²²²²²²²²   ²²²²²   ²²²²²²\n");
   printf ("     é                          î                             \n");
   printf ("                                                          \n");
   printf ("                è         è         é       è            ì  \n");
   printf ("                            ì                            \n");
   printf ("     í                                   \n");
   printf ("      01                                           02  \n");
   printf ("                              03                               \n");
   printf ("     ê                                                         \n");
   printf ("                \n");
   printf ("                                                         \n");
   printf ("     ë       ì     î         ë        ê        é   ê          ë  \n");
   printf ("                                                                 \n");
   printf ("         \n");
   printf ("\n");
   printf ("              \n");
   printf ("                          \n");
   printf ("                               \n");
   printf ("                              \n");
   printf ("                      \n");
   printf ("             \n");
   printf ("               \n");
   printf ("                          \n");
   printf ("          []               \n");
   printf ("                      \n");
   printf ("                         \n");
   printf ("               \n");
   printf ("             \n");
   printf ("                       \n");
   printf ("                     \n");
   printf ("                     \n");
   printf ("                    \n");
   printf ("           ´  \n");
   printf ("       ·  \n");
   printf ("            \n");
   printf ("               \n");
   printf ("                    \n");
   printf ("                  \n");
   printf ("       ·  \n");
   printf ("                   \n");
   printf ("                      \n");
   printf ("                      \n");
   printf ("                      \n");
   printf ("                      \n");
   printf ("                   \n");
   printf ("          \n");
   printf ("                   \n");
   printf ("       []                \n");
   printf ("                     \n");
   printf ("                     \n");
   printf ("          \n");
   printf ("\n");
   printf ("\n");
   printf ("                             yang           ²  yin\n");
   printf ("\n");
   printf ("                                             sky                    \n");
   printf ("             lake  ²    wind    \n");
   printf ("     |                                \n");
   printf ("      |                      ²          \n");
   printf ("     |                     l  s  w ²          \n");
   printf ("       |              fire  ² f     r   river   \n");
   printf ("   --------                  t  e  m ²          \n");
   printf ("   Ï                    ² ²           \n");
   printf ("                   ² ² ²          \n");
   printf ("                        thunder   ² ²  mountain\n");
   printf ("                                   earth                   \n");
   printf ("       \n           ");
   printf ("\n");
   printf ("      initiating      responding      completion      transition \n");
   printf ("         ²²    ²²    \n");
   printf ("         ²²        ²²\n");
   printf ("         ²²    ²²    \n");
   printf ("         ²²        ²²\n");
   printf ("         ²²    ²²    \n");
   printf ("         ²²        ²²\n");
   printf ("          01              02              63              64     \n");
   printf ("\n");
   printf ("\n");
   printf ("                 \n");
   printf ("        36  22     11  26      49  13     55  30 \n");
   printf ("                 \n");
   printf ("  c     15  52     46  18      31  33     62  56 \n");
   printf ("  o          \n");
   printf ("  r                                                      \n");
   printf ("  e          \n");
   printf ("        05  09     40  54      44  28     34  14 \n");
   printf ("  o              \n");
   printf ("  f     48  57  38      43  32  50 \n");
   printf ("           63  01    \n");
   printf ("  t    ²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n");
   printf ("  h        02  64    \n");
   printf ("  e     19  41  24      53  17  25 \n");
   printf ("                 \n");
   printf ("  c     07  04     27  23      37  39     45  12 \n");
   printf ("  o          \n");
   printf ("  r                                                      \n");
   printf ("  e          \n");
   printf ("        60  61     03  42      58  10     51  21 \n");
   printf ("                 \n");
   printf ("        29  59     08  20      47  06     16  35 \n");
   printf ("                 \n");
   printf ("\n");
   printf ("\n");
   printf ("\n");
   printf ("\n");
   printf ("\n");
   printf ("\n");
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper [Ï´···\n");
   /*---(complete)-----------------------*/
   return 0;
}


