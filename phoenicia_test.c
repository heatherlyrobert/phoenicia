#include    "phoenicia.h"

char           unit_answer [LEN_FULL];

char
PROG__unit_quiet        (void)
{
   return 0;
}

char
PROG__unit_loud         (void)
{
   int         x_narg       = 2;
   char       *x_args [20]  = {"phoenicia_unit" , "@@kitchen"  };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   /*> yURG_by_name  ("kitchen"      , YURG_ON);                                      <*/
   /*> DEBUG_YGLTEX  yLOG_info     ("phoenicia" , PROG_version   ());                 <*/
   return 0;
}

char
PROG__unit_end          (void)
{
   DEBUG_YGLTEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}
