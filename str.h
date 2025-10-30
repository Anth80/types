#pragma once

#include <stdint.h>

void init_stringmem(int);

uint32_t string_ref(char *, int);

int string_len(uint32_t); 

int stringmem_get_alloc();

extern char * ref_ptr(uint32_t);