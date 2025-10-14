#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "str.h"

struct stringmem mem;

void init_stringmem(int bank_size){
  printf("init string mem\n");
  mem.bank_size = bank_size;
  mem.banks = 0;
  mem.banks_used = 0;
  mem.free_offset = 0;}

void add_bank(){ 
  printf("add bank\n");
  mem.banks_used++;
  mem.banks = realloc(mem.banks, sizeof(void *)*mem.banks_used);
  mem.banks[mem.banks_used-1] = malloc(mem.bank_size);
  mem.free_offset = 0;
}

int32_t string_ref(char * str, int len){
  if(mem.banks == 0 || mem.bank_size - mem.free_offset < len){
    add_bank();
  }
  memcpy((char *)mem.banks[mem.banks_used-1] + mem.free_offset, str, len);
  mem.free_offset += len;
  return 42;//(char *)mem.banks[mem.banks_used-1] + mem.free_offset - len;
}


void hehe(){
  printf("%s\n", (char *)mem.banks[0]);
}