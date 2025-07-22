#include "fw_read.h"


char *read_word(FILE *file){
  char *wp = NULL ;
  int i = 0;
  int retval = 0;
  if ((wp = malloc(DEFAULT_BUFFER)) == NULL){
    perror("MALLOC"); 
    exit(0);
  }
  
  while((retval = getc(file)) != EOF){
    /* 
     * word is defined as following :
     * --> string of alphabetic character delimeted by something that
     *     is not.
     *
     */
    if(!isalpha(retval)){
      /* Run in to a character that is not alphabetic */
      wp[i] = '\0';
      if(strlen(wp) == 0){
        /* You have to check if you have to return with nothing
         * returning nothing is not meaningful so you have to keep reading
         * to return some word.
         */
        continue;
      }
      return wp;
    }
    wp[i++] = tolower(retval); 
    if(i % (DEFAULT_BUFFER-2) == 0) {
      if((wp = realloc(wp, i + 2 + DEFAULT_BUFFER)) == NULL) {
        perror("Malloc");
        exit(0);
      }
    }
  }


  return NULL;
  /* You're my sunshine.\nHello World, this is Jun from Calpoly.\n*/

}
