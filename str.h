#pragma once

#include <stdint.h>

void init_stringmem(int);

uint32_t string_ref(char *, int);

extern char * ref_ptr(uint32_t);