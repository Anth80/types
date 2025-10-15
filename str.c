#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "str.h"

struct stringmem{
  void ** banks;
  uint32_t bank_size;
  uint32_t banks_used;
  uint32_t free_offset;
  uint32_t refs_created;
};

struct stringmem mem;

void init_stringmem(int bank_size){
  mem.bank_size = bank_size;
  mem.banks = 0;
  mem.banks_used = 0;
  mem.free_offset = 0;
  mem.refs_created = 0;
}

void add_bank(){ 
  mem.banks_used++;
  mem.banks = realloc(mem.banks, sizeof(void *)*mem.banks_used);
  mem.banks[mem.banks_used-1] = malloc(mem.bank_size);
  mem.free_offset = 0;
}

uint32_t string_ref(char * str, int len){
  int64_t ref = get_ref(str);
  if(ref >= 0) {
    return ref;
  }
  uint32_t ref2 = ref;

  if(mem.banks == 0 || mem.bank_size - mem.free_offset < len+1){
    add_bank();
  }
  uintptr_t addr = (uintptr_t)&mem.banks[mem.banks_used-1] + mem.free_offset;
  
  memcpy((char *)addr, str, len+1);
  mem.free_offset += len+1;

  ref = mem.refs_created;
  
  set_ref(str, ref, addr);
  
  mem.refs_created++;
  return ref;
}