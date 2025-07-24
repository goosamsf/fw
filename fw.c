
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


  /*
   * Testing 
   *
   */
  int vec_size = DEFAULT_V_SIZE;
  word_count* fwvec = fw_vector_init();
  print_fw_vector(fwvec, vec_size);




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


