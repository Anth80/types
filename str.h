#pragma once

struct stringmem{
  void ** banks;
  int bank_size;
  int banks_used;
  int free_offset;
};
/*struct stringmem{
  void *mem;
  int size;
  int used;
};*/

void init_stringmem(int);

void add_bank();

char * string_add(char *, int);

void hehe();