
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<time.h>

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
  
  char *endptr = NULL;
  char *word;
  int vec_size = DEFAULT_V_SIZE;

  word_count **ht;
  word_count** newloc;
  word_count* fwvec;

  unsigned char slash_n_flag = 0;
  unsigned char top_n_flag = 0;
  double cpu_time_used;
  clock_t start,end;
  start = clock(); 

  (void) ht;
  (void) newloc;
  (void) fwvec;
  (void) vec_size;
  (void) topn;

  if(argv[INDICATE_N] && !strcmp(slash_n, "-n")){
    slash_n_flag = 1;
    topn = strtol(argv[INDICATE_TOPN], &endptr, BASE_TEN);
    if(endptr && *endptr != '\0'){
      print_usage();
    }
    if(endptr == argv[INDICATE_TOPN] || errno == ERANGE){
      print_usage();
    }
    top_n_flag = 1;
  }else{
    topn = 10;
  }

  if(slash_n_flag && top_n_flag){
    i = 3;
  }else if(!slash_n_flag && !top_n_flag){
    i = 1;
    /* printf("Neither slash n and top n both provided :\n"); */
  }else{
    printf("only_one provided , shouldn't be it, something wrong\n");
    print_usage();
  }
  
  if(!argv[i]){
    /* fp should be set to stdin */
    fp = stdin;
    printf("fp is set to stdin , you will fix this later\n");
    printf("Terminating this program ...\n");
    return 0;
  }

  ht = ds_init();
  ds_print_ht(ht);

  /* curretly program should end here */
  for(; argv[i] != NULL; i++){

    if((fp = fopen(argv[i], "r")) == NULL){
      perror(argv[i]);
      continue;
    }
    /*printf("Processing file name : %s\n", argv[i]); */
    while(!feof(fp)){
      word = read_word(fp);
      if(word){
        /*printf("Beginning word : %s : ",word); */
        process(ht,word);
      }
    }
  }
  /*printf("File Opend!\n"); */
  /* FILE CLOSE */
  fclose(fp);
  /*printf("And Closed !\n"); */

  fwvec = fw_vector_init(); 
  newloc = &fwvec; 
  mig2_fw_vector(ht,newloc,&vec_size);
  qsort(*newloc, vec_size, sizeof(word_count), cmp_int);
  /*printf("Done upto here \n"); */
  print_fw_vector(*newloc, vec_size, topn); 

  end = clock(); 
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Execution time: %f seconds\n", cpu_time_used);


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

