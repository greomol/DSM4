#include <string>
using namespace std;

extern string errlog_name;

#define INIT    -1 /* the first message has come (errorlog  */
                   /* file will be created or rewritten)    */

#define WARNING  0 /* warning has occurred ("Warning:" will */
                   /* be printed before message)            */

#define ERROR    1 /* error has  occurred ("Error:" will be */
                   /* printed before message)               */

#define FINAL    2 /* the final message has come and will   */
                   /* will be saved in the errorlog file    */


/* Function SendErrorMsg sends error or warning message     */
/* containing in the string diagnosis into the text file    */
/* with path defined by error_log_path.                     */
/* Parameter error_state defines what kind of message       */
/* has come.                                                */
/*                                                          */
/* Features:                                                */
/* If file with name defined by error_log_path can't be     */
/* opened or created SendErrorMsg skipped diagnosis.        */

void SendErrorMsg (string const &error_log_path,
                   string const &diagnosis,
                   int    error_state);
