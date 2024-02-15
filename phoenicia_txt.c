#include    "phoenicia.h"



/*---(file)---------------------------*/
char        g_name      [100]         = "";
FILE       *g_file      = NULL;
char        g_recd      [2000];

tCH         g_char      [MAX_CHARSET];

/*---(glyph)--------------------------*/
static short  s_map      [MAX_LINE];               /* map 16 glyphs into charset pos */
static char   s_print    [LEN_RECD]  = "";



char        g_font       [LEN_LABEL] = "Shrike";  /* font name                */
char        g_pointsz    [LEN_LABEL] = "100";     /* full top-to-bottom       */
char        g_pixelsz    [LEN_LABEL] = "10";      /* full top-to-bottom       */
int         g_tall                   = 10;        /* full top-to-bottom       */
int         g_ascent                 =  8;        /* space between letters    */
int         g_descent                =  2;        /* space between letters    */
int         g_upper                  =  7;        /* capital ascend           */
int         g_lower                  =  5;        /* lower ascend             */
int         g_wide                   =  6;        /* width of characters      */
int         g_space                  =  2;        /* space between letters    */
int         g_next                   =  8;        /* x-dist to next char      */
int         g_prefix                 = 14;        /* left edge to first char  */

int         g_ytall   = 0;
int         g_ywide   = 0;



char
TXT__title              (int a_line, char a_recd [LEN_RECD], char r_title [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_title  != NULL)  strcpy (r_title, "");
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_INPT    yLOG_note    ("not a control record, must start with ¶#@ ¶");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ font_title " , 14) != 0) {
      DEBUG_INPT    yLOG_note    ("not a title record, must identify with ¶#@ font_title ¶");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd + 14, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_INPT    yLOG_info    ("t"         , t);
   x_len = strlen (t);
   /*---(checks)-------------------------*/
   DEBUG_INPT    yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 1) {
      DEBUG_INPT    yLOG_note    ("title is empty");
      yURG_err ('f', "%4d, ¶#@ font_title¶ is empty", a_line);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 29) {
      DEBUG_INPT    yLOG_note    ("title is too long");
      yURG_err ('f', "%4d, ¶#@ font_title¶ length (%d) is too long (1-29)", a_line, x_len);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check only alpha)---------------*/
   --rce;  for (i = 0; i < x_len; ++i) {
      if (strchr (YSTR_ALNUM, t [i]) == NULL) {
         DEBUG_INPT    yLOG_note    ("title contains non-alphanumeric characters");
         yURG_err ('f', "%4d, ¶#@ font_title¶ pos (%d) char (%c) is not allowed [a-zA-Z0-9]", a_line, i, t [i]);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(save·back)----------------------*/
   if (r_title  != NULL)  ystrlcpy (r_title, t, LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TXT__sizing             (int a_line, char a_recd [LEN_RECD], char *r_wide, char *r_tall, char *r_ascent, char *r_descent, char *r_upper, char *r_lower)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   char        c           =    0;
   char        x, y, a, d, u, l;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_wide    != NULL)  *r_wide    = 0;
   if (r_tall    != NULL)  *r_tall    = 0;
   if (r_ascent  != NULL)  *r_ascent  = 0;
   if (r_descent != NULL)  *r_descent = 0;
   if (r_upper   != NULL)  *r_upper   = 0;
   if (r_lower   != NULL)  *r_lower   = 0;
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_INPT    yLOG_note    ("not a control record, must start with ¶#@ ¶");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ font_size ", 13) != 0) {
      DEBUG_INPT    yLOG_note    ("not a sizing record, must identify with ¶#@ font_size ¶");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_INPT    yLOG_info    ("t"         , t);
   /*---(prepare)------------------------*/
   p = strtok_r (t + 13, q, &r);
   while (p != NULL) {
      DEBUG_INPT    yLOG_info    ("p"         , p);
      switch (c) {
      case  0 :  x = atoi (p);  break;
      case  1 :  y = atoi (p);  break;
      case  2 :  a = atoi (p);  break;
      case  3 :  u = atoi (p);  break;
      case  4 :  l = atoi (p);  break;
      }
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(checks)-------------------------*/
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 5) {
      DEBUG_INPT    yLOG_note    ("field count must be 5");
      yURG_err ('f', "%4d, ¶#@ font_size¶ field count (%d) must be 5 [x y a u l]", a_line, c);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x"         , x);
   --rce;  if (x < 5 || x > 20) {
      DEBUG_INPT    yLOG_note    ("wide must be >= 5 and <= 20");
      yURG_err ('f', "%4d, ¶#@ font_size¶ x/wide (%d) out-of-range (5-20)", a_line, x);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("y"         , y);
   --rce;  if (y < 5 || y > 20) {
      DEBUG_INPT    yLOG_note    ("wide must be >= 5 and <= 20");
      yURG_err ('f', "%4d, ¶#@ font_size¶ y/tall (%d) out-of-range (5-20)", a_line, y);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("a"         , a);
   --rce;  if (a >  y || a <= 0) {
      DEBUG_INPT    yLOG_note    ("ascent must be <= y and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ a/ascent (%d) out-of-range (1-%d)", a_line, a, y);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   d = y - a;
   DEBUG_INPT    yLOG_value   ("d"         , d);
   DEBUG_INPT    yLOG_value   ("u"         , u);
   --rce;  if (u >  a || u <= 0) {
      DEBUG_INPT    yLOG_note    ("upper must be <= a and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ u/upper (%d) out-of-range (1-%d)", a_line, u, a);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("l"         , l);
   --rce;  if (l >  a || l <= 0) {
      DEBUG_INPT    yLOG_note    ("lower must be <= a and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ l/lower (%d) out-of-range (1-%d)", a_line, l, a);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save·back)----------------------*/
   if (r_wide    != NULL)  *r_wide    = x;
   if (r_tall    != NULL)  *r_tall    = y;
   if (r_ascent  != NULL)  *r_ascent  = a;
   if (r_descent != NULL)  *r_descent = d;
   if (r_upper   != NULL)  *r_upper   = u;
   if (r_lower   != NULL)  *r_lower   = l;
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*====================------------------------------------====================*/
/*===----                         file level                           ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

char
inpt__begin          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         k           =    0;
   /*---(open)---------------------------*/
   /*> ystrlcpy (g_name, FILE_SHRIKE, 100);                                            <*/
   g_file = fopen (g_name, "r");
   if (g_file == NULL) {
      return -1;
   }
   /*---(initialize g_char)--------------*/
   for (i = 0; i < MAX_CHARSET; ++i) {
      strcpy (g_char [i].name, "");
      g_char [i].abbr = '\0';
      g_char [i].key  = '-';
      for (j = 0; j < LEN_TERSE; ++j) {
         g_char [i].bytes [j] = 0;
         for (k = 0; k < LEN_TERSE; ++k) {
            g_char [i].image [j][k] = '-';
         }
      }
      for (j = 0; j < g_ytall; ++j) {
         for (k = 0; k < g_ywide; ++k) {
            g_char [i].yfont  [j][k] =  0;
            g_char [i].pretty [j][k] = ' ';
         }
      }
   }
   /*---(initialize map)-----------------*/
   for (i = 0; i < 16; ++i) {
      s_map [i] = 0;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
share_shrike         (void)
{
   strcpy  (g_name, FILE_SHRIKE);
   sprintf (g_font, "%s", "Shrike");
   g_tall      = 10;
   g_ytall     = 57;
   sprintf (g_pointsz , "%d", g_tall * 10);
   sprintf (g_pixelsz , "%d", g_tall);
   g_ascent    =  8;
   g_descent   =  2;
   g_upper     =  7;
   g_lower     =  5;
   g_wide      =  6;
   g_ywide     = 34;
   g_space     =  2;
   g_next      = g_wide + g_space;
   g_prefix    = 14;
   return 0;
}

char
share_square         (void)
{
   strcpy  (g_name, FILE_SQUARE);
   sprintf (g_font, "%s", "Square");
   g_tall      =  9;
   sprintf (g_pointsz , "%d", g_tall * 10);
   sprintf (g_pixelsz , "%d", g_tall);
   g_ascent    =  8;
   g_descent   =  1;
   g_upper     =  7;
   g_lower     =  5;
   g_wide      =  9;
   g_space     =  2;
   g_next      = g_wide + g_space;
   g_prefix    = 14;
   return 0;
}

char
inpt__end            (void)
{
   fclose (g_file);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       row handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLERS________________o (void) {;}

char
TXT__hex                (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short r_map [MAX_LINE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i, j;
   int         l           =    0;
   char        x_bad       =  '-';
   int         x_max       =    0;
   char        t           [LEN_DESC];
   char        s           [LEN_TERSE];
   char        x_hex       [LEN_TERSE];
   double      x_map       =  0.0;
   int         x_off       =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   DEBUG_INPT    yLOG_complex ("a_args"    , "%2dp, %2dw, %2dn", a_prefix, a_wide, a_next);
   /*---(default)------------------------*/
   if (r_map != NULL) { for (i = 0; i < MAX_LINE; ++i)  r_map [i] = -1;  }
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "hex", 3) != 0) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_recd);
   DEBUG_INPT    yLOG_value   ("l"         , l);
   x_max = a_prefix + (MAX_LINE * (a_next - 1)) - 1;
   DEBUG_INPT    yLOG_value   ("x_max"     , x_max);
   --rce;  if (x_max > l) {
      yURG_err ('f', "%4d, ¶hex¶ line does not have enough space (%d) vs expected (%d)", a_line, l, x_max);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd + 3, YSTR_EMPTY, a_prefix - 3) != 0) {
      yURG_err ('f', "%4d, ¶hex¶ line has non-whitespace (%*.*s) in prefix area (first %d chars)", a_line, a_prefix, a_prefix, a_recd, a_prefix);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk the line)------------------*/
   for (i = 0; i < MAX_LINE; ++i) {
      x_map = -1;
      x_off = a_prefix + i * (a_next - 1);
      DEBUG_INPT    yLOG_value   ("x_off"     , x_off);
      ystrlcpy  (t, a_recd + x_off, a_next);
      if (t [0] == 'x')  t [0] = 'õ';
      DEBUG_INPT    yLOG_info    ("t"         , t);
      x_bad = 'y';
      if      (t [0] == 'õ')                        { x_bad = '-'; l = 3; }
      else if (strchr (YSTR_HEXUP, t [0]) != NULL)  { x_bad = '-'; l = 2; }
      DEBUG_INPT    yLOG_char    ("x_bad"     , x_bad);
      if (x_bad == 'y') {
         yURG_err ('f', "%4d, ¶hex¶ entry %d (%s) does not start with [õ0-9a-fA-F]", a_line, i, t);
         continue;
      }
      if ((l == 2 && t [1] == ' ') || (l == 3 && t [2] == ' ')) {
         yURG_err ('f', "%4d, ¶hex¶ entry %d (%s) hex code can not be a single digit", a_line, i, t);
         continue;
      }
      DEBUG_INPT    yLOG_value   ("l"         , l);
      for (j = l; j < a_next - 1; ++j) {
         DEBUG_INPT    yLOG_char    ("t [j]"     , t [j]);
         if (t [j] == 0 || strchr ("· ", t [j]) == NULL) {
            yURG_err ('f', "%4d, ¶hex¶ entry %d (%s) contains garbage in whitespace, pos %d (%c)", a_line, i, t, j, t [j]);
            x_bad = 'y';
            continue;
         }
      }
      if (x_bad == 'y')  continue;
      ystrlcpy  (s, t, l + 1);
      DEBUG_INPT    yLOG_info    ("s"         , s);
      if (s [0] != 'õ')  sprintf   (x_hex, "õ%s", s);
      else               strcpy    (x_hex, s);
      DEBUG_INPT    yLOG_info    ("x_hex"     , x_hex);
      rc = ystrl2hex  (x_hex, &x_map, LEN_TERSE);
      DEBUG_INPT    yLOG_value   ("ystrl2hex" , rc);
      if (rc < 0) {
         yURG_err ('f', "%4d, ¶hex¶ entry %d (%s) not a translatable hex code [õ0-9a-fA-F]", a_line, i, t);
         continue;
      }
      if (x_map == 0 && strcmp (x_hex, "õ00") != 0) {
         yURG_err ('f', "%4d, ¶hex¶ entry %d (%s) translated as 0, but is not 00 or õ00", a_line, i, t);
         continue;
      }
      DEBUG_INPT    yLOG_value   ("x_map"     , (int) x_map);
      ++c;
      if (r_map != NULL)  r_map [i] = x_map;
   }
   /*---(check trouble)------------------*/
   yURG_msg ('-', "%4d, ¶hex¶ line, processed %c fields correctly", a_line, c);
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 16) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
TXT__map_show           (short a_map [MAX_LINE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (s_print, "");
   for (i = 0; i < MAX_LINE; ++i) {
      if (a_map [i] < 0)  strcpy  (t, "?   ");
      else                sprintf (t, "%-3d ", a_map [i]);
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return s_print;
}

char
TXT__name               (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, tCH b_char [MAX_CHARSET])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i, j;
   int         l           =    0;
   char        x_bad       =  '-';
   int         x_max       =    0;
   char        t           [LEN_DESC];
   char        s           [LEN_TERSE];
   char        x_hex       [LEN_TERSE];
   double      x_map       =  0.0;
   int         x_off       =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   DEBUG_INPT    yLOG_complex ("a_args"    , "%2dp, %2dw, %2dn", a_prefix, a_wide, a_next);
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "1 " , 2) != 0) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_recd);
   DEBUG_INPT    yLOG_value   ("l"         , l);
   x_max = a_prefix + (MAX_LINE * (a_next - 1)) - 1;
   DEBUG_INPT    yLOG_value   ("x_max"     , x_max);
   --rce;  if (x_max > l) {
      yURG_err ('f', "%4d, ¶#¶ line does not have enough space (%d) vs expected (%d)", a_line, l, x_max);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd + 1, YSTR_EMPTY, a_prefix - 1) != 0) {
      yURG_err ('f', "%4d, ¶#¶ line has non-whitespace (%*.*s) in prefix area (first %d chars)", a_line, a_prefix, a_prefix, a_recd, a_prefix);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk the line)------------------*/
   /*> for (i = 0; i < MAX_LINE; ++i) {                                                                                         <* 
    *>    x_map = -1;                                                                                                           <* 
    *>    x_off = a_prefix + i * (a_next - 1);                                                                                  <* 
    *>    DEBUG_INPT    yLOG_value   ("x_off"     , x_off);                                                                     <* 
    *>    ystrlcpy  (t, a_recd + x_off, a_next);                                                                                <* 
    *>    if (t [0] == 'x')  t [0] = 'õ';                                                                                       <* 
    *>    DEBUG_INPT    yLOG_info    ("t"         , t);                                                                         <* 
    *>    x_bad = 'y';                                                                                                          <* 
    *>    if      (t [0] == 'õ')                        { x_bad = '-'; l = 3; }                                                 <* 
    *>    else if (strchr (YSTR_HEXUP, t [0]) != NULL)  { x_bad = '-'; l = 2; }                                                 <* 
    *>    DEBUG_INPT    yLOG_char    ("x_bad"     , x_bad);                                                                     <* 
    *>    if (x_bad == 'y') {                                                                                                   <* 
    *>       yURG_err ('f', "%4d, ¶#¶ entry %d (%s) does not start with [õ0-9a-fA-F]", a_line, i, t);                           <* 
    *>       continue;                                                                                                          <* 
    *>    }                                                                                                                     <* 
    *>    if ((l == 2 && t [1] == ' ') || (l == 3 && t [2] == ' ')) {                                                           <* 
    *>       yURG_err ('f', "%4d, ¶#¶ entry %d (%s) hex code can not be a single digit", a_line, i, t);                         <* 
    *>       continue;                                                                                                          <* 
    *>    }                                                                                                                     <* 
    *>    DEBUG_INPT    yLOG_value   ("l"         , l);                                                                         <* 
    *>    for (j = l; j < a_next - 1; ++j) {                                                                                    <* 
    *>       DEBUG_INPT    yLOG_char    ("t [j]"     , t [j]);                                                                  <* 
    *>       if (t [j] == 0 || strchr ("· ", t [j]) == NULL) {                                                                  <* 
    *>          yURG_err ('f', "%4d, ¶#¶ entry %d (%s) contains garbage in whitespace, pos %d (%c)", a_line, i, t, j, t [j]);   <* 
    *>          x_bad = 'y';                                                                                                    <* 
    *>          continue;                                                                                                       <* 
    *>       }                                                                                                                  <* 
    *>    }                                                                                                                     <* 
    *>    if (x_bad == 'y')  continue;                                                                                          <* 
    *>    ystrlcpy  (s, t, l + 1);                                                                                              <* 
    *>    DEBUG_INPT    yLOG_info    ("s"         , s);                                                                         <* 
    *>    if (s [0] != 'õ')  sprintf   (x_hex, "õ%s", s);                                                                       <* 
    *>    else               strcpy    (x_hex, s);                                                                              <* 
    *>    DEBUG_INPT    yLOG_info    ("x_hex"     , x_hex);                                                                     <* 
    *>    rc = ystrl2hex  (x_hex, &x_map, LEN_TERSE);                                                                           <* 
    *>    DEBUG_INPT    yLOG_value   ("ystrl2hex" , rc);                                                                        <* 
    *>    if (rc < 0) {                                                                                                         <* 
    *>       yURG_err ('f', "%4d, ¶#¶ entry %d (%s) not a translatable hex code [õ0-9a-fA-F]", a_line, i, t);                   <* 
    *>       continue;                                                                                                          <* 
    *>    }                                                                                                                     <* 
    *>    if (x_map == 0 && strcmp (x_hex, "õ00") != 0) {                                                                       <* 
    *>       yURG_err ('f', "%4d, ¶#¶ entry %d (%s) translated as 0, but is not 00 or õ00", a_line, i, t);                      <* 
    *>       continue;                                                                                                          <* 
    *>    }                                                                                                                     <* 
    *>    DEBUG_INPT    yLOG_value   ("x_map"     , (int) x_map);                                                               <* 
    *>    ++c;                                                                                                                  <* 
    *>    if (r_map != NULL)  r_map [i] = x_map;                                                                                <* 
    *> }                                                                                                                        <*/
   /*---(check trouble)------------------*/
   yURG_msg ('-', "%4d, ¶#¶ line, processed %c fields correctly", a_line, c);
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 16) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
inpt__names          (int a_offset)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        x_name      [30];
   int         n           = 0;
   /*---(walk names)---------------------*/
   for (i = 0; i < 16; i += 2) {
      /*---(get name)--------------------*/
      ystrlcpy  (x_name, g_recd + g_prefix + (i + a_offset) * g_next, 16);
      ystrltrim (x_name, ySTR_BOTH, 2000);
      /*---(store it)--------------------*/
      n = s_map [i + a_offset];
      if (strcmp ("-", x_name) == 0)  sprintf (x_name, "char%d", n);
      /*> printf ("%-2d  [%s]\n", i + a_offset, x_name);                              <*/
      ystrlcpy  (g_char [n].name, x_name, 16);
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__abbr           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         n           =    0;
   uchar       x_short     =    0;
   /*> printf ("%s\n", g_recd);                                                       <*/
   for (i = 0; i < 16; ++i) {
      n = s_map [i];
      x_short = g_recd [g_prefix + (i * g_next)];
      /*> printf ("%c ", x_short);                                                    <*/
      switch (x_short) {
      case 172  : g_char [n].abbr = '\0';     break;
      default   : g_char [n].abbr = x_short;  break;
      }
      /*> if (g_char [n].abbr > 0)  printf ("%c ", g_char [n].abbr);                  <*/
      /*> else                      printf ("  ");                                    <*/
      x_short = g_recd [g_prefix + (i * g_next) + 2];
      if (x_short == (uchar) '´')  g_char [n].key = 'y';
      /*> printf ("%c ", x_short);                                                    <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__char           (int a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         x_val       =    0;
   int         x_byte      =    0;
   int         n           =    0;
   int         x_max       = g_wide - 1;
   /*> printf ("   -- bytes         ");                                               <*/
   for (i = 0; i < 16; ++i) {
      n = s_map [i];
      x_byte = 0;
      for (j = x_max; j >= 0; --j) {
         if (j == 0)  x_val = 1;
         else         x_val = pow (2, j);
         g_char [n].image [a_row][x_max - j] =  ' ';
         if (g_recd [g_prefix + (i * g_next) + (x_max - j)] == '#') {
            x_byte += x_val;
            g_char [n].image [a_row][x_max - j] = '#';
         }
      }
      g_char [n].bytes [a_row] = x_byte;
      /*> printf ("%-3d/%-1d:%-4d ", n, a_row, g_char [n].bytes [a_row]);             <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
inpt__glyph          (int a_block, int a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         n           =    0;
   uchar       x_ch        =  ' ';
   char       *x_valid     = "-+:*172%98#@";
   char       *p           = NULL;
   uchar       v           =    0;
   float       x_inc       =    0;
   uchar       x_val       =    0;
   /*> printf ("   -- bytes        :  ");                                             <*/
   x_inc = 255 / 13;
   for (i = 0; i < 16; ++i) {
      n = a_block * 16 + i;
      for (j = 0; j < g_ywide; ++j) {
         /*---(get char)-----------------*/
         x_ch  = g_recd [4 + i * g_ywide + j];
         /*> printf ("%c", x_ch);                                                     <*/
         /*---(defaults)-----------------*/
         g_char [n].yfont  [a_row][j] =  0;
         g_char [n].pretty [a_row][j] = x_ch;
         /*---(check char)---------------*/
         p  = strchr ("-+:*172%98#@", x_ch);
         if (p == NULL)  continue;
         /*---(replace)------------------*/
         v = p - x_valid + 1;
         x_val = v * x_inc;
         g_char [n].yfont  [a_row][j] = x_val;
         /*---(done)---------------------*/
      }
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       main driver                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
TXT__read               (FILE *f, int *b_line, int *r_len, char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         x_len       =    0;
   char        t           [LEN_HUND]  = "";
   uchar       c           =  '·';
   char        x_valid     =  '-';
   char        x_new       =  '-';
   int         x_line      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   if (b_line != NULL)  x_line = *b_line;
   if (r_len  != NULL)  *r_len   = 0;
   if (r_recd != NULL)  strcpy (r_recd, "");
   /*---(open·file)----------------------*/
   DEBUG_INPT    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read·for·next)------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, f);
      if (feof (f))  {
         DEBUG_INPT    yLOG_note    ("end of file reached");
         break;
      }
      ++x_line;
      x_len = strlen (x_recd);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      ystrlcpy (t, x_recd, LEN_HUND);
      DEBUG_INPT    yLOG_complex ("line"      , "%4d %4då%sæ", x_line, x_len, t);
      /*---(filter)----------------------*/
      c = x_recd [0];
      if      (strncmp (x_recd, "hex       ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found hex identifiers");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "1         ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found odd-numbered character names");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "2         ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found even-numbered character names");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "short     ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found shorthand character names");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "c  "       ,  3) == 0) {
         DEBUG_INPT    yLOG_note    ("found character pixel data");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "#@ "       ,  3) == 0) {
         DEBUG_INPT    yLOG_note    ("found control record");
         x_valid = 'y';
      }
      if (x_valid != 'y')  continue;
      /*---(accept)----------------------*/
      if (b_line != NULL)  *b_line = x_line;
      if (r_len  != NULL)  *r_len  = x_len;
      if (r_recd != NULL)  ystrlcpy (r_recd, x_recd, LEN_RECD);
      rc = 1;
      break;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (b_line != NULL)  *b_line = x_line;
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return rc;
}

char
TXT_get_all             (char a_audit, cchar a_txtfile [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         x_len       =    0;
   int         i, j;
   int         x_line      =    0;
   int         x_row       =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(start)--------------------------*/
   if      (a_audit == 'y')  yURG_msg ('>', "conducting font file (txt) audit...");
   else                      yURG_msg ('>', "gather file file (txt) data...");
   /*---(file open)----------------------*/
   yURG_msg ('-', "font file å%sæ", a_txtfile);
   rc = FILE_open (a_txtfile, 'r', NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "file could not be openned (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "font file openned successfully");
   rc = inpt__begin ();
   --rce;  if (rc < 0) return rce;
   /*---(read file)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (g_recd, 2000, g_file);
      if (feof (g_file)) return -1;
      ++x_line;
      /*---(fix)-------------------------*/
      x_len = strlen (g_recd);
      if (x_len <= 0)  continue;
      g_recd [--x_len] = '\0';
      /*> printf ("%-2d : [%s]\n", x_row, g_recd);                                    <*/
      /*---(handle)----------------------*/
      switch (g_recd [0]) {
      case '#' : case ' ' : case '\n' : case '\0'  :
         break;
      case 'h' :
         /*> inpt__hex  ();                                                           <*/
         x_row = 0;
         break;
      case '1' :
         /*> printf ("found inpt__names (0);\n");                                     <*/
         inpt__names (0);
         break;
      case '2' :
         /*> printf ("found inpt__names (1);\n");                                     <*/
         inpt__names (1);
         break;
      case 's' :
         inpt__abbr  ();
         break;
      case 'c' :
         if (x_row <  0)  break;
         inpt__char (x_row);
         ++x_row;
         if (x_row >= g_tall)   x_row = -1;
         break;
      default  :
         break;
      }
      /*> /+---(display)---------------------+/                                       <* 
       *> for (j = 0; j < 10; ++j) {                                                  <* 
       *>    printf ("%2d :");                                                        <* 
       *>    for (i = 0; i < 16; ++i) {                                               <* 
       *>       printf ("  %-4d", g_char [i].bytes [j]);                              <* 
       *>    }                                                                        <* 
       *>    printf ("\n");                                                           <* 
       *> }                                                                           <*/
      /*---(done)------------------------*/
   }
   /*---(file close)---------------------*/
   rc = inpt__end ();
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                                        <* 
 *> SHARE_read_yfont      (void)                                                                <* 
 *> {  /+---(design notes)-------------------+/                                                 <* 
 *>    /+                                                                                       <* 
 *>     *  init happens in SHARE_read_all, and this is second pass at file                      <* 
 *>     *                                                                                       <* 
 *>     +/                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    char        rce         =  -10;                                                          <* 
 *>    char        rc          =    0;                                                          <* 
 *>    int         x_len       =    0;                                                          <* 
 *>    int         i, j;                                                                        <* 
 *>    int         x_line      =    0;                                                          <* 
 *>    int         x_row       =    0;                                                          <* 
 *>    int         x_block     =    0;                                                          <* 
 *>    /+---(file open)----------------------+/                                                 <* 
 *>    g_file = fopen (g_name, "r");                                                            <* 
 *>    if (g_file == NULL) {                                                                    <* 
 *>       return -1;                                                                            <* 
 *>    }                                                                                        <* 
 *>    /+---(read file)----------------------+/                                                 <* 
 *>    while (1) {                                                                              <* 
 *>       /+---(read)------------------------+/                                                 <* 
 *>       fgets (g_recd, 2000, g_file);                                                         <* 
 *>       if (feof (g_file)) return -1;                                                         <* 
 *>       ++x_line;                                                                             <* 
 *>       /+---(fix)-------------------------+/                                                 <* 
 *>       x_len = strlen (g_recd);                                                              <* 
 *>       if (x_len <= 0)  continue;                                                            <* 
 *>       g_recd [--x_len] = '\0';                                                              <* 
 *>       /+> printf ("%-2d : [%s]\n", x_row, g_recd);                                    <+/   <* 
 *>       /+---(handle)----------------------+/                                                 <* 
 *>       switch (g_recd [0]) {                                                                 <* 
 *>       case 'y' :                                                                            <* 
 *>          if (x_row <  0)  break;                                                            <* 
 *>          inpt__glyph (x_block, x_row);                                                      <* 
 *>          ++x_row;                                                                           <* 
 *>          if (x_row >= g_ytall) {                                                            <* 
 *>             x_row = 0;                                                                      <* 
 *>             ++x_block;                                                                      <* 
 *>          }                                                                                  <* 
 *>          break;                                                                             <* 
 *>       default  :                                                                            <* 
 *>          break;                                                                             <* 
 *>       }                                                                                     <* 
 *>       /+> /+---(display)---------------------+/                                       <*    <* 
 *>        *> for (j = 0; j < 10; ++j) {                                                  <*    <* 
 *>        *>    printf ("%2d :");                                                        <*    <* 
 *>        *>    for (i = 0; i < 16; ++i) {                                               <*    <* 
 *>        *>       printf ("  %-4d", g_char [i].bytes [j]);                              <*    <* 
 *>        *>    }                                                                        <*    <* 
 *>        *>    printf ("\n");                                                           <*    <* 
 *>        *> }                                                                           <+/   <* 
 *>       /+---(done)------------------------+/                                                 <* 
 *>    }                                                                                        <* 
 *>    /+---(file close)---------------------+/                                                 <* 
 *>    fclose (g_file);                                                                         <* 
 *>    /+---(complete)-----------------------+/                                                 <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/
