
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include"fw_ds.h"
#include"fw_read.h"
#include"fw_vector.h"

#define INDICATE_N 1
#define INDICATE_TOPN 2
#define BASE_TEN 10
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#pragma clang diagnostic ignored "-Wempty-translation-unit"

void print_comm_args(char**);
void print_usage(void);
void process(word_count ** , char* );

int main(int argc, char* argv[]){

  FILE *fp =NULL;
  int i;
  long topn;
  char *endptr;
  char *word;
  int vec_size = DEFAULT_V_SIZE;
  word_count **ht;
  word_count** newloc;
  word_count* fwvec;

  /* VECTOR Feature */
/*   word_count* fwvec = fw_vector_init(); */
/*   newloc = &fwvec; */
/*   /mig2_fw_vector(ht,) */
/*   print_fw_vector(fwvec, vec_size); */

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

    /* Initialize hash table for the word */
    ht = ds_init();
    ds_print_ht(ht);

    if(!argv[INDICATE_TOPN + 1]){
      /* -n and number is rightly presented but file name is not present */
      /* set fp to stdin */
      fp = stdin;

      while(!feof(fp)) {
        word = read_word(fp);
        puts(word);
      }
    }

    for(; argv[i] != NULL; i++){

      if((fp = fopen(argv[i], "r")) == NULL){
        perror(argv[i]);
        continue;
      }
      printf("Processing file name : %s\n", argv[i]);
      while(!feof(fp)){
        word = read_word(fp);
        if(word){
          printf("Beginning word : %s : ",word);
          process(ht,word);
        }
      }
    }
    printf("File Opend!\n");
    /* FILE CLOSE */
    fclose(fp);
    printf("And Closed !\n");
  } /* braces for checking the number of arguments is greater than 1. */ 

  /*
  for(k = 0; k< HASH_SIZE; k++){
    if(ht[k]){
      node_traversal(ht[k]);
    }
  }
  node_destructor(ht);
  for(k = 0; k< HASH_SIZE; k++){
    if(ht[k]){
      node_traversal(ht[k]);
    }
  }
  */
  
   fwvec = fw_vector_init(); 
   newloc = &fwvec; 
   mig2_fw_vector(ht,newloc,vec_size);
   printf("Done upto here \n");
   print_fw_vector(*newloc, vec_size); 



  return 0;

}/* braces that main function end */


void process(word_count **ht, char* word){
  /* what process(ht) does :
   * check if word exist
   *   if EXIST? -- > Increment the counter in the node
   *   if NOT? --> Create a node and append it at the end of chaining hash table
   */
  int i;
  word_count* p;
  if((p=check_existence(word, ht, &i)) != NULL){
    /* if word found , */
    increment_count(p);
  }else {
    /* if word not found */
    node_append(&ht[i],word);

  }
}

void print_usage(void){
  /* This function handles giving usage message whenever user input is not
   * valid. 
   */
  fprintf(stderr, "fw [-n num] [ file1 [ file 2 ... ] ]\n");
  exit(-1);
}


void print_comm_args(char *t[]){
  /* 
   * For DEBUG purpose :
   *  - How to iterate over string array in C ?
   */
  int i;
  for(i = 1; t[i] != NULL; i++){
    printf("%s ", t[i]);
  }
}


