#include    "phoenicia.h"






int
main                 (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   if (rc <  0) { PROG_shutdown (); return -1; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   if (rc <  0) { PROG_shutdown (); return -2; }
   /*---(main-loop)----------------------*/
   rc = PROG_driver   (my.run_mode);
   DEBUG_PROG   yLOG_value    ("driver"    , rc);
   /*---(wrap-up)------------------------*/
   rc = PROG_shutdown ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   /*---(complete)-----------------------*/
   return 0;
}
