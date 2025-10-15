#pragma once

#include <stdint.h>

void init_stringmem(int);

void add_bank();

uint32_t string_ref(char *, int);

int64_t get_ref(char *);

void set_ref(char *, uint32_t, uintptr_t);

char * ref_ptr(uint32_t);