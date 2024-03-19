#include    "phoenicia.h"



tMY  my;
char      verstring    [500];



/*====================------------------------------------====================*/
/*===----                        program wide                          ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o (void) {;}

char         /*-> display command line help/usage ----[ leaf   [gc.760.000.00]*/ /*-[00.0000.012.!]-*/ /*-[--.---.---.--]-*/
PROG_help               (void)
{
   printf("\n");
   printf("s : light, clean, fast, and aesthetic console-based spreadsheet\n");
   printf("\n");
   printf("usage : s [urgents] [options]\n");
   printf("\n");
   printf("standard urgents -- debugging tracing/information\n");
   printf("   startup---  ---------------------------\n");
   printf("   @c          command line arguments\n");
   printf("   @x          setup and teardown\n");
   printf("   @i          file input\n");
   printf("   process---  ---------------------------\n");
   printf("   @e          xwindows events/input\n");
   printf("   @g          ncurses/opengl graphics\n");
   printf("   @p          processing\n");
   printf("   @d          data structures/mgmt\n");
   printf("   @a          programming api\n");
   printf("   wrapup----  ---------------------------\n");
   printf("   @o          file output\n");
   printf("\n");
   printf("specific urgents -- debugging tracing/information\n");
   printf("   @@averages  conversion of raw to basic to average points\n");
   printf("   @@circles   circle identificition and marking\n");
   printf("   @@curves    curve marking\n");
   printf("   @@keys      key point identification and marking\n");
   printf("   @@deps      dependency creation and processing\n");
   printf("\n");
   exit(0);
}

char*        /*-> return library versio --------------[ leaf   [gs.420.012.00]*/ /*-[00.0000.012.!]-*/ /*-[--.---.---.--]-*/
PROG_version            (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   ystrlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   ystrlcpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   ystrlcpy (t, "[cbang      ]", 15);
#else
   ystrlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT________o (void) {;}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP________o (void) {;}

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__init         (int a_argc, char *a_argv[])
{
   char        rce         =  -10;
   char        rc          =    0;
   /*---(log header)---------------------*/
   DEBUG_PROG   yLOG_info     ("purpose"   , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake"  , P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage"  , P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery"   , P_IMAGERY);
   DEBUG_PROG   yLOG_info     ("phoenicia" , PROG_version      ());
   /*> DEBUG_PROG   yLOG_info     ("yLOG"      , yLOGS_version     ());               <*/
   DEBUG_PROG   yLOG_info     ("yURG"      , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("ySTR"      , ySTR_version      ());
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   /*---(code)---------------------------*/
   my.run_loud = RUNMODE_QUIET;
   my.run_mode = RUNMODE_CHECK;
   ystrlcpy (my.run_file, "", LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   return 0;
}

char         /*-> process the command line args ------[ ------ [gz.952.251.B4]*/ /*-[01.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__args              (int a_argc, char *a_argv[])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char       *a           = NULL;
   char       *b           = NULL;
   int         x_total     =    0;
   int         x_args      =    0;
   char        x_name      [LEN_FULL]   = "";
   char        t           [LEN_FULL]   = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(set up args)-----------------*/
      DEBUG_ARGS  yLOG_value   ("check----" , i);
      a = a_argv [i];
      if (i + 1 < a_argc)  b = a_argv [i + 1];
      else                 b = NULL;
      DEBUG_ARGS  yLOG_info    ("a"         , a);
      DEBUG_ARGS  yLOG_info    ("b"         , b);
      ++x_total;
      /*---(filter)----------------------*/
      if (a[0] == '@') {
         DEBUG_ARGS  yLOG_note    ("skipped urgent");
         continue;
      }
      /*---(local)-----------------------*/
      ++x_args;
      if      (strcmp (a, "-v"             ) == 0)    PROG_version ();
      else if (strcmp (a, "--version"      ) == 0)    PROG_version ();
      else if (strcmp (a, "-h"             ) == 0)    PROG_help    ();
      else if (strcmp (a, "--help"         ) == 0)    PROG_help    ();
      else if (strcmp (a, "--charmap"      ) == 0)  { my.run_mode = RUNMODE_CHARMAP;   my.run_loud = RUNMODE_QUIET;   }
      /*---(prefixes)--------------------*/
      else if (strcmp (a, "--square"       ) == 0)    ystrlcpy (my.run_file, RUNFILE_SQUARE, LEN_PATH);
      else if (strcmp (a, "--shrike"       ) == 0)    ystrlcpy (my.run_file, RUNFILE_SHRIKE, LEN_PATH);
      else if (strcmp (a, "--check"        ) == 0)  { my.run_mode = RUNMODE_CHECK;     my.run_loud = RUNMODE_QUIET;   }
      else if (strcmp (a, "--ccheck"       ) == 0)  { my.run_mode = RUNMODE_CHECK;     my.run_loud = RUNMODE_CONFIRM; }
      else if (strcmp (a, "--vcheck"       ) == 0)  { my.run_mode = RUNMODE_CHECK;     my.run_loud = RUNMODE_VERBOSE; }
      /*---(actions)---------------------*/
      else if (strcmp (a, "--txt2bdf"      ) == 0)  { my.run_mode = RUNMODE_TXT2BDF;   my.run_loud = RUNMODE_QUIET;   }
      else if (strcmp (a, "--ctxt2bdf"     ) == 0)  { my.run_mode = RUNMODE_TXT2BDF;   my.run_loud = RUNMODE_CONFIRM; }
      else if (strcmp (a, "--vtxt2bdf"     ) == 0)  { my.run_mode = RUNMODE_TXT2BDF;   my.run_loud = RUNMODE_VERBOSE; }
      else if (strcmp (a, "--txt2psf"      ) == 0)  { my.run_mode = RUNMODE_TXT2PSF;   my.run_loud = RUNMODE_QUIET;   }
      else if (strcmp (a, "--ctxt2psf"     ) == 0)  { my.run_mode = RUNMODE_TXT2PSF;   my.run_loud = RUNMODE_CONFIRM; }
      else if (strcmp (a, "--vtxt2psf"     ) == 0)  { my.run_mode = RUNMODE_TXT2PSF;   my.run_loud = RUNMODE_VERBOSE; }
      /*---(other)-----------------------*/
      else {
         DEBUG_PROG   yLOG_info     ("option"    , a);
         DEBUG_PROG   yLOG_note     ("unrecognized option requested");
         DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
      DEBUG_PROG  yLOG_exit  (__FUNCTION__);
      return 0;
   }
   DEBUG_ARGS  yLOG_char   ("run_mode"  , my.run_mode);
   if (my.run_mode == RUNMODE_CHARMAP) {
      DEBUG_ARGS  yLOG_note   ("called for charmap");
      DEBUG_PROG  yLOG_exit  (__FUNCTION__);
      return 0;
   }
   DEBUG_ARGS  yLOG_info   ("run_file"  , my.run_file);
   --rce;  if (strcmp (my.run_file, "") == 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (my.bdf_file, my.run_file, LEN_PATH);
   l = strlen (my.bdf_file);
   strcpy (my.bdf_file + l - 3, "bdf");
   DEBUG_ARGS  yLOG_info   ("bdf_file"  , my.bdf_file);
   ystrlcpy (my.psf_file, my.run_file, LEN_PATH);
   l = strlen (my.psf_file);
   strcpy (my.psf_file + l - 3, "psf");
   DEBUG_ARGS  yLOG_info   ("psf_file"  , my.psf_file);
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}

char         /*-> initialize program and variables ---[ ------ [gz.741.041.07]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__begin             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program execution                     ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION______o (void) {;}

char
PROG_driver             (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(adjust verbosity)---------------*/
   if (my.run_loud == RUNMODE_VERBOSE) {
      yURG_msg_live ();
      yURG_err_live ();
      yURG_msg ('>', P_ONELINE);
   }
   /*---(run appropriate functions)------*/
   switch (a_mode) {
   case RUNMODE_CHARMAP   :
      charmap_main ();
      break;
   case RUNMODE_CHECK   :
      rc = TXT_get_all ('y', my.run_file);
      break;
   case RUNMODE_TXT2BDF :
      rc = TXT_get_all ('y', my.run_file);
      if (rc >= 0)  rc = BDF_make_all (my.bdf_file, g_title, g_wide, g_tall, g_ascent, g_descent, g_upper, g_lower);
      break;
   case RUNMODE_TXT2PSF :
      rc = TXT_get_all ('y', my.run_file);
      if (rc >= 0)  rc = PSF_make_all (my.psf_file, g_wide, g_tall);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN_______o (void) {;}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG__end            (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_END);
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}



