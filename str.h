#pragma once

#include <stdint.h>

void init_stringmem(int);

uint32_t string_ref(char *, int);

int string_len(uint32_t); 

extern char * ref_ptr(uint32_t);