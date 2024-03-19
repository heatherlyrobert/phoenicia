#include    "phoenicia.h"

char       s_print [LEN_RECD];

/*
 *  PSF  = pc screen font
 *     -- currently employed by linux kernel for console fonts
 *     -- version one PSF1 was 8-bit wide only
 *     -- version two PSF2 is variable width
 *
 *  PSF2 format (each entry is 4 bytes)
 *     -- magic number    4  byte    72 b5 4a 86
 *     -- version         32 uint    0
 *     -- header size     32 uint    32
 *     -- flags           32 uint    1 = unicode table, 0 = without
 *     -- length          32 uint    number of glyphs
 *     -- gylph size      32 uint    number of total bytes per glyph
 *     -- height          32 uint    gylph height
 *     -- width           32 uint    gylph width
 *
 *   be wary of automatic PSF creation which tweeks 7 and 9 bit into 8
 *   while saving space, it can't really be 9bit
 *
 *   one bit is one pixel, all rows are padded on right
 *
 *   000001100000  0000
 *   000011110000  0000
 *   000110011000  0000     perfect representation, quick to display
 *   001100001100  0000
 *   011000000110  0000     example 12x12 font with 4bit padding on right
 *   110000000011  0000
 *   111111111111  0000     this means two-bytes per row
 *   111111111111  0000
 *   110000000011  0000
 *   110000000011  0000
 *   110000000011  0000
 *   110000000011  0000
 *
 */

typedef  struct cPSF  tPSF;
struct cPSF {
   uint32_t    magic;     /* standard                                          */
   uint32_t    ver;       /* always 0                                          */
   uint32_t    offset;    /* offset from start of file to first glyph in bytes */
   uint32_t    config;    /* 0 defalt, 1 if unicode table                      */
   uint32_t    count;     /* number of glyphs                                  */
   uint32_t    bytes;     /* byte for entire glyph image                       */
   uint32_t    tall;      /* glyph pixel height                                */
   uint32_t    wide;      /* glyph pixel width                                 */
};

char
PSF__header             (FILE *f, char a_wide, char a_tall, char *r_bytes)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPSF        h;
   char        x_bytes     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_bytes != NULL)  *r_bytes = 0;
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_bytes   = (a_wide > 8) ? 2 : 1 ;
   /*---(load structure)-----------------*/
   h.magic   = 0x864ab572;     /* standard PSF2 magic */
   h.ver     = 0;
   h.offset  = 32;
   h.config  = 0;
   h.count   = MAX_CHARSET;
   h.bytes   = x_bytes * a_tall;
   h.tall    = a_tall;
   h.wide    = a_wide;
   /*---(write structure)----------------*/
   rc = fwrite (&h, sizeof (tPSF), 1, f);
   DEBUG_INPT    yLOG_value   ("fwrite"    , rc);
   /*---(save-back)----------------------*/
   if (r_bytes != NULL)  *r_bytes = x_bytes;
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
PSF__show_header        (char a_psffile [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         i           =    0;
   uchar       c           =    0;
   char        t           [LEN_LABEL] = "";
   int         v           =    0;
   /*---(file open)----------------------*/
   rc = FILE_open (a_psffile, 'R', NULL, NULL, &f);
   --rce;  if (rc < 0)   return "can not open";
   /*---(read header)--------------------*/
   strcpy (s_print, "");
   for (i = 0; i < 32; ++i) {
      if (i > 0 && (i % 4) == 0)  ystrlcat (s_print, "  ", LEN_RECD);
      rc = fread (&c, sizeof (uchar), 1, f);
      sprintf (t, "%02x ", c);
      ystrlcat (s_print, t, LEN_RECD);
      switch (i % 4) {
      case 0 :   v  = c;                       break;
      case 1 :   v += c * 256;                 break;
      case 2 :   v += c * 256 * 256;           break;
      case 3 :   v += c * 256 * 256 * 256;
                 if (i > 4) {
                    sprintf (t, "= %-3d ", v);
                    ystrlcat (s_print, t, LEN_RECD);
                 }
                 break;
      }
   }
   /*---(file close)---------------------*/
   rc = FILE_close (NULL, NULL, &f);
   --rce;  if (rc < 0) return "can not close";
   /*---(complete)-----------------------*/
   return s_print;
}

char
PSF__glyph              (FILE *f, uchar a_index, char a_bytes, char a_wide, char a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_bits      =    0;
   char        x, y;
   int         x_byte      =    0;
   int         x_val       =    0;
   uchar       c           =  ' ';
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("a_wide"    , a_wide);
   --rce;  if (a_wide < 6 || a_wide > 16) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("a_tall"    , a_tall);
   --rce;  if (a_tall < 6 || a_tall > 16) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT    yLOG_value   ("a_bytes"    , a_bytes);
   --rce;  if (a_bytes < 1 || a_bytes > 2) {
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write glyph)--------------------*/
   x_bits = a_bytes * 8;
   for (y = 0; y < a_tall; ++y) {
      x_byte = 0;
      for (x = 0; x < x_bits; ++x) {
         x_val = pow (2, 15 - x);
         c = g_char [a_index].image [y][x];
         if (c == '#')  x_byte += x_val;
         DEBUG_INPT    yLOG_complex ("loop"      , "%2d, %5d, %c, %5c", x, x_val, c, x_byte);
      }
      DEBUG_INPT    yLOG_value   ("x_byte"    , x_byte);
      ystrl4bin ((double) x_byte, t, 4, 'n', LEN_LABEL);
      DEBUG_INPT    yLOG_info    ("t"         , t);
      if (a_bytes == 2)  sprintf (t, "%c%c", x_byte / 256, x_byte % 256);
      else               sprintf (t, "%c", x_byte / 256);
      DEBUG_INPT    yLOG_info    ("t"         , t);
      rc = fwrite (&t, a_bytes, 1, f);
      DEBUG_INPT    yLOG_value   ("fwrite"    , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
PSF__show_glyph         (char a_psffile [LEN_PATH], uchar a_index, char a_bytes, char a_wide, char a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         x, y        =    0;
   uchar       c           [LEN_LABEL] = "";
   uchar       u           =    0;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(file open)----------------------*/
   rc = FILE_open (a_psffile, 'R', NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0)   return "can not open";
   /*---(prepare)------------------------*/
   rc = fseek (f, 32 + a_index * (a_bytes * a_tall), SEEK_SET);
   DEBUG_INPT    yLOG_value   ("fseek"     , rc);
   /*> fseek (f, 32, SEEK_SET);                                                       <*/
   /*---(read header)--------------------*/
   strcpy (s_print, "");
   for (y = 0; y < a_tall; ++y) {
      rc = fread (&c, a_bytes, 1, f);
      u = c [0];
      ystrl4bin (u, t, 2, 'n', LEN_LABEL);
      ystrlcat (s_print, t, LEN_RECD);
      DEBUG_INPT    yLOG_complex ("loop"      , "%2d, %3d, %s", y, u, t);
      if (a_bytes == 2)  {
         ystrlcat (s_print, ":", LEN_RECD);
         u = c [1];
         ystrl4bin (u, t, 2, 'n', LEN_LABEL);
         ystrlcat (s_print, t, LEN_RECD);
         DEBUG_INPT    yLOG_complex ("loop"      , "%2d, %3d, %s", y, u, t);
      }
      ystrlcat (s_print, "  ", LEN_RECD);
   }
   /*---(file close)---------------------*/
   rc = FILE_close (NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) return "can not close";
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return s_print;
}

char
PSF_make_all            (char a_psffile [LEN_PATH], char a_wide, char a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        b           =    0;
   int         i           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT    yLOG_enter   (__FUNCTION__);
   /*---(start)--------------------------*/
   yURG_msg ('>', "create PSF version of font source data...");
   /*---(file open)----------------------*/
   yURG_msg ('-', "PSF file å%sæ", a_psffile);
   rc = FILE_open (a_psffile, 'W', NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "PSF file could not be openned (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "PSF file openned successfully");
   /*---(write header)-------------------*/
   PSF__header (f, a_wide, a_tall, &b);
   DEBUG_INPT    yLOG_value   ("b"         , b);
   /*---(write all chars)----------------*/
   for (i = 0; i < MAX_CHARSET; ++i) {
      rc = PSF__glyph (f, i, b, a_wide, a_tall);
      if (rc >= 0)  ++c;
   }
   /*---(file close)---------------------*/
   rc = FILE_close (NULL, NULL, &f);
   DEBUG_INPT    yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "file could not be closed (%d)", rc);
      DEBUG_INPT    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "PSF file closed successfully");
   yURG_msg ('-', "%d characters written", c);
   /*---(complete)-----------------------*/
   DEBUG_INPT    yLOG_exit    (__FUNCTION__);
   return 0;
}








