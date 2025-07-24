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

void mig2_fw_vector(word_count**ht, word_count **v, int* l){
  /* Hash Table's contents will be migrated into the 'v', which is
   * dynamically allocated contiguous data structure so that it can be
   * sorted easily.
   */
  int i;
  int vindex=0;
  int v_size = DEFAULT_V_SIZE;
  word_count* newloc = *v;
  word_count* curr;
  for(i = 0; i < HASH_SIZE; i++){
    if(ht[i]){
      /* If the bucket is filled with something */
      curr = ht[i];
      while(curr){
        memcpy(&newloc[vindex++], curr, sizeof(word_count));
        if(vindex != 1 && vindex % (DEFAULT_V_SIZE-1) == 0){
          /* Realloc */
          v_size += DEFAULT_V_SIZE;
          if((newloc = realloc(newloc, sizeof(word_count)* v_size)) == NULL){
            perror("REALLOC_MIG2");
            exit(-1);
          }
          /* Should I memset to 0 for remaining portion */
        }
        curr = curr->next;
      }
    }
  }
  /* Update the address of dynamic array */
  *v = newloc;
  *l = vindex;
}
