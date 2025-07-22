#include "fw_ds.h"

/*
typedef struct {
  int count; 
  char * word;
  struct word_count *next;
  
} word_count;
*/


/* ds_init() 
 *
 * what does it do? 
 *  args : void
 *  ret val : pointer to begining of the array
 *  create an array of pointer to "word_count" and null-processing
 *
 *
 * */

word_count** ds_init(void) {
  /* dynamically allocate the array 
   * size , 
   */
  int i;
  word_count** ret;
  if((ret = malloc(sizeof(word_count*) * HASH_SIZE)) == NULL){
    perror("malloc");
    exit(-1);
  }
  for(i =0; i< HASH_SIZE; i++){
    ret[i] = NULL;
  }
  return ret;
}

word_count* create_node(const char * word ){
  /* 
   * What it does:
   * 1. allocate dynamiccally created node
   * 2. initialize the count value as 1
   * 3. initialize the word value as "word" in word
   * 4. initialize the next value as null
   * 4. return pointer to that dynamically allocated part
   */
  int len;
  word_count *ret;
  if((ret = malloc(sizeof(word_count))) == NULL) {
    perror("Malloc");
    exit(-1);
  }
  len = strlen(word);
  ret->count = 1;
  ret->word = strndup(word, len);
  if(errno == ENOMEM){
    perror("strdup");
    exit(-1);
  }

  ret->next = NULL;

  return ret; 
}


void ds_print_ht(word_count** arr){
  int i;
  word_count *node;
  word_count *curr;
  for(i = 0; i < HASH_SIZE; i++){
  /*    
    if(i == 30){
      break;
    }

 */   
    node = arr[i];
    curr = node;
    if(!node){
      continue; 
      /* only print none -null */
    }

    ds_print_node(curr);

  }
}

void ds_print_node(word_count* node){
  word_count* it;
  it = node;
  while(it){
    printf("addr : %p: [ %s, %d, %p ] ",(void*)it, it->word, it->count,(void*)it->next);
    if(! it->next){
      printf("-----> NULL\n");
    }
    it = it->next;
    printf("\n  -->");
  }
}

unsigned long djb2(const char* str){
  unsigned long hash = 5381;
  int c;
  while((c = *str++)) {
    hash =((hash << 5) + hash) + c;
  }
  return hash;
}

int hash(const char *str){
  unsigned long raw = djb2(str);
  int range = HASH_SIZE-1;
  return raw % range;

}

word_count * check_existence(const char *str, word_count **ht, int *i){
  /* if found return its address
   * otherwise it reuturn NULL;
   */
  int index;
  word_count *node;
  word_count *curr;
  index = hash(str);
  *i = index;
  node = ht[index];
  curr = node;
  while(curr){
    if(!strcmp(curr->word, str)){
      /* found */
      printf("found in index %d\n",index);
      return curr;
    }
    curr = curr->next;
  }
  printf("Not Found \n");
  return NULL;
}

void increment_count(word_count* node){
  node->count++ ;
}

void node_append(word_count **node_at, const char * word){
  /* node_at will be given as following form :
   * ht[hash[index]] meaning : append function should check if the room is
   * taken 
   */
  word_count *node;
  word_count *curr = *node_at;
  node = create_node(word);
  if(!(*node_at)){ 
    *node_at = node;
    return;
  }
  while(curr && curr->next) {
    curr = curr->next;
  }
  curr->next = node;
}

void node_traversal(word_count* node){
  word_count* curr = node;
  while(curr){
    printf("%s : %d" ,curr->word, curr->count);
    if(curr->next){
      printf("\n  --> ");
    }
    curr = curr->next;
  }
  printf("\n");
}
/* Node Append Test cases */
/*
 * 1. When appending at the top of the list
 * 2. When appending at the end of the list
 * ( There is no case for adding in the middle )
 * Test function should do :
 * 1. Read Bunch of words
 * 2. put it in the hash table (most likely at the top of the list )
 *
 */


