#include    "phoenicia.h"


/*
 *  BDF  =  glyph bitmap distribution format (adobe)
 *     -- only seen on unix and linux now-days
 *     -- version 2.1 was standardized on my x-windows (1988)
 *     -- version 2.2 extensions for non-western languages
 *
 *  generally replaced by...
 *     -- PCF = portable compiled format, slightly more efficient that BDF
 *     -- OTF = open-type format (scalable and complex)  ZERO INTEREST
 *     -- TTF = true-type format (scalable and complex)  ZERO INTEREST
 *
 *
 *  PSF  = pc screen font
 *     -- currently employed by linux kernel for console fonts
 *
 */
/*  header from wiki page
 *     -- FONT line uses XLFD = x-windows logical font description
 *     -- XLFD is largely replaced by "fontconfig" system
 *
 *  STARTFONT 2.1
 *
 *  FONT -gnu-unifont-medium-r-normal--16-160-75-75-c-80-iso10646-1
 *  SIZE 16 75 75                    point-of-font dpix dpiy  (75 75 is normal x-windows)
 *  FONTBOUNDINGBOX 16 16 0 -2       default > width height left bottom
 *
 *  STARTPROPERTIES 2
 *  FONT_ASCENT 14
 *  FONT_DESCENT 2
 *  ENDPROPERTIES
 *
 *  CHARS 1
 *
 *  STARTCHAR U+0041
 *  ENCODING 64
 *  SWIDTH 500 0
 *  DWIDTH 8 0
 *  BBX 8 16 0 -2                    override > width height left bottom
 *  BITMAP
 *  00
 *  00
 *  00
 *  00
 *  18
 *  24
 *  24
 *  42
 *  42
 *  7E
 *  42
 *  42
 *  42
 *  42
 *  00
 *  00
 *  ENDCHAR
 *  ENDFONT
 *
 *
 */


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

/*> char                                                                              <* 
 *> conv_row             (void)                                                       <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    char        x_ch        =  '-';                                                <* 
 *>    int         x_val       =    0;                                                <* 
 *>    for (i = 0; i < 2; ++i) {                                                      <* 
 *>       x_ch   = g_recd [i];                                                        <* 
 *>       if      (x_ch >= '0' && x_ch <= '9')  x_val = x_ch - '0';                   <* 
 *>       else if (x_ch >= 'A' && x_ch <= 'F')  x_val = x_ch - 'A' + 10;              <* 
 *>       else                                  x_val = 0;                            <* 
 *>       printf ("%s", s_map [x_val]);                                               <* 
 *>    }                                                                              <* 
 *>    printf ("\n");                                                                 <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> int                                                                                         <* 
 *> main                 (int a_argc, char *a_argv[])                                           <* 
 *> {                                                                                           <* 
 *>    char        x_conv      =  '-';                                                          <* 
 *>    int         x_line      =    0;                                                          <* 
 *>    int         x_len       =    0;                                                          <* 
 *>    g_file = fopen (g_name, "r");                                                            <* 
 *>    if (g_file == NULL) {                                                                    <* 
 *>       return -1;                                                                            <* 
 *>    }                                                                                        <* 
 *>    while (1) {                                                                              <* 
 *>       fgets (g_recd, 2000, g_file);                                                         <* 
 *>       if (feof (g_file)) {                                                                  <* 
 *>          /+> printf ("   -- end of file\n");                                          <+/   <* 
 *>          break;                                                                             <* 
 *>       }                                                                                     <* 
 *>       ++x_line;                                                                             <* 
 *>       if (strchr ("\0\n# ", g_recd [0]) != NULL) {                                          <* 
 *>          /+> printf ("   -- blank line\n");                                           <+/   <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       if (g_recd [0] == '#') {                                                              <* 
 *>          /+> printf ("   -- comment line\n");                                         <+/   <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       /+> printf ("   LINE %3d\n", x_line);                                           <+/   <* 
 *>       x_len = strlen (g_recd);                                                              <* 
 *>       g_recd [--x_len] = '\0';                                                              <* 
 *>       /+> printf ("   len  %d\n" , x_len);                                            <+/   <* 
 *>       /+> printf ("   recd %s\n" , g_recd);                                           <+/   <* 
 *>       if (strncmp ("BITMAP", g_recd, 6) == 0) {                                             <* 
 *>          x_conv = 'y';                                                                      <* 
 *>          /+> printf ("   -- something else\n");                                       <+/   <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       if (strncmp ("ENDCHAR", g_recd, 7) == 0) {                                            <* 
 *>          x_conv = '-';                                                                      <* 
 *>          /+> printf ("   -- something else\n");                                       <+/   <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       if (x_conv != 'y') {                                                                  <* 
 *>          printf ("%s\n", g_recd);                                                           <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       conv_row ();                                                                          <* 
 *>    }                                                                                        <* 
 *>    fclose (g_file);                                                                         <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/



/*---(key fields)--------------------------------*/
/*                             shrike  square
 * FOUNDRY   is font name
 * CAPHEIGHT is for capitals    7       5
 * XHEIGHT is for lower         5       3
 * PIXELSZ                     10       6
 * WEIGHT                      10       6
 * QUADWIDTH                    6       6
 * ACCENT                       8       5
 * DESCENT                      2       l
 *
 *
 */

FILE       *s_out       = NULL;


#define     BDFVERSION  2.1
#define     REGISTRY    ""

#define     FOUNDRY     "heatherly"
#define     WEIGHTNM    "medium"
#define     SLANT       "r"
#define     STYLE       ""
#define     SETWIDTH    "normal"
#define     RESX        "75"
#define     RESY        "75"
#define     RESNUM      75
#define     SPACING     "c"
#define     AVGWIDTH    "60"
#define     CHARSET     "iso8859"
#define     ENCODING    "1"
#define     COPYRIGHT   "none"
/*> #define     CAPHEIGHT   7               /+ uppercase height above baseline    +/   <*/
/*> #define     XHEIGHT     5               /+ lowercase height above baseline    +/   <*/
/*> #define     WEIGHT      10                                                        <*/
#define     RES         103
/*> #define     QUADWIDTH   6                                                         <*/
/*> #define     ASCENT      8                                                         <*/
/*> #define     DESCENT     2                                                         <*/



/*> char                                                                                                                   <* 
 *> DBF__open               (char a_name [LEN_PATH], char a_access, char r_name [LEN_PATH], char *r_mode, FILE **r_file)   <* 
 *> {                                                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                            <* 
 *>    char        rce         =  -10;                                                                                     <* 
 *>    int         x_len       =    0;                                                                                     <* 
 *>    FILE       *f           = NULL;                                                                                     <* 
 *>    char        x_access    [LEN_TERSE] = "";                                                                           <* 
 *>    /+---(header)-------------------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                                                        <* 
 *>    /+---(defense)------------------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("r_file"    , r_file);                                                                <* 
 *>    --rce;  if (r_file == NULL) {                                                                                       <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("file pointer (r_file) can not be null");                                          <* 
 *>       DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                                                <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("*r_file"   , *r_file);                                                               <* 
 *>    --rce;  if (*r_file != NULL) {                                                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("file appears already open");                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                                                <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    /+---(default)------------------------+/                                                                            <* 
 *>    if (r_name  != NULL)  strcpy (r_name, "");                                                                          <* 
 *>    if (r_file  != NULL)  *r_file = NULL;                                                                               <* 
 *>    if (r_mode  != NULL)  *r_mode = '-';                                                                                <* 
 *>    /+---(secondary defense)--------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);                                                                <* 
 *>    --rce;  if (a_name == NULL || a_name [0] == '\0') {                                                                 <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("file name (a_name) can not be null or empty");                                    <* 
 *>       DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                                                <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);                                                                <* 
 *>    x_len = strlen (a_name);                                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("x_len"     , x_len);                                                                 <* 
 *>    --rce;  if (x_len < 5) {                                                                                            <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("file (a_name) is too short ( < 5 chars)");                                        <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                                     <* 
 *>       return  rce;                                                                                                     <* 
 *>    }                                                                                                                   <* 
 *>    /+---(check access)-------------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_char    ("a_access"  , a_access);                                                              <* 
 *>    --rce;  switch (a_access) {                                                                                         <* 
 *>    case 'r' :   strcpy (x_access, "rt");   break;                                                                      <* 
 *>    case 'w' :   strcpy (x_access, "wt");   break;                                                                      <* 
 *>    case 'R' :   strcpy (x_access, "rb");   break;                                                                      <* 
 *>    case 'W' :   strcpy (x_access, "wb");   break;                                                                      <* 
 *>    default  :                                                                                                          <* 
 *>                 DEBUG_YGLTEX    yLOG_warn    ("access request not understood");                                        <* 
 *>                 DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                                      <* 
 *>                 return rce;                                                                                            <* 
 *>    }                                                                                                                   <* 
 *>    DEBUG_YGLTEX    yLOG_info    ("x_access"  , x_access);                                                              <* 
 *>    /+---(open)---------------------------+/                                                                            <* 
 *>    f = fopen (a_name, x_access);                                                                                       <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("f"         , f);                                                                     <* 
 *>    --rce;  if (f == NULL) {                                                                                            <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("file could not be openned");                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                                                <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    /+---(save·back)----------------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("saving back to return arguments");                                                   <* 
 *>    if (r_name  != NULL)  ystrlcpy (r_name, a_name, LEN_HUND);                                                          <* 
 *>    if (r_file  != NULL)  *r_file = f;                                                                                  <* 
 *>    if (r_mode  != NULL)  *r_mode = a_access;                                                                           <* 
 *>    /+---(complete)-----------------------+/                                                                            <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                                        <* 
 *>    return 0;                                                                                                           <* 
 *> }                                                                                                                      <*/

char
BDF__header          (FILE *f, char a_title [LEN_LABEL], char a_wide, char a_tall, char a_ascent, char a_descent, char a_upper, char a_lower)
{
   fprintf (f, "STARTFONT %.1f\n"             , BDFVERSION);
   fprintf (f, "FONT -%s-%s-%s-%s-%s-"        , FOUNDRY, a_title, WEIGHTNM, SLANT, SETWIDTH);
   fprintf (f,    "-%d-%d-%s-%s-%s"           , a_tall, a_tall * 10, RESX, RESY, SPACING);
   fprintf (f,    "-%s-%s-%s\n"               , AVGWIDTH, CHARSET, ENCODING);
   fprintf (f, "SIZE %d %s %s\n"              , a_tall, RESX, RESY);
   fprintf (f, "FONTBOUNDINGBOX %d %d %d %d\n", a_wide, a_tall, 0, -a_descent);
   fprintf (f, "\n");
   fprintf (f, "STARTPROPERTIES %d\n"         , 23);
   fprintf (f, "  FONTNAME_REGISTRY \"%s\"\n"   , REGISTRY);
   fprintf (f, "  FOUNDRY           \"%s\"\n"   , FOUNDRY);
   fprintf (f, "  FAMILY_NAME       \"%s\"\n"   , a_title);
   fprintf (f, "  WEIGHT_NAME       \"%s\"\n"   , WEIGHTNM);
   fprintf (f, "  SLANT             \"%s\"\n"   , SLANT);
   fprintf (f, "  SETWIDTH_NAME     \"%s\"\n"   , SETWIDTH);
   fprintf (f, "  ADD_STYLE_NAME    \"%s\"\n"   , STYLE);
   fprintf (f, "  PIXEL_SIZE        \"%d\"\n"   , a_tall);
   fprintf (f, "  POINT_SIZE        \"%d\"\n"   , a_tall * 10);
   fprintf (f, "  RESOLUTION_X      \"%s\"\n"   , RESX);
   fprintf (f, "  RESOLUTION_Y      \"%s\"\n"   , RESY);
   fprintf (f, "  SPACING           \"%s\"\n"   , SPACING);
   fprintf (f, "  AVERAGE_WIDTH     \"%s\"\n"   , AVGWIDTH);
   fprintf (f, "  CHARSET_REGISTRY  \"%s\"\n"   , CHARSET);
   fprintf (f, "  CHARSET_ENCODING  \"%s\"\n"   , ENCODING);
   fprintf (f, "  COPYRIGHT         \"%s\"\n"   , COPYRIGHT);
   fprintf (f, "  CAP_HEIGHT        %d\n"       , a_upper);
   fprintf (f, "  X_HEIGHT          %d\n"       , a_lower);
   fprintf (f, "  WEIGHT            %d\n"       , a_tall);
   fprintf (f, "  RESOLUTION        %d\n"       , RES);
   fprintf (f, "  QUAD_WIDTH        %d\n"       , a_wide);
   fprintf (f, "  FONT_ASCENT       %d\n"       , a_ascent);
   fprintf (f, "  FONT_DESCENT      %d\n"       , a_descent);
   fprintf (f, "ENDPROPERTIES\n"       );
   fprintf (f, "\n");
   fprintf (f, "CHARS %d\n"                   , MAX_CHARSET);
   fprintf (f, "\n");
   return 0;
}

char
BDF__glyph              (FILE *f, uchar a_index, char a_wide, char a_tall, char a_descent)
{
   int         y           = 0;
   char       *x_hex       = "0123456789ABCDEF";
   int         x_val       = 0;
   int         x_byte      = 0;
   float       x_pixel     = 0.0;
   float       x_res       = 0.0;
   float       x_respx     = 0.0;
   int         x_swidth    =   0;
   /*---(openning)-----------------------*/
   fprintf (f, "STARTCHAR %s\n"   , g_char [a_index].name);
   fprintf (f, "ENCODING %d\n"    , a_index);
   x_pixel =  (float) a_wide;
   x_res   = ((float) RESNUM) / 72.0;
   x_respx = x_pixel / x_res;
   x_swidth = x_respx * 100;
   fprintf (f, "SWIDTH %d %d\n"   , x_swidth , 0);
   fprintf (f, "DWIDTH %d %d\n"   , a_wide, 0);
   fprintf (f, "BBX %d %d %d %d\n", a_wide, a_tall, 0, -a_descent);
   fprintf (f, "BITMAP\n");
   /*---(bitmap)-------------------------*/
   for (y = 0; y < a_tall; ++y) {
      fprintf (f, "%04X\n", g_char [a_index].bytes [y]);
      /*> x_val = g_char [a_index].bytes [y];                                         <* 
       *> fprintf (f, "%5d   ", x_val);                                               <* 
       *> /+---(over 8-bit)--------+/                                                 <* 
       *> x_byte = x_val / 256;                                                       <* 
       *> fprintf (f, "0%c", x_hex [x_byte]);                                         <* 
       *> x_val  %= 256;                                                              <* 
       *> /+---(high nibble)-------+/                                                 <* 
       *> x_byte = x_val / 16;                                                        <* 
       *> fprintf (f, "%c", x_hex [x_byte]);                                          <* 
       *> /+---(low nibble)--------+/                                                 <* 
       *> x_byte = x_val % 16;                                                        <* 
       *> fprintf (f, "%c", x_hex [x_byte]);                                          <* 
       *> /+---(finish)------------+/                                                 <* 
       *> fprintf (f, "\n");                                                          <*/
   }
   /*---(closing)------------------------*/
   fprintf (f, "ENDCHAR\n");
   fprintf (f, "\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
BDF__footer             (FILE *f)
{
   fprintf (f, "ENDFONT\n");
   return 0;
}

char
BDF_make_all            (char a_bdffile [LEN_PATH], char a_title [LEN_DESC], char a_wide, char a_tall, char a_ascent, char a_descent, char a_upper, char a_lower)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         i           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(start)--------------------------*/
   yURG_msg ('>', "create BDF version of font source data...");
   /*---(file open)----------------------*/
   yURG_msg ('-', "BDF file å%sæ", a_bdffile);
   rc = FILE_open (a_bdffile, 'w', NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "BDF file could not be openned (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "BDF file openned successfully");
   /*---(write header)-------------------*/
   BDF__header (f, a_title, a_wide, a_tall, a_ascent, a_descent, a_upper, a_lower);
   /*---(write all chars)----------------*/
   for (i = 0; i < MAX_CHARSET; ++i) {
      rc = BDF__glyph (f, i, a_wide, a_tall, a_descent);
      if (rc >= 0)  ++c;
   }
   /*---(write footer)-------------------*/
   BDF__footer (f);
   /*---(file close)---------------------*/
   rc = FILE_close (NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "file could not be closed (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "BDF file closed successfully");
   yURG_msg ('-', "%d characters written", c);
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                        <* 
 *> BDF_rows             (void)                                                                 <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         i           = 0;                                                             <* 
 *>    int         j           = 0;                                                             <* 
 *>    char       *x_hex       = "0123456789ABCDEF";                                            <* 
 *>    int         x_val       = 0;                                                             <* 
 *>    int         x_byte      = 0;                                                             <* 
 *>    float       x_pixel     = 0.0;                                                           <* 
 *>    float       x_res       = 0.0;                                                           <* 
 *>    float       x_respx     = 0.0;                                                           <* 
 *>    int         x_swidth    =   0;                                                           <* 
 *>    for (i = 0; i < MAX_CHARSET; ++i) {                                                      <* 
 *>       x_pixel =  (float) g_wide;                                                            <* 
 *>       x_res   = ((float) RESNUM) / 72.0;                                                    <* 
 *>       x_respx = x_pixel / x_res;                                                            <* 
 *>       x_swidth = x_respx * 100;                                                             <* 
 *>       printf ("STARTCHAR %s\n"   , g_char [i].name);                                        <* 
 *>       printf ("ENCODING %d\n"    , i);                                                      <* 
 *>       /+> printf ("pixels  %8.3f\n" , x_pixel);                                       <+/   <* 
 *>       /+> printf ("res     %8.3f\n" , x_res);                                         <+/   <* 
 *>       /+> printf ("px/res  %8.3f\n" , x_respx);                                       <+/   <* 
 *>       printf ("SWIDTH %d %d\n"   , x_swidth , 0);                                           <* 
 *>       printf ("DWIDTH %d %d\n"   , g_wide, 0);                                              <* 
 *>       printf ("BBX %d %d %d %d\n", g_wide, g_tall, 0, -g_descent);                          <* 
 *>       printf ("BITMAP\n");                                                                  <* 
 *>       for (j = 0; j < g_tall; ++j) {                                                        <* 
 *>          x_val = g_char [i].bytes [j];                                                      <* 
 *>          /+> printf ("%-2d  [", x_val);                                               <+/   <* 
 *>          /+---(over 8-bit)--------+/                                                        <* 
 *>          x_byte = x_val / 256;                                                              <* 
 *>          printf ("0%c", x_hex [x_byte]);                                                    <* 
 *>          x_val  %= 256;                                                                     <* 
 *>          /+---(high nibble)-------+/                                                        <* 
 *>          x_byte = x_val / 16;                                                               <* 
 *>          printf ("%c", x_hex [x_byte]);                                                     <* 
 *>          /+---(low nibble)--------+/                                                        <* 
 *>          x_byte = x_val % 16;                                                               <* 
 *>          printf ("%c", x_hex [x_byte]);                                                     <* 
 *>          /+> printf ("]");                                                            <+/   <* 
 *>          /+---(finish)------------+/                                                        <* 
 *>          printf ("\n");                                                                     <* 
 *>       }                                                                                     <* 
 *>       printf ("ENDCHAR\n");                                                                 <* 
 *>       printf ("\n");                                                                        <* 
 *>    }                                                                                        <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/

/*> int                                                                                         <* 
 *> main                 (int a_argc, char *a_argv[])                                           <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    char        rc          =    0;                                                          <* 
 *>    /+---(read source)--------------------+/                                                 <* 
 *>    /+> if (a_argc < 2)  return -1;                                                    <*    <* 
 *>     *> if      (strcmp (a_argv [1], "shrike") == 0)  share_shrike ();                 <*    <* 
 *>     *> else if (strcmp (a_argv [1], "square") == 0)  share_square ();                 <*    <* 
 *>     *> else    return  -2;                                                            <*    <* 
 *>     *> rc = SHARE_read_all ();                                                        <+/   <* 
 *>    /+---(write out)----------------------+/                                                 <* 
 *>    /+> BDF_header ();                                                                 <*    <* 
 *>     *> BDF_rows   ();                                                                 <*    <* 
 *>     *> BDF_footer   ();                                                               <+/   <* 
 *>    /+---(complete)-----------------------+/                                                 <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/
