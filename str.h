#pragma once

#include <stdint.h>

void init_stringmem(int);

void add_bank();

uint32_t string_ref(char *, int);

extern int64_t get_ref(char *);

extern void set_ref(char *, uint32_t, uintptr_t);

extern char * ref_ptr(uint32_t);