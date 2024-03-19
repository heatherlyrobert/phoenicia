#include    "phoenicia.h"



/*---(file)---------------------------*/
/*> char        g_name      [100]         = "";                                       <*/
/*> FILE       *g_file      = NULL;                                                   <*/
/*> char        g_recd      [2000];                                                   <*/

tCH         g_char      [MAX_CHARSET];

/*---(glyph)--------------------------*/
static char   s_print    [LEN_RECD]  = "";



/*> char        g_font       [LEN_LABEL] = "Shrike";  /+ font name                +/   <*/
/*> char        g_pointsz    [LEN_LABEL] = "100";     /+ full top-to-bottom       +/   <*/
/*> char        g_pixelsz    [LEN_LABEL] = "10";      /+ full top-to-bottom       +/   <*/


char        g_title      [LEN_DESC]  = "";        /* font name                */

int         g_wide                   =  0;        /* width of characters      */
int         g_tall                   =  0;        /* full top-to-bottom       */

int         g_ascent                 =  0;        /* space between letters    */
int         g_descent                =  0;        /* space between letters    */

int         g_upper                  =  0;        /* capital ascend           */
int         g_lower                  =  0;        /* lower ascend             */

int         g_prefix                 =  0;        /* left edge to first char  */
int         g_gap                    =  0;        /* space between letters    */
int         g_next                   =  0;        /* x-dist to next char      */

int         g_cen                    =  0;        /* left-right center        */
int         g_mid                    =  0;        /* top-bottom middle        */

int         g_ytall   = 0;
int         g_ywide   = 0;



char
TXT__clear              (uchar n)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x, y;
   /*---(source)-------------------------*/
   g_char [n].hexline  = -1;
   g_char [n].hexcol   = -1;
   /*---(basics)-------------------------*/
   strcpy (g_char [n].name   , "");
   for (y = 0; y < LEN_LABEL; ++y) {
      for (x = 0; x < LEN_LABEL; ++x) {
         g_char [n].image [y][x] = '\0';
      }
   }
   g_char [n].bytes [y] = -1;
   g_char [n].abbr      = -1;
   /*---(symmetry)-----------------------*/
   g_char [n].pixels    = 0;
   for (y = 0; y < LEN_LABEL; ++y) {
      g_char [n].verts [y] = 0;
      g_char [n].horzs [y] = 0;
      g_char [n].diags [y] = 0;
   }
   g_char [n].vert      = 0.0;
   g_char [n].horz      = 0.0;
   g_char [n].diag      = 0.0;
   /*---(working)------------------------*/
   g_char [n].key       = '-';
   g_char [n].ready     = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
TXT_purge               (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_CHARSET; ++i) {
      TXT__clear (i);
   }
   return 0;
}

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
   /*---(message)------------------------*/
   yURG_msg ('-', "processed title å%sæ", t);
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TXT__sizing             (int a_line, char a_recd [LEN_RECD], char *r_wide, char *r_tall, char *r_ascent, char *r_descent, char *r_upper, char *r_lower, char *r_prefix, char *r_gap, char *r_next, char *r_center, char *r_middle)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   char        c           =    0;
   char        x_wid, x_tal, x_asc, x_des, x_upr, x_low, x_pre, x_gap, x_nxt, x_cen, x_mid;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_wide    != NULL)  *r_wide    = 0;
   if (r_tall    != NULL)  *r_tall    = 0;
   if (r_ascent  != NULL)  *r_ascent  = 0;
   if (r_descent != NULL)  *r_descent = 0;
   if (r_upper   != NULL)  *r_upper   = 0;
   if (r_lower   != NULL)  *r_lower   = 0;
   if (r_prefix  != NULL)  *r_prefix  = 0;
   if (r_gap     != NULL)  *r_gap     = 0;
   if (r_next    != NULL)  *r_next    = 0;
   if (r_center  != NULL)  *r_center  = 0;
   if (r_middle  != NULL)  *r_middle  = 0;
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
      case  0 :  x_wid = atoi (p);  break;
      case  1 :  x_tal = atoi (p);  break;
      case  2 :  x_asc = atoi (p);  break;
      case  3 :  x_upr = atoi (p);  break;
      case  4 :  x_low = atoi (p);  break;
      case  5 :  x_pre = atoi (p);  break;
      case  6 :  x_gap = atoi (p);  break;
      case  7 :  x_cen = atoi (p);  break;
      case  8 :  x_mid = atoi (p);  break;
      }
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(checks)-------------------------*/
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 9) {
      DEBUG_INPT    yLOG_note    ("field count must be 9");
      yURG_err ('f', "%4d, ¶#@ font_size¶ field count (%d) must be 9 [x y a u l p g c m]", a_line, c);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_wid"     , x_wid);
   --rce;  if (x_wid < 5 || x_wid > 20) {
      DEBUG_INPT    yLOG_note    ("wide must be >= 5 and <= 20");
      yURG_err ('f', "%4d, ¶#@ font_size¶ x/wide (%d) out-of-range (5-20)", a_line, x_wid);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_tal"     , x_tal);
   --rce;  if (x_tal < 5 || x_tal > 20) {
      DEBUG_INPT    yLOG_note    ("tall must be >= 5 and <= 20");
      yURG_err ('f', "%4d, ¶#@ font_size¶ y/tall (%d) out-of-range (5-20)", a_line, x_tal);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_asc"     , x_asc);
   --rce;  if (x_asc >  x_tal || x_asc <= 0) {
      DEBUG_INPT    yLOG_note    ("ascent must be <= y and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ a/ascent (%d) out-of-range (1-%d)", a_line, x_asc, x_tal);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_des = x_tal - x_asc;
   DEBUG_INPT    yLOG_value   ("x_des"     , x_des);
   DEBUG_INPT    yLOG_value   ("x_upr"     , x_upr);
   --rce;  if (x_upr >  x_asc || x_upr <= 0) {
      DEBUG_INPT    yLOG_note    ("upper must be <= a and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ u/upper (%d) out-of-range (1-%d)", a_line, x_upr, x_asc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_low"         , x_low);
   --rce;  if (x_low >  x_asc || x_low <= 0) {
      DEBUG_INPT    yLOG_note    ("lower must be <= a and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ l/lower (%d) out-of-range (1-%d)", a_line, x_low, x_asc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_pre"     , x_pre);
   --rce;  if (x_pre > 20 || x_pre <= 5) {
      DEBUG_INPT    yLOG_note    ("prefix must be >= 5 and <= 20");
      yURG_err ('f', "%4d, ¶#@ font_size¶ p/prefix (%d) out-of-range (5-20)", a_line, x_pre);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_gap"     , x_gap);
   --rce;  if (x_gap >  5 || x_gap <= 0) {
      DEBUG_INPT    yLOG_note    ("gap must be <= 5 and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ g/gap (%d) out-of-range (1-5)", a_line, x_gap);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_nxt = x_wid + x_gap + 1;
   DEBUG_INPT    yLOG_value   ("x_nxt"     , x_nxt);
   DEBUG_INPT    yLOG_value   ("x_cen"     , x_cen);
   --rce;  if (x_cen >= x_tal || x_cen <= 0) {
      DEBUG_INPT    yLOG_note    ("center must be < tall and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ c/center (%d) out-of-range (> 0 && < tall)", a_line, x_cen);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("x_mid"     , x_mid);
   --rce;  if (x_mid >= x_tal || x_mid <= 0) {
      DEBUG_INPT    yLOG_note    ("middle must be < wide and > 0");
      yURG_err ('f', "%4d, ¶#@ font_size¶ m/middle (%d) out-of-range (> 0 && < wide)", a_line, x_mid);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save·back)----------------------*/
   if (r_wide    != NULL)  *r_wide    = x_wid;
   if (r_tall    != NULL)  *r_tall    = x_tal;
   if (r_ascent  != NULL)  *r_ascent  = x_asc;
   if (r_descent != NULL)  *r_descent = x_des;
   if (r_upper   != NULL)  *r_upper   = x_upr;
   if (r_lower   != NULL)  *r_lower   = x_low;
   if (r_prefix  != NULL)  *r_prefix  = x_pre;
   if (r_gap     != NULL)  *r_gap     = x_gap;
   if (r_next    != NULL)  *r_next    = x_nxt;
   if (r_center  != NULL)  *r_center  = x_cen;
   if (r_middle  != NULL)  *r_middle  = x_mid;
   /*---(message)------------------------*/
   yURG_msg ('-', "processed sizing %dw, %dt, %da, %dd, %du, %dl, %dp, %dg, %dn, %dc, %dm", x_wid, x_tal, x_asc, x_des, x_upr, x_low, x_pre, x_gap, x_nxt, x_cen, x_mid);
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         file level                           ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

/*> char                                                                                         <* 
 *> inpt__begin          (void)                                                                  <* 
 *> {                                                                                            <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                  <* 
 *>    int         i           =    0;                                                           <* 
 *>    int         j           =    0;                                                           <* 
 *>    int         k           =    0;                                                           <* 
 *>    /+---(open)---------------------------+/                                                  <* 
 *>    /+> ystrlcpy (g_name, FILE_SHRIKE, 100);                                            <+/   <* 
 *>    g_file = fopen (g_name, "r");                                                             <* 
 *>    if (g_file == NULL) {                                                                     <* 
 *>       return -1;                                                                             <* 
 *>    }                                                                                         <* 
 *>    /+---(initialize g_char)--------------+/                                                  <* 
 *>    for (i = 0; i < MAX_CHARSET; ++i) {                                                       <* 
 *>       strcpy (g_char [i].name, "");                                                          <* 
 *>       g_char [i].abbr = '\0';                                                                <* 
 *>       g_char [i].key  = '-';                                                                 <* 
 *>       for (j = 0; j < LEN_TERSE; ++j) {                                                      <* 
 *>          g_char [i].bytes [j] = 0;                                                           <* 
 *>          for (k = 0; k < LEN_TERSE; ++k) {                                                   <* 
 *>             g_char [i].image [j][k] = '-';                                                   <* 
 *>          }                                                                                   <* 
 *>       }                                                                                      <* 
 *>       for (j = 0; j < g_ytall; ++j) {                                                        <* 
 *>          for (k = 0; k < g_ywide; ++k) {                                                     <* 
 *>             g_char [i].yfont  [j][k] =  0;                                                   <* 
 *>             g_char [i].pretty [j][k] = ' ';                                                  <* 
 *>          }                                                                                   <* 
 *>       }                                                                                      <* 
 *>    }                                                                                         <* 
 *>    /+---(initialize map)-----------------+/                                                  <* 
 *>    for (i = 0; i < 16; ++i) {                                                                <* 
 *>       s_map [i] = 0;                                                                         <* 
 *>    }                                                                                         <* 
 *>    /+---(complete)-----------------------+/                                                  <* 
 *>    return 0;                                                                                 <* 
 *> }                                                                                            <*/

/*> char                                                                              <* 
 *> share_shrike         (void)                                                       <* 
 *> {                                                                                 <* 
 *>    strcpy  (g_name, FILE_SHRIKE);                                                 <* 
 *>    sprintf (g_font, "%s", "Shrike");                                              <* 
 *>    g_tall      = 10;                                                              <* 
 *>    g_ytall     = 57;                                                              <* 
 *>    sprintf (g_pointsz , "%d", g_tall * 10);                                       <* 
 *>    sprintf (g_pixelsz , "%d", g_tall);                                            <* 
 *>    g_ascent    =  8;                                                              <* 
 *>    g_descent   =  2;                                                              <* 
 *>    g_upper     =  7;                                                              <* 
 *>    g_lower     =  5;                                                              <* 
 *>    g_wide      =  6;                                                              <* 
 *>    g_ywide     = 34;                                                              <* 
 *>    g_space     =  2;                                                              <* 
 *>    g_next      = g_wide + g_space;                                                <* 
 *>    g_prefix    = 14;                                                              <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> share_square         (void)                                                       <* 
 *> {                                                                                 <* 
 *>    strcpy  (g_name, FILE_SQUARE);                                                 <* 
 *>    sprintf (g_font, "%s", "Square");                                              <* 
 *>    g_tall      =  9;                                                              <* 
 *>    sprintf (g_pointsz , "%d", g_tall * 10);                                       <* 
 *>    sprintf (g_pixelsz , "%d", g_tall);                                            <* 
 *>    g_ascent    =  8;                                                              <* 
 *>    g_descent   =  1;                                                              <* 
 *>    g_upper     =  7;                                                              <* 
 *>    g_lower     =  5;                                                              <* 
 *>    g_wide      =  9;                                                              <* 
 *>    g_space     =  2;                                                              <* 
 *>    g_next      = g_wide + g_space;                                                <* 
 *>    g_prefix    = 14;                                                              <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> inpt__end            (void)                                                       <* 
 *> {                                                                                 <* 
 *>    fclose (g_file);                                                               <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



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
      DEBUG_INPT    yLOG_note    ("do not recognize record type");
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
      /*---(prepare)---------------------*/
      x_map = -1;
      x_off = a_prefix + i * (a_next - 1);
      DEBUG_INPT    yLOG_value   ("x_off"     , x_off);
      ystrlcpy  (t, a_recd + x_off, a_next);
      if (t [0] == 'x')  t [0] = 'õ';
      DEBUG_INPT    yLOG_info    ("t"         , t);
      x_bad = 'y';
      /*---(size)------------------------*/
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
      /*---(check extra chars)-----------*/
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
      /*---(verify hex)------------------*/
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
      /*---(save back)-------------------*/
      DEBUG_INPT    yLOG_value   ("x_map"     , (int) x_map);
      ++c;
      if (r_map != NULL)  r_map [i] = x_map;
      g_char [(int) x_map].hexline = a_line;
      g_char [(int) x_map].hexcol  = i;
      /*---(done)------------------------*/
   }
   /*---(check trouble)------------------*/
   yURG_msg ('-', "%4d, ¶hex¶ line, processed %d fields correctly", a_line, c);
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
TXT__name               (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short a_map [MAX_LINE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i, j;
   int         l           =    0;
   char        x_bad       =  '-';
   int         x_max       =    0;
   char        x_name      [LEN_TERSE] = "";
   char        t           [LEN_DESC];
   int         x_skip      =    0;
   int         x_off       =    0;
   char        c           =    0;
   short       n           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   DEBUG_INPT    yLOG_complex ("a_args"    , "%2dp, %2dw, %2dn", a_prefix, a_wide, a_next);
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map  == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;
   if      (strncmp (a_recd, "odds" , 4) == 0)   x_skip = 0;
   else if (strncmp (a_recd, "even" , 4) == 0)   x_skip = 1;
   else {
      DEBUG_INPT    yLOG_note    ("do not recognize record type");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (x_name, a_recd, 5);
   l = strlen (a_recd);
   DEBUG_INPT    yLOG_value   ("l"         , l);
   x_max = a_prefix + (MAX_LINE * (a_next - 1)) - 1;
   DEBUG_INPT    yLOG_value   ("x_max"     , x_max);
   --rce;  if (x_max > l) {
      yURG_err ('f', "%4d, ¶%s¶ line does not have enough space (%d) vs expected (%d)", a_line, x_name, l, x_max);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd + 4, YSTR_EMPTY, a_prefix - 4) != 0) {
      yURG_err ('f', "%4d, ¶%s¶ line has non-whitespace (%*.*s) in prefix area (first %d chars)", a_line, x_name, a_prefix, a_prefix, a_recd, a_prefix);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk the line)------------------*/
   for (i = x_skip; i < MAX_LINE; i += 2) {
      /*---(grab full entry)-------------*/
      x_off = a_prefix + i * (a_next - 1);
      DEBUG_INPT    yLOG_value   ("x_off"     , x_off);
      ystrlcpy  (t, a_recd + x_off, (2 * a_next) - 1);
      DEBUG_INPT    yLOG_info    ("t"         , t);
      if (t [0] == ' ') {
         yURG_err ('f', "%4d, ¶%s¶ entry %d (%s) can not start with a space", a_line, x_name, i, t);
         continue;
      }
      /*---(grab substring)--------------*/
      ystrldchg (t, '·', ' ' , LEN_DESC);
      ystrltrim (t, ySTR_BOTH, LEN_DESC);
      DEBUG_INPT    yLOG_info    ("t"         , t);
      l = strlen (t);
      DEBUG_INPT    yLOG_value   ("l"         , l);
      /*---(check for junk chars)--------*/
      for (j = 0; j < l; ++j) {
         DEBUG_INPT    yLOG_char    ("t [j]"     , t [j]);
         if (strchr (YSTR_ALNUM, t [j]) == NULL) {
            yURG_err ('f', "%4d, ¶%s¶ entry %d (%s) contains illegal char, pos %d (%c)", a_line, x_name, i, t, j, t [j]);
            x_bad = 'y';
            continue;
         }
      }
      DEBUG_INPT    yLOG_char    ("x_bad"     , x_bad);
      if (x_bad == 'y')  continue;
      /*---(place name)------------------*/
      DEBUG_INPT    yLOG_value   ("i"         , i);
      n = a_map [i];
      DEBUG_INPT    yLOG_value   ("n"         , n);
      DEBUG_INPT    yLOG_info    ("g_char"    , g_char [n].name);
      if (strcmp ("-", t) == 0)  sprintf (t, "char%d", n);
      if (strcmp (g_char [n].name, "") != 0) {
         yURG_err ('f', "%4d, ¶%s¶ entry %d mapped to %d is duplicate, i.e., entry already set", a_line, x_name, i, t, j, t [j]);
         continue;
      }
      ystrlcpy (g_char [n].name, t, LEN_LABEL);
      /*---(next)------------------------*/
      ++c;
   }
   /*---(check trouble)------------------*/
   yURG_msg ('-', "%4d,    ¶%s¶ line, processed %d fields correctly", a_line, x_name, c);
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 8) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TXT__image              (int a_line, cchar a_recd [LEN_RECD], short a_prefix, short a_wide, short a_next, short a_tall, short a_map [MAX_LINE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i, j;
   int         l           =    0;
   char        x_bad       =  '-';
   char        x_name      [LEN_TERSE] = "";
   int         x_max       =    0;
   char        t           [LEN_DESC];
   int         x_off       =    0;
   char        c           =    0;
   short       n           =    0;
   int         x_byte      =    0;
   int         x_val       =    0;
   static char x_line      =    0;
   static char x_bot       =  'y';
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   DEBUG_INPT    yLOG_complex ("a_args"    , "%2dp, %2dw, %2dn", a_prefix, a_wide, a_next);
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map  == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_complex ("before"    , "%c, %d", x_bot, x_line);
   --rce;
   if      (strncmp (a_recd, "TOP " , 4) == 0)  {
      DEBUG_INPT    yLOG_note    ("handle a TOP");
      strcpy (x_name, "TOP");
      if (x_bot != 'y') {
         DEBUG_INPT    yLOG_note    ("can not handle TOP unless first or after BOT");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, can not process TOP unless first, until after BOT", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_line = 0;
      x_bot  = '-';
   }
   else if (strncmp (a_recd, "BOT " , 4) == 0)  {
      DEBUG_INPT    yLOG_note    ("handle a BOT");
      strcpy (x_name, "BOT");
      ++x_line;
      if (x_bot == 'y') {
         DEBUG_INPT    yLOG_note    ("can not handle BOT as it is already set");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, can not process BOT as already set", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_bot = 'y';
      if (x_line < a_tall - 1) {
         DEBUG_INPT    yLOG_note    ("too few image lines processed to be BOT");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, attempted BOT with too few total lines", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (x_line > a_tall - 1) {
         DEBUG_INPT    yLOG_note    ("too many image lines processed to be BOT");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, attempted BOT with too many total lines", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   else if (strncmp (a_recd, "c "   , 2) == 0)  {
      DEBUG_INPT    yLOG_note    ("handle a c/pixel line");
      strcpy (x_name, "c");
      ++x_line;
      if (x_bot == 'y') {
         DEBUG_INPT    yLOG_note    ("can not handle c/pixel as BOT is set");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, can not add lines, BOT already set", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (x_line > a_tall - 2) {
         DEBUG_INPT    yLOG_note    ("too many c/pixel lines image lines without BOT");
         yURG_err ('f', "%4d, ¶%s¶ line %d of %d, attempted too many total lines before BOT", a_line, x_name, x_line + 1, a_tall);
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   else {
      DEBUG_INPT    yLOG_note    ("do not recognize record type");
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_complex ("after"     , "%c, %d", x_bot, x_line);
   l = strlen (a_recd);
   DEBUG_INPT    yLOG_value   ("l"         , l);
   x_max = a_prefix + (MAX_LINE * (a_next - 1)) - 1;
   DEBUG_INPT    yLOG_value   ("x_max"     , x_max);
   --rce;  if (x_max > l) {
      yURG_err ('f', "%4d, ¶%s¶ line does not have enough space (%d) vs expected (%d)", a_line, x_name, l, x_max);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk the line)------------------*/
   for (i = 0; i < MAX_LINE; ++i) {
      /*---(grab full entry)-------------*/
      x_off = a_prefix + i * (a_next - 1);
      DEBUG_INPT    yLOG_value   ("x_off"     , x_off);
      ystrlcpy  (t, a_recd + x_off, a_wide + 1);
      ystrltrim (t, ySTR_BOTH, LEN_DESC);
      DEBUG_INPT    yLOG_info    ("t"         , t);
      l = strlen (t);
      DEBUG_INPT    yLOG_value   ("l"         , l);
      if (l != a_wide) {
         yURG_err ('f', "%4d, ¶%s¶ entry %d line %d (%s) does not match width (%d)", a_line, x_name, i, x_line, t, a_wide);
         x_bad = 'y';
         continue;
      }
      /*---(check for junk chars)--------*/
      for (j = 0; j < l; ++j) {
         DEBUG_INPT    yLOG_char    ("t [j]"     , t [j]);
         if (strchr ("-#", t [j]) == NULL) {
            yURG_err ('f', "%4d, ¶%s¶ entry %d line %d (%s) contains illegal charater, pos %d (%c)", a_line, x_name, i, x_line, t, j, t [j]);
            x_bad = 'y';
            continue;
         }
      }
      if (x_bad == 'y')  continue;
      /*---(place image)-----------------*/
      DEBUG_INPT    yLOG_value   ("i"         , i);
      n = a_map [i];
      DEBUG_INPT    yLOG_value   ("n"         , n);
      DEBUG_INPT    yLOG_info    ("g_char"    , g_char [n].image [x_line]);
      if (strcmp (g_char [n].image [x_line], "") != 0) {
         yURG_err ('f', "%4d, ¶%s¶ entry %d line %d mapped to %d is duplicate, i.e., entry already set", a_line, x_name, i, x_line, t, j, t [j]);
         continue;
      }
      ystrlcpy (g_char [n].image [x_line], t, LEN_LABEL);
      /*---(update byte)-----------------*/
      x_byte = 0;
      for (j = 0; j < l; ++j) {
         x_val = pow (2, 15 - j);
         if (t [j] == '#')  x_byte += x_val;
      }
      g_char [n].bytes [x_line] = x_byte;
      /*---(next)------------------------*/
      ++c;
   }
   /*---(check trouble)------------------*/
   yURG_msg ('-', "%4d,    ¶%s¶ line, processed %d fields correctly", a_line, x_name, c);
   DEBUG_INPT    yLOG_value   ("c"         , c);
   --rce;  if (c != 16) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}


/*> char                                                                                        <* 
 *> inpt__names          (int a_offset)                                                         <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         i           = 0;                                                             <* 
 *>    char        x_name      [30];                                                            <* 
 *>    int         n           = 0;                                                             <* 
 *>    /+---(walk names)---------------------+/                                                 <* 
 *>    for (i = 0; i < 16; i += 2) {                                                            <* 
 *>       /+---(get name)--------------------+/                                                 <* 
 *>       ystrlcpy  (x_name, g_recd + g_prefix + (i + a_offset) * g_next, 16);                  <* 
 *>       ystrltrim (x_name, ySTR_BOTH, 2000);                                                  <* 
 *>       /+---(store it)--------------------+/                                                 <* 
 *>       n = s_map [i + a_offset];                                                             <* 
 *>       if (strcmp ("-", x_name) == 0)  sprintf (x_name, "char%d", n);                        <* 
 *>       /+> printf ("%-2d  [%s]\n", i + a_offset, x_name);                              <+/   <* 
 *>       ystrlcpy  (g_char [n].name, x_name, 16);                                              <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("\n");                                                                 <+/   <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/

/*> char                                                                                        <* 
 *> inpt__abbr           (void)                                                                 <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         i           =    0;                                                          <* 
 *>    int         n           =    0;                                                          <* 
 *>    uchar       x_short     =    0;                                                          <* 
 *>    /+> printf ("%s\n", g_recd);                                                       <+/   <* 
 *>    for (i = 0; i < 16; ++i) {                                                               <* 
 *>       n = s_map [i];                                                                        <* 
 *>       x_short = g_recd [g_prefix + (i * g_next)];                                           <* 
 *>       /+> printf ("%c ", x_short);                                                    <+/   <* 
 *>       switch (x_short) {                                                                    <* 
 *>       case 172  : g_char [n].abbr = '\0';     break;                                        <* 
 *>       default   : g_char [n].abbr = x_short;  break;                                        <* 
 *>       }                                                                                     <* 
 *>       /+> if (g_char [n].abbr > 0)  printf ("%c ", g_char [n].abbr);                  <+/   <* 
 *>       /+> else                      printf ("  ");                                    <+/   <* 
 *>       x_short = g_recd [g_prefix + (i * g_next) + 2];                                       <* 
 *>       if (x_short == (uchar) '´')  g_char [n].key = 'y';                                    <* 
 *>       /+> printf ("%c ", x_short);                                                    <+/   <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("\n");                                                                 <+/   <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/

/*> char                                                                                        <* 
 *> inpt__char           (int a_row)                                                            <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         i           =    0;                                                          <* 
 *>    int         j           =    0;                                                          <* 
 *>    int         x_val       =    0;                                                          <* 
 *>    int         x_byte      =    0;                                                          <* 
 *>    int         n           =    0;                                                          <* 
 *>    int         x_max       = g_wide - 1;                                                    <* 
 *>    /+> printf ("   -- bytes         ");                                               <+/   <* 
 *>    for (i = 0; i < 16; ++i) {                                                               <* 
 *>       n = s_map [i];                                                                        <* 
 *>       x_byte = 0;                                                                           <* 
 *>       for (j = x_max; j >= 0; --j) {                                                        <* 
 *>          if (j == 0)  x_val = 1;                                                            <* 
 *>          else         x_val = pow (2, j);                                                   <* 
 *>          g_char [n].image [a_row][x_max - j] =  ' ';                                        <* 
 *>          if (g_recd [g_prefix + (i * g_next) + (x_max - j)] == '#') {                       <* 
 *>             x_byte += x_val;                                                                <* 
 *>             g_char [n].image [a_row][x_max - j] = '#';                                      <* 
 *>          }                                                                                  <* 
 *>       }                                                                                     <* 
 *>       g_char [n].bytes [a_row] = x_byte;                                                    <* 
 *>       /+> printf ("%-3d/%-1d:%-4d ", n, a_row, g_char [n].bytes [a_row]);             <+/   <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("\n");                                                                 <+/   <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/

/*> char                                                                                        <* 
 *> inpt__glyph          (int a_block, int a_row)                                               <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         i           =    0;                                                          <* 
 *>    int         j           =    0;                                                          <* 
 *>    int         n           =    0;                                                          <* 
 *>    uchar       x_ch        =  ' ';                                                          <* 
 *>    char       *x_valid     = "-+:*172%98#@";                                                <* 
 *>    char       *p           = NULL;                                                          <* 
 *>    uchar       v           =    0;                                                          <* 
 *>    float       x_inc       =    0;                                                          <* 
 *>    uchar       x_val       =    0;                                                          <* 
 *>    /+> printf ("   -- bytes        :  ");                                             <+/   <* 
 *>    x_inc = 255 / 13;                                                                        <* 
 *>    for (i = 0; i < 16; ++i) {                                                               <* 
 *>       n = a_block * 16 + i;                                                                 <* 
 *>       for (j = 0; j < g_ywide; ++j) {                                                       <* 
 *>          /+---(get char)-----------------+/                                                 <* 
 *>          x_ch  = g_recd [4 + i * g_ywide + j];                                              <* 
 *>          /+> printf ("%c", x_ch);                                                     <+/   <* 
 *>          /+---(defaults)-----------------+/                                                 <* 
 *>          g_char [n].yfont  [a_row][j] =  0;                                                 <* 
 *>          g_char [n].pretty [a_row][j] = x_ch;                                               <* 
 *>          /+---(check char)---------------+/                                                 <* 
 *>          p  = strchr ("-+:*172%98#@", x_ch);                                                <* 
 *>          if (p == NULL)  continue;                                                          <* 
 *>          /+---(replace)------------------+/                                                 <* 
 *>          v = p - x_valid + 1;                                                               <* 
 *>          x_val = v * x_inc;                                                                 <* 
 *>          g_char [n].yfont  [a_row][j] = x_val;                                              <* 
 *>          /+---(done)---------------------+/                                                 <* 
 *>       }                                                                                     <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("\n");                                                                 <+/   <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/



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
         rc = 2;
         break;
      }
      ++x_line;
      x_len = strlen (x_recd);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      ystrlcpy (t, x_recd, LEN_HUND);
      DEBUG_INPT    yLOG_complex ("line"      , "%4d %4då%sæ", x_line, x_len, t);
      /*---(filter)----------------------*/
      x_valid = '-';
      c = x_recd [0];
      if      (strncmp (x_recd, "#@ "       ,  3) == 0) {
         DEBUG_INPT    yLOG_note    ("found control record");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "hex       ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found hex identifiers");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "odds      ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found odd-numbered character names");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "even      ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found even-numbered character names");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "TOP -"     ,  5) == 0) {
         DEBUG_INPT    yLOG_note    ("found top of character pixel data");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "c  "       ,  3) == 0) {
         DEBUG_INPT    yLOG_note    ("found character pixel data");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "BOT -"     ,  5) == 0) {
         DEBUG_INPT    yLOG_note    ("found bottom of character pixel data");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "short     ", 10) == 0) {
         DEBUG_INPT    yLOG_note    ("found shorthand character names");
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
TXT__symmetry        (uchar a_index, char a_wide, char a_tall, char a_cen, char a_mid)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i, x, y;
   /*> int         t, m, b, l, c, r;                                                  <*/
   float       a, n;
   float       p, q;
   int         x_ring      = 0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   g_char [a_index].pixels    = 0;
   for (i = 0; i < LEN_LABEL; ++i) {
      g_char [a_index].verts [i] = 0;
      g_char [a_index].horzs [i] = 0;
      g_char [a_index].diags [i] = 0;
   }
   g_char [a_index].vert = 0.0;
   g_char [a_index].horz = 0.0;
   g_char [a_index].diag = 0.0;
   /*---(clear stats)-----------------*/
   /*> t = m = b = l = c = r = 0;                                                     <*/
   p = q = 0.0;
   n = 0;
   /*---(by row)----------------------*/
   for (y = 0; y < a_tall; ++y) {
      /*---(by column)----------------*/
      for (x = 0; x < a_wide; ++x) {
         /*---(filter)----------------*/
         if (g_char [a_index].image [y][x] != '#')    continue;
         /*---(add vertical)----------*/
         ++(g_char [a_index].verts [a_tall - y]);
         ++(g_char [a_index].horzs [x]);
         x_ring = sqrt ((a_mid - x) * (a_mid - x) + (a_cen - y) * (a_cen - y));
         ++(g_char [a_index].diags [x_ring]);
         ++n;
         /*---(done with column)------*/
      }
      /*---(done with row)------------*/
   }
   g_char [a_index].pixels = n;
   /*---(vertical stats)-----------------*/
   a = 0;
   for (y = 0; y < a_tall; ++y) {
      a += g_char [a_index].verts [y] * (a_mid - y);
   }
   g_char [a_index].vert = a / n;
   /*---(horizontal stats)---------------*/
   a = 0;
   for (x = 0; x < a_wide; ++x) {
      a += g_char [a_index].horzs [x] * (x - a_cen);
   }
   g_char [a_index].horz = a / n;
   /*---(diagonal stats)-----------------*/
   a = 0;
   for (i = 0; i < LEN_LABEL; ++i) {
      a += g_char [a_index].diags [i] * i;
   }
   g_char [a_index].diag = a / n;
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;





   /*> for (x = 0; x < MAX_CHARSET; ++x) {                                                                <* 
    *>    t = m = b = l = c = r = 0;                                                                      <* 
    *>    p = q = 0.0;                                                                                    <* 
    *>    n = 0;                                                                                          <* 
    *>    for (y = 0; y < a_tall; ++y) {                                                                  <* 
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
    *> }                                                                                                  <*/
   return 0;
}

char
TXT__verify             (uchar a_index, char a_wide, char a_tall)
{
   char        rce         =  -10;
   int         i           =    0;
   int         l           =    0;
   char        x_bad       =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_INPT    yLOG_complex ("a_index"   , "%3d, %2x", a_index, a_index);
   g_char [a_index].ready = '-';
   DEBUG_INPT    yLOG_char    ("default"   , x_bad);
   if (g_char [a_index].hexline  <  0)           x_bad = 'y';
   DEBUG_INPT    yLOG_char    ("hexline"   , x_bad);
   if (g_char [a_index].hexcol   <  0)           x_bad = 'y';
   DEBUG_INPT    yLOG_char    ("hexcol"    , x_bad);
   if (strcmp (g_char [a_index].name, "") == 0)  x_bad = 'y';
   DEBUG_INPT    yLOG_char    ("name"      , x_bad);
   for (i = 0; i < a_tall; ++i) {
      l  = strlen (g_char [a_index].image [i]);
      if (l != a_wide)  x_bad = 'y';
   }
   DEBUG_INPT    yLOG_char    ("image"     , x_bad);
   --rce;  if (x_bad == 'y') {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_char [a_index].ready = 'y';
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TXT__audit              (char a_wide, char a_tall)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_bad       =  '-';
   for (i = 0; i < MAX_CHARSET; ++i) {
      rc = TXT__verify (i, a_wide, a_tall);
      if (rc < 0)  x_bad = 'y';
   }
   if (x_bad == 'y')  return -1;
   return 0;
}

char
TXT_get_all             (char a_audit, cchar a_txtfile [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(file handling)----+-----+-------*/
   FILE       *f           = NULL;
   short       x_map       [MAX_LINE]  = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
   char        x_recd      [LEN_RECD]  = "";
   int         x_len       =    0;
   /*---(config)-----------+-----+-------*/
   char        x_title     [LEN_DESC]  = "";
   char        w, t, a, d, u, l, p, g, n, c, m;
   /*---(working)----------+-----+-------*/
   int         x_line      =    0;
   char        x_mapped    =  '-';
   char        x_bad       =  '-';
   char        x_skip      =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(start)--------------------------*/
   if      (a_audit == 'y')  yURG_msg ('>', "conducting font source file (txt) audit...");
   else if (a_audit == 'p')  yURG_msg ('>', "gathre partial font source file (txt) data...");
   else                      yURG_msg ('>', "gather font source file (txt) data...");
   /*---(file open)----------------------*/
   yURG_msg ('-', "font source file å%sæ", a_txtfile);
   rc = FILE_open (a_txtfile, 'r', NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "font source file could not be openned (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purge data)---------------------*/
   yURG_msg ('-', "font source file openned successfully");
   rc = TXT_purge ();
   yURG_msg ('-', "purged existing font data");
   /*---(read file)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = TXT__read (f, &x_line, &x_len, x_recd);
      if (rc == 2) {
         yURG_msg ('-', "hit EOF, stop processing");
         break;
      }
      /*---(handle controls--------------*/
      if      (strncmp (x_recd, "#@ font_title ", 14) == 0) {
         rc = TXT__title  (x_line, x_recd, x_title);
         continue;
      }
      else if (strncmp (x_recd, "#@ font_size " , 13) == 0) {
         rc = TXT__sizing (x_line, x_recd, &w, &t, &a, &d, &u, &l, &p, &g, &n, &c, &m);
         continue;
      }
      else if (strncmp (x_recd, "#@ "           ,  3) == 0) {
         yURG_err ('f', "%4d, skipping unknown control line (%-20.20s)", x_line, x_recd);
         continue;
      }
      /*---(wait until controls)---------*/
      x_skip = '-';
      if (strcmp (x_title, "") == 0)  x_skip = 'y';
      if (w <= 0 || t <= 0)           x_skip = 'y';
      if (a <= 0 || d <= 0)           x_skip = 'y';
      if (u <= 0 || l <= 0)           x_skip = 'y';
      if (g <= 0)                     x_skip = 'y';
      if (x_skip   == 'y')  {
         yURG_err ('f', "%4d, skipping line (%-20.20s), controls not set", x_line, x_recd);
         continue;
      }
      /*---(handle)----------------------*/
      if      (strncmp (x_recd, "hex "          ,  4) == 0) {
         x_mapped = '-';
         rc = TXT__hex   (x_line, x_recd, p, w, n, x_map);
         if (rc < 0)  x_bad    = 'y';
         else         x_mapped = 'y';
         continue;
      }
      if (x_mapped == '-')  {
         yURG_err ('f', "%4d, skipping line (%-20.20s), mapping not set", x_line, x_recd);
         continue;
      }
      /*---(handle detail)---------------*/
      switch (x_recd [0]) {
      case 'o' : case 'e' :
         rc = TXT__name  (x_line, x_recd, p, w, n, x_map);
         if (rc < 0)  x_bad = 'y';
         break;
      case 's' :
         break;
      case 'T' : case 'c' : case 'B' :
         rc = TXT__image (x_line, x_recd, p, w, n, t, x_map);
         if (rc < 0)  x_bad = 'y';
         break;
      default  :
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(file close)---------------------*/
   rc = FILE_close (NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "file could not be closed (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "font source file closed successfully");
   yURG_msg ('-', "%d line read", x_line);
   /*---(save-back)----------------------*/
   --rce;  if (x_bad == 'y') {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify)-------------------------*/
   if (a_audit != 'p') {
      rc = TXT__audit (w, t);
      --rce;  if (rc < 0) {
         yURG_err ('f', "txt font did not pass audit");
         DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "all characters passed final audit");
   }
   /*---(save-back)----------------------*/
   ystrlcpy (g_title, x_title, LEN_DESC);
   g_wide    = w;
   g_tall    = t;
   g_ascent  = a;
   g_descent = d;
   g_upper   = u;
   g_lower   = l;
   g_prefix  = p;
   g_gap     = g;
   g_next    = n;
   g_cen     = c;
   g_mid     = m;
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
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

char*
TXT__show_map           (short a_map [MAX_LINE])
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

char*
TXT__show_charset       (char a_type, char a_wide, char a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i, j;
   int         l           =    0;
   int         l_all       =    0;
   int         x_max       = MAX_CHARSET;
   int         x_off       =    0;
   char        x_bad       =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   for (i = 0; i < LEN_RECD; ++i)   s_print [i] = '\0';
   if (tolower (a_type) == a_type) {
      x_max = 127 - 32;
      x_off = 32;
   }
   for (i = 0; i < x_max; ++i) {
      DEBUG_INPT    yLOG_value   ("char"      , i + x_off);
      s_print [i] = '·';
      switch (a_type) {
      case 'E' : case 'e' :
         if      (i + x_off <   32)  s_print [i] = '·';
         else if (i + x_off == 127)  s_print [i] = '·';
         else                        s_print [i] = i + x_off;
         break;
      case 'X' : case 'x' :
         if (g_char [i + x_off].hexline >= 0 && g_char [i + x_off].hexcol >= 0)   s_print [i] = '³';
         break;
      case 'N' : case 'n' :
         if (strcmp (g_char [i + x_off].name, "") != 0)   s_print [i] = '³';
         break;
      case 'R' : case 'r' :
         if (g_char [i + x_off].ready == 'y')             s_print [i] = '³';
         break;
      case 'I' : case 'i' :
         l_all = 0;
         x_bad = '-';
         for (j = 0; j < a_tall; ++j) {
            l  = strlen (g_char [i + x_off].image [j]);
            if (l != a_wide)  x_bad = 'y';
            l_all += l;
            DEBUG_INPT    yLOG_complex ("image"     , "%2d#, %2dw, %2dl, %2da, %c", j, a_wide, l, l_all, x_bad);
         }
         if      (l_all >   0) {
            if (x_bad != 'y')  s_print [i] = '³';
            else               s_print [i] = '?';
         }
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return s_print;
}

char*
TXT__show_vert          (uchar a_index)
{
   int         i          =    0;
   char        t          [LEN_TERSE] = "";
   sprintf (t, "%3d ", g_char [a_index].verts [i]);
   ystrlcat (s_print, t, LEN_RECD);
   for (i = 0; i < LEN_TERSE; ++i) {
      sprintf (t, "%2d ", g_char [a_index].verts [i]);
      ystrlcat (s_print, t, LEN_RECD);
   }
   sprintf (t, "%4.2d", g_char [a_index].vert);
   ystrlcat (s_print, t, LEN_RECD);
   return s_print;
}

