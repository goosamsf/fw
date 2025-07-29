
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
/*
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
*/

void print_comm_args(char**);
void print_usage(void);
void process(word_count ** , char* );
int cmp_int(const void*, const void *);

int main(int argc, char* argv[]){

  FILE *fp =NULL;
  int i;
  char *slash_n = argv[1];
  long topn;
  
  char *endptr;
  char *word;
  int vec_size = DEFAULT_V_SIZE;
  word_count **ht;
  word_count** newloc;
  word_count* fwvec;
  unsigned char slash_n_flag = 0;
  unsigned char top_n_flag = 0;

  if(argv[INDICATE_N] && !strcmp(slash_n, "-n")){
    slash_n_flag = 1;
  }
  if(argv[INDICATE_TOPN]){
    /* if third argument is not null */
    topn = strtol(argv[INDICATE_TOPN], &endptr, BASE_TEN);
    if(endptr == argv[INDICATE_TOPN] || errno == ERANGE){
      print_usage();
    }
    top_n_flag = 1;
  }
  /*
   * TODO : 7/29/25/ 23:50
   *  Stopped after trying to parse the command line argument.
   *  still have to figure out how to gracefully handle all the unordinary cases
   *  - topn is set to 0 if strtol convertion string is "ish10"
   *  - we also want to make sure "10-ish" is not allowed.
   *  - after that we set the right fileptr and topn , see below if elif and
   *  else.
   */

  if(slash_n_flag && top_n_flag){
    /* case 1 
     * topn is set
     * check file name is given and if given fptr = open
     *                              if not-given fptr = stdin*/
    printf("Both slash n and top n provided :\n");
  }else if(!slash_n_flag && !top_n_flag){
    /*
     * topn is set to 10
     * check if file name is given and if given fptr = open()
     *                                    not-given fptr = stdin
     */
    printf("Neither slash n and top n both provided :\n");
  }else{
    /* print usage() */
    printf("only_one provided\n");
  }

  /* curretly program should end here */
  return 0;


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
   mig2_fw_vector(ht,newloc,&vec_size);
   qsort(*newloc, vec_size, sizeof(word_count), cmp_int);
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

int cmp_int(const void* a, const void* b){
  const word_count* p1 = (const word_count*) a;
  const word_count* p2 = (const word_count*) b;

  if(p1->count != p2->count){
    return p2->count - p1->count;
  }
  return strcmp(p1->word, p2->word);
}

