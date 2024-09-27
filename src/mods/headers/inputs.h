#ifndef _INPUTS_H_
#define _INPUTS_H_

// if <stdlib.h> isn't already imported
#ifndef _STDLIB_H_
  #include <stdlib.h>
#endif


// if <stdio.h> isn't already imported
#ifndef _STDIO_H_
  #include <stdio.h>
#endif

// if <ctype.h> isn't already imported
#ifndef _CTYPE_H_
  #include <ctype.h>
#endif

/*
This function returns a String (char*) by user's command line
response
*/

char* get_user_response();

#endif
