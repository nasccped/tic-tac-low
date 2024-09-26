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

char* get_user_response() {

  int    cur_char                             ;
  size_t index_helper = 0                     ;
  char  *temp_string                          ,
        *result = (char *)malloc(sizeof(char));

  if (result == NULL) return NULL;

  result[index_helper] = '\0';

  while ((cur_char = getchar()) != EOF && cur_char != '\n') {

    index_helper++;
    temp_string = (char *)realloc(result, index_helper + 1);

    if (temp_string == NULL) {

      free(result);
      return NULL;
    }

    result = temp_string;

    result[index_helper - 1] = cur_char;
    result[index_helper] = '\0';
  }

  return result;
}

#endif
