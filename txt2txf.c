#include    "font.h"

#include <GL/gl.h>                   /* main header for opengl                */
#include <GL/glx.h>                  /* for xlib/opengl integration           */

#include    <yFONT.h>
#include    <yGLTEX.h>

/*> /+ small version +/                                                               <* 
 *> short    g_gwide   =   6;                                                         <* 
 *> short    g_gtall   =  10;                                                         <* 
 *> short    g_above   =   8;                                                         <* 
 *> short    g_below   =  -2;                                                         <* 
 *> short    g_margin  =   2;                                                         <* 
 *> short    g_fwide   =   8;                                                         <* 
 *> short    g_ftall   =  12;                                                         <*/

/* 40pt version */
short    g_gwide   =  32;
short    g_gtall   =  55;
short    g_above   =  43;
short    g_below   = -12;
short    g_margin  =   2;

short    g_fwide   =   8;
short    g_ftall   =  12;

short    g_twide   =   0;
short    g_ttall   =   0;

uint        g_tex;                    /* task texture                      */
uint        g_fbo;                    /* task fbo                          */

uchar   *g_texmap  = NULL;


char
txf_header              (char *a_slot)
{
   /*---(wide)---------------------------*/
   g_fwide   =  g_gwide + g_margin;
   g_twide   =  g_fwide;            /* character plus margin to next */
   g_twide  *= 16;                  /* 16 per row      */
   g_twide  +=  4;                  /* outside margins */
   g_twide  += 16 - (g_twide % 16);  /* round up to 16  */
   /*---(tall)---------------------------*/
   g_ftall   =  g_gtall + g_margin;
   g_ttall   =  g_ftall;            /* character plus margin to next */
   g_ttall  *= 16;                  /* 16 rows         */
   g_ttall  +=  4;                  /* outside margins */
   g_ttall  += 16 - (g_ttall % 16);  /* round up to 16  */
   /*---(write header)-------------------*/
   yFONT_head_force  (a_slot, "shrike", 40, g_twide, g_ttall, g_above, g_below, g_margin, 256);
   /*---(complete)-----------------------*/
   return 0;
}

char
txf_glyph               (short n, short a_left, short a_topp)
{
   /*---(locals)-----------+-----------+-*/
   int         x, y;                   /* iterator -- gylphs                  */
   int         x_pos       =    0;
   uchar       c           =  ' ';
   uchar       v           =  ' ';
   /*---(measure all glyphs)-------------*/
   /*> printf ("\n\ncharacter %c/%3d\n", n, n);                                       <*/
   for (y = 0; y < g_ftall; ++y) {
      for (x = 0; x < g_fwide; ++x) {
         x_pos = ((a_topp + y) * g_twide) + (a_left + x);
         c = g_char [n].pretty [y][x];
         v = g_char [n].yfont  [y][x];
         g_texmap [x_pos] = v;
         /*> printf ("  %3dx %3dy    %3d %c %3d    %3dw %5dp\n", x, y, c, c, v, g_twide, x_pos);   <*/
         /*> if (g_char [n].yfont [y][x] == '#') {                                              <* 
          *>    /+> printf ("%c", '°');                                                   <+/   <* 
          *>    printf ("%3dn, %3dx, %3dy, %3dw, %5dp\n", n, x, y, g_twide, x_pos);             <* 
          *>    g_texmap [x_pos] = 255;                                                         <* 
          *>    /+> glPointSize (1.0);                                                    <+/   <* 
          *>    /+> glBegin (GL_POLYGON); {                                               <*    <* 
          *>     *>    glVertex3f (10, -10, 0);                                           <*    <* 
          *>     *>    glVertex3f (30, -10, 0);                                           <*    <* 
          *>     *>    glVertex3f (30, -30, 0);                                           <*    <* 
          *>     *>    glVertex3f (10, -30, 0);                                           <*    <* 
          *>     *> } glEnd();                                                            <+/   <* 
          *>    /+> glBegin (GL_POLYGON); {                                               <*    <* 
          *>     *>    glVertex3f (10,  30, 0);                                           <*    <* 
          *>     *>    glVertex3f (30,  30, 0);                                           <*    <* 
          *>     *>    glVertex3f (30,  10, 0);                                           <*    <* 
          *>     *>    glVertex3f (10,  10, 0);                                           <*    <* 
          *>     *> } glEnd();                                                            <+/   <* 
          *>    /+> glBegin (GL_POINTS); {                                                <*    <* 
          *>     *>    glVertex3f (a_left + x, 0 - y, 0);                                 <*    <* 
          *>     *> } glEnd();                                                            <+/   <* 
          *> /+> } else {                                                                 <*    <* 
          *>  *>    printf ("%c", g_char [n].image [y][x]);                               <+/   <* 
          *> }                                                                                  <*/
         /*---(done)------------------------*/
      }
      /*> printf ("\n");                                                              <*/
   }
   /*> printf ("\n");                                                                 <*/
   return 0;
}

char
txf_draw                (void)
{
   /*---(locals)-----------+-----------+-*/
   int         n           =      0;   /* iterator -- gylphs                  */
   int         x, y;                   /* iterator -- gylphs                  */
   int         x_pos       =      0;   /* current width                       */
   int         y_pos       =      0;   /* current height                      */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   DEBUG_INPT   yLOG_value   ("g_fwide"   , g_fwide);
   DEBUG_INPT   yLOG_value   ("g_ftall"   , g_ftall);
   /*---(measure all glyphs)-------------*/
   for (y = 0; y < 16; ++y) {
      for (x = 0; x < 16; ++x) {
         y_pos  = g_margin + 1 + (y * g_ftall);
         x_pos  = g_margin + 1 + (x * g_fwide);
         txf_glyph (n, x_pos, y_pos);
         ++n;
         /*---(done)------------------------*/
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_slot      =    0;
   /*---(read source)--------------------*/
   printf ("starting\n");
   yGLTEX_config ();
   share_shrike ();
   rc = SHARE_read_all   ();
   rc = SHARE_read_yfont ();
   /*---(write out)----------------------*/
   printf ("write header\n");
   rc = txf_header  (&x_slot);
   printf ("force index\n");
   rc    = yFONT_index_force (x_slot, g_gwide, g_gtall);
   DEBUG_GRAF   yLOG_note     ("create texture");
   g_texmap = yFONT_map_force   (x_slot);
   txf_draw  ();
   rc    = yFONT_write_force (x_slot);
   /*> printf ("create texture %4dw, %4dt\n", g_twide, g_ttall);                                <* 
    *> yGLTEX_new_font (&g_tex, &g_fbo, g_twide, g_ttall);                                      <* 
    *> DEBUG_GRAF   yLOG_note     ("setup opengl view");                                        <* 
    *> printf ("prepare to draw\n");                                                            <* 
    *> yGLTEX_draw (g_fbo, YGLTEX_TOPLEF, g_twide, g_ttall, 1.0);                               <* 
    *> printf ("draw\n");                                                                       <* 
    *> glColor4f (0.5f, 0.5f, 0.5f, 0.5f);                                                      <* 
    *> txf_draw (2, 8, 12);                                                                     <* 
    *> /+> printf ("make into png\n");                                                    <+/   <* 
    *> /+> yGLTEX_tex2png ("shrike.png", g_twide, g_ttall);                               <+/   <* 
    *> printf ("close down texture\n");                                                         <* 
    *> yGLTEX_done (g_tex);                                                                     <* 
    *> printf ("free everything\n");                                                            <* 
    *> yGLTEX_free_font (&g_tex, &g_fbo);                                                       <*/
   /*> BDF_header ();                                                                 <*/
   /*> BDF_rows   ();                                                                 <*/
   /*> BDF_footer   ();                                                               <*/
   /*---(complete)-----------------------*/
   return 0;
}
