/* This line should be pasted into fw.c when the whole program is tested 
 * This lines of code basically parse the command line argument and process
 * the program ( read word put it into hash table count the frequency )
 */
  return 0;
  FILE *fp =NULL;
  int i;
  int k;
  long topn;
  char *endptr;
  char *word;
  word_count **ht;
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

