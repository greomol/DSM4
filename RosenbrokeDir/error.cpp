// Module error.c
// error message sender. 
// 
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 18.11.2002.

#include <stdlib.h>
#include <stdio.h>
#include "error.h"


string errlog_name;// storage for for the name of
                  // errorlog file

/* Function SendErrorMsg sends error or warning message     */
/* containing in the string diagnosis into the text file    */
/* with path defined by error_log_path.                     */
/* Parameter error_state defines what kind of message       */
/* has come. Error_state may take the following values      */
/* defined in error.h:                                      */
/* ERROR     error has  occurred ("Error:" will be printed  */
/*           before message);                               */
/* WARNING   warning has occurred ("Warning:" will be       */
/*           printed before message);                       */
/* INIT      the first message has come (the file will be   */
/*           created or rewritten)                          */
/* FINAL     the final message has come and will be saved   */
/*           in the file                                    */
/*                                                          */
/* Features:                                                */
/* If file with name defined by error_log_path can't be     */
/* opened or created SendErrorMsg skipped diagnosis.        */

void SendErrorMsg (string const &error_log_path,
                   string const &diagnosis,
                   int    error_state){
      FILE *output;

      output = (error_state == INIT)? 
               fopen (error_log_path.c_str(), "w"):
               fopen (error_log_path.c_str(), "a+");

      if (output == NULL){
         return;
      }
      switch (error_state){
      case ERROR:   fprintf (output, "Error: %s\n", diagnosis.c_str());
                    break;
      case WARNING: fprintf (output, "Warning: %s\n", diagnosis.c_str());
                    break;
      case INIT:    
      case FINAL:   fprintf (output, "%s\n", diagnosis.c_str());
                    break;
      default:      fprintf (output, "Abnormal error state\n");
                break;
      }
      fclose (output);
}
