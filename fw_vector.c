#pragma clang diagnostic ignored "-Wempty-translation-unit"


#include "fw_ds.h"
#include "fw_vector.h"


word_count* fw_vector_init(void){
  /* What this does: 
   * Create dynamically allocated area using malloc 
   * its default size is 64 as it defined up above.
   * Ensure all data is initialized to 0
   *
   * return address of created data structure
   */
  word_count* ret;
  if((ret = (word_count*)malloc(DEFAULT_V_SIZE * sizeof(word_count))) == NULL){
    perror("MALLOC_FW_VECTOR_C");
    exit(-1);
  }
  memset(ret, 0 , sizeof(word_count) * DEFAULT_V_SIZE);
  return ret;
}

void print_fw_vector(word_count* v, int l){
  /* This Traverse the array and print every single element in the array */
  int i;
  for(i=0; i<l; i++){
    printf("%d :[ %s,%d ]\n", i,v[i].word , v[i].count);
  }
  printf("Traverse done.\n");
}
