#include "headers/inputs.h"

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
