#pragma once

#include <stdint.h>
//#include "_obj/_cgo_export.h"

struct stringmem{
  void ** banks;
  int bank_size;
  int banks_used;
  int free_offset;
};

void init_stringmem(int);

void add_bank();

//char * string_add(char *, int);

void hehe();

//typedef struct { const char *p; intgo n; } _GoString_;

int32_t string_ref(char*, int);