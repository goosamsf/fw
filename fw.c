
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define INDICATE_N 1
#define INDICATE_TOPN 2
#define BASE_TEN 10
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"

void print_comm_args(char**);
void print_usage(void);

int main(int argc, char* argv[]){


  FILE *fp;
  int i;
  long topn;
  char *endptr;

  if(argc > 1){
    /* meaning that file-name is likely provided. */

    if(!strcmp(argv[INDICATE_N], "-n")){
      /* meaning that -n is provided  in argv[1] */
      topn = strtol(argv[INDICATE_TOPN], &endptr, BASE_TEN);
      if(endptr == argv[INDICATE_TOPN] || errno == ERANGE ){
        /* Some problem getting from strtol */
        print_usage();
      }
      /* ./fw -n <some_number> is provided */
      printf("topn is set %ld\n", topn);
      i = 3;
    }else{
      /* -n is not provided so we set n value as 10 */
      topn = 10;
      i = 1;
      printf("topn is set %ld\n", topn);
    }

    if(!argv[INDICATE_TOPN + 1]){
      /* -n and number is rightly presented but file name is not present */
      /* print usage*/
      print_usage();
    }

    for(; argv[i] != NULL; i++){

      if((fp = fopen(argv[i], "r")) == NULL){
        perror(argv[i]);
        continue;
      }
  }

  /* 
   * How to pass char * argv[] to a function call?
   * and how is different from passing some pointer related arguments?
   * like **argv
   */

    /* Entry point for Reading a word processing */
    /* readword is what ? 
     *  - return value : nothing
     *  - arguments : take a FILE pointer
     *  - Does what 
     *    - process from the FILE pointer and read word and store it into a
     *    data structure
     *  - Order 
     *    getchar to read character ->
     *    if encounter something that's not a character
     *      that is a word and takes that word and put it into a data
     *      structure. do until EOF
     *
     *    if EOF is encountered, get out of the word processing and go to
     *    the next file. 
     *
     *
     *
     */

    
    printf("File Opend!\n");

    /* FILE CLOSE */
    fclose(fp);
    printf("And Closed !\n");
  }


  /* print_comm_args(argv); */


  /*
   *  Order of this project 
   *  - Pare the command line argument 
   *    - What argument can be made?
   *      - 1. nothing -- > generate error message
   *      - 2. 1 word --> open that file 
   *                          process that file
   *                          or
   *                          Generate Error message
   *
   *      - 3. 
   *
   */

  return 0;

}

void print_usage(void){
  fprintf(stderr, "fw [-n num] [ file1 [ file 2 ... ] ]\n");
  exit(-1);
}


void print_comm_args(char *t[]){
  int i;
  /* 
   * How to iterate over string array in C ?
   */
  for(i = 1; t[i] != NULL; i++){
    printf("%s ", t[i]);
  }

}


