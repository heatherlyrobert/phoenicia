#include    "font.h"


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


#define     BDFVERSION  2.1
#define     REGISTRY    ""

/*> #define     FOUNDRY     "Shrike"                                                  <*/
#define     FAMILY      "Fixed"
#define     WEIGHTNM    "Medium"
#define     SLANT       "R"
#define     STYLE       ""
#define     SETWIDTH    "Normal"
/*> #define     PIXELSZ     "10"                                                      <*/
/*> #define     POINTSZ     "100"                                                     <*/
#define     RESX        "75"
#define     RESY        "75"
#define     RESNUM      75
#define     SPACING     "C"
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



char
BDF_header           (void)
{
   printf ("STARTFONT %.1f\n"             , BDFVERSION);
   printf ("FONT -%s-%s-%s-%s-%s-"        , g_font, FAMILY, WEIGHTNM, SLANT, SETWIDTH);
   printf ("-%s-%s-%s-%s-%s"              , g_pixelsz, g_pointsz, RESX, RESY, SPACING);
   printf ("-%s-%s-%s\n"                  , AVGWIDTH, CHARSET, ENCODING);
   printf ("SIZE %s %s %s\n"              , g_pixelsz, RESX, RESY);
   printf ("FONTBOUNDINGBOX %d %d %d %d\n", g_wide, g_tall, 0, -g_descent);
   printf ("\n");
   printf ("STARTPROPERTIES %d\n"         , 23);
   printf ("FONTNAME_REGISTRY \"%s\"\n"   , REGISTRY);
   printf ("FOUNDRY \"%s\"\n"             , g_font);
   printf ("FAMILY_NAME \"%s\"\n"         , FAMILY);
   printf ("WEIGHT_NAME \"%s\"\n"         , WEIGHTNM);
   printf ("SLANT \"%s\"\n"               , SLANT);
   printf ("SETWIDTH_NAME \"%s\"\n"       , SETWIDTH);
   printf ("ADD_STYLE_NAME \"%s\"\n"      , STYLE);
   printf ("PIXEL_SIZE \"%s\"\n"          , g_pixelsz);
   printf ("POINT_SIZE \"%s\"\n"          , g_pointsz);
   printf ("RESOLUTION_X \"%s\"\n"        , RESX);
   printf ("RESOLUTION_Y \"%s\"\n"        , RESY);
   printf ("SPACING \"%s\"\n"             , SPACING);
   printf ("AVERAGE_WIDTH \"%s\"\n"       , AVGWIDTH);
   printf ("CHARSET_REGISTRY \"%s\"\n"    , CHARSET);
   printf ("CHARSET_ENCODING \"%s\"\n"    , ENCODING);
   printf ("COPYRIGHT \"%s\"\n"           , COPYRIGHT);
   printf ("CAP_HEIGHT %d\n"              , g_upper);
   printf ("X_HEIGHT %d\n"                , g_lower);
   printf ("WEIGHT %d\n"                  , g_tall);
   printf ("RESOLUTION %d\n"              , RES);
   printf ("QUAD_WIDTH %d\n"              , g_wide);
   printf ("FONT_ASCENT %d\n"             , g_ascent);
   printf ("FONT_DESCENT %d\n"            , g_descent);
   printf ("ENDPROPERTIES\n"       );
   printf ("\n");
   printf ("CHARS %d\n"                   , 256);
   printf ("\n");
   return 0;
}

char
BDF_footer           (void)
{
   printf ("ENDFONT\n");
   return 0;
}

char
BDF_rows             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   int         j           = 0;
   char       *x_hex       = "0123456789ABCDEF";
   int         x_val       = 0;
   int         x_byte      = 0;
   float       x_pixel     = 0.0;
   float       x_res       = 0.0;
   float       x_respx     = 0.0;
   int         x_swidth    =   0;
   for (i = 0; i < LEN_CHARSET; ++i) {
      x_pixel =  (float) g_wide;
      x_res   = ((float) RESNUM) / 72.0;
      x_respx = x_pixel / x_res;
      x_swidth = x_respx * 100;
      printf ("STARTCHAR %s\n"   , g_char [i].name);
      printf ("ENCODING %d\n"    , i);
      /*> printf ("pixels  %8.3f\n" , x_pixel);                                       <*/
      /*> printf ("res     %8.3f\n" , x_res);                                         <*/
      /*> printf ("px/res  %8.3f\n" , x_respx);                                       <*/
      printf ("SWIDTH %d %d\n"   , x_swidth , 0);
      printf ("DWIDTH %d %d\n"   , g_wide, 0);
      printf ("BBX %d %d %d %d\n", g_wide, g_tall, 0, -g_descent);
      printf ("BITMAP\n");
      for (j = 0; j < g_tall; ++j) {
         x_val = g_char [i].bytes [j];
         /*> printf ("%-2d  [", x_val);                                               <*/
         x_byte = x_val / 16;
         printf ("%c", x_hex [x_byte]);
         x_byte = x_val % 16;
         printf ("%c", x_hex [x_byte]);
         /*> printf ("]");                                                            <*/
         printf ("\n");
      }
      printf ("ENDCHAR\n");
      printf ("\n");
   }
   return 0;
}

int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(read source)--------------------*/
   if (a_argc < 2)  return -1;
   if      (strcmp (a_argv [1], "shrike") == 0)  share_shrike ();
   else if (strcmp (a_argv [1], "square") == 0)  share_square ();
   else    return  -2;
   rc = SHARE_read_all ();
   /*---(write out)----------------------*/
   BDF_header ();
   BDF_rows   ();
   BDF_footer   ();
   /*---(complete)-----------------------*/
   return 0;
}
