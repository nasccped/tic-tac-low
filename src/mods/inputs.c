/* ------------------------------------------------------------------
 *
 * inputs.c
 *
 *    this file is responsible to store some functions that can get
 *    the user input by command line.
 *
 *    I know... I know. "Some in-out functions already exists Bro!".
 *    But, this current file works in a diferent way, with dynamic
 *    string sizes and etc...
 * --------------------------------------------------------------- */

// including the essential includes and the inputs header
#include "headers/_includes.h"
#include "headers/inputs.h"

/*
 * Function: get_user_response
 * ---------------------------
 * starts a kind of 'input()' Python's function but it's in C lang.
 * It will take all the pressed key from the keyboard until find a
 * '\n' character (you press Enter <Return>)
 *
 * The max size is undefined, strlen can be 10, 50, 100, etc.
 * The buffer size increases 1 by 1 every time you press a key.
 * It needs to be 'freed' at the end of the program...
 *
 * returns: string AKA char*
 *
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
