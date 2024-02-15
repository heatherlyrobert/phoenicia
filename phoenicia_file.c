#include    "phoenicia.h"


char
FILE_open               (char a_name [LEN_PATH], char a_access, char r_name [LEN_PATH], char *r_mode, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   FILE       *f           = NULL;
   char        x_access    [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_FILE    yLOG_warn    ("file pointer (r_file) can not be null");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file != NULL) {
      DEBUG_FILE    yLOG_warn    ("file appears already open");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_file  != NULL)  *r_file = NULL;
   if (r_mode  != NULL)  *r_mode = '-';
   /*---(secondary defense)--------------*/
   DEBUG_FILE    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_FILE    yLOG_warn    ("file name (a_name) can not be null or empty");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE    yLOG_info    ("a_name"    , a_name);
   x_len = strlen (a_name);
   DEBUG_FILE    yLOG_point   ("x_len"     , x_len);
   --rce;  if (x_len < 5) {
      DEBUG_FILE    yLOG_warn    ("file (a_name) is too short ( < 5 chars)");
      DEBUG_FILE    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(check access)-------------------*/
   DEBUG_FILE    yLOG_char    ("a_access"  , a_access);
   --rce;  switch (a_access) {
   case 'r' :   strcpy (x_access, "rt");   break;
   case 'w' :   strcpy (x_access, "wt");   break;
   case 'R' :   strcpy (x_access, "rb");   break;
   case 'W' :   strcpy (x_access, "wb");   break;
   default  :
                DEBUG_FILE    yLOG_warn    ("access request not understood");
                DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
                return rce;
   }
   DEBUG_FILE    yLOG_info    ("x_access"  , x_access);
   /*---(open)---------------------------*/
   f = fopen (a_name, x_access);
   DEBUG_FILE    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_FILE    yLOG_warn    ("file could not be openned");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save·back)----------------------*/
   DEBUG_FILE    yLOG_note    ("saving back to return arguments");
   if (r_name  != NULL)  ystrlcpy (r_name, a_name, LEN_HUND);
   if (r_file  != NULL)  *r_file = f;
   if (r_mode  != NULL)  *r_mode = a_access;
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE_close              (char r_name [LEN_PATH], char *r_mode, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file == NULL) {
      DEBUG_FILE    yLOG_note    ("file not open");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   fflush (*r_file);
   rc = fclose (*r_file);
   DEBUG_FILE    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_FILE    yLOG_warn    ("file could not be closed");
      DEBUG_FILE    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_file  != NULL)  *r_file = NULL;
   if (r_mode  != NULL)  *r_mode = '-';
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return 0;
}
