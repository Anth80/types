#pragma once

#include <stdint.h>

void stringmem_init(int);
void stringmem_free();

uint32_t string_ref(char *, int);

int string_len(uint32_t); 

int stringmem_get_alloc();

char * ref_ptr(uint32_t);