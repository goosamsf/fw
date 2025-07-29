#include "fw_ds.h"
char *strndup(const char *, size_t );

word_count** ds_init(void) {
  /* 
   * This function initializes the HASH TABLE(array of word_count* )
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
   *  - allocate dynamiccally created node
   *  - initialize the count value as 1
   *  - initialize the word value as "word" in word
   *  - initialize the next value as null
   *  - return the address of the node that has been just created. 
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
    node = arr[i];
    curr = node;
    if(!node){
      /* only print if non-null */
      continue; 
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
  /* WHAT it DOES:
   *  - Compute hash with 'str' --> int
   *  - Update i ; i is ptr to integer that's defined upper stack. 
   *    (we update i so that when str is not found, else statement can use
   *    i value to access right bucket.)
   *    - IF found, return the address of the node.
   *    -       Or, return NULL
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
  /* Access the node with the given address and increment the counter */
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
  /* For Debugging Purpose */
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

void node_destructor(word_count** ht){
  /* This function will be executed at the end of main so that we properly
   * handles and follow good practice for memory usage 
   * Basically, for all bucket in the hash map traverse every single node
   * including the one lineked together due to avoidence of collison(if any)
   * Free every single dynamically allocated memory.
   * Notice the strdup should be taken care too.
   */
  
  int i;
  word_count* curr;
  word_count* prev;
  for(i = 0; i< HASH_SIZE; i++){
    curr = ht[i];
    prev = NULL;
    while(curr){
      prev = curr;
      curr = curr->next;
      free(prev->word);
      free(prev);
    }
    ht[i] = NULL;
  }
}


