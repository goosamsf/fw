#ifndef WORDCOUNT_H
#define WORDCOUNT_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define HASH_SIZE 10017

typedef struct word_count{

  int count; 
  char * word;
  struct word_count *next;
  
} word_count;

word_count **ds_init(void);
word_count* create_node(const char * );
word_count * check_existence(const char *str, word_count **ht, int *i);
void ds_print_ht(word_count**);
void ds_print_node(word_count*);
unsigned long djb2(const char *);
int hash(const char *);
void increment_count(word_count*);
void node_append(word_count **, const char *);
void node_traversal(word_count*);



/*
 * Requirements
 *  define struct first :
 *    struct has two values
 *    cnt : count for the word,
 *    word :  char *
 *  init : create datastructure
 *  close : close and deallocate all the dynamically created memory
 *  add : add found word
 *  hash : hash word
 *
 * if word is found
 *  1. first hash that word --> get some number 
 *  2. htable[that_number] = word
 *
 */
 
#endif
