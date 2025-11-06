#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "str.h"

struct stringmem {
    void ** banks;
    uint32_t bank_size;
    uint32_t banks_used;
    uint32_t free_offset;
    uint32_t refs_created;
    pthread_rwlock_t lock;
};

struct stringmem mem;

void stringmem_init(int bank_size) {
    mem.bank_size = bank_size;
    mem.banks = 0;
    mem.banks_used = 0;
    mem.free_offset = 0;
    mem.refs_created = 0;
    pthread_rwlock_init(&mem.lock, 0);
    string_ref("", 0);
}

void stringmem_free() {
    for(int i=0; i<mem.banks_used; i++) {
        free(mem.banks[i]);
    }
    free(mem.banks);
}

void add_bank() {
    mem.banks_used++;
    mem.banks = (void **)realloc(mem.banks, sizeof(void *)*mem.banks_used);
    mem.banks[mem.banks_used-1] = malloc(mem.bank_size);
    mem.free_offset = 0;
}

extern int64_t get_ref(char *);

extern void set_ref(char *, uint32_t, uintptr_t);

uint32_t string_ref(char * str, int len) {
    if(str == NULL) {
        str = "";
    }
    if(len >= mem.bank_size-1) {
        printf("string_ref: maximum string length exceeded: %d > %d\n", len, mem.bank_size-1);
        exit(1);
    }
    pthread_rwlock_rdlock(&mem.lock);
    int64_t ref = get_ref(str);
    if(ref >= 0) {
        pthread_rwlock_unlock(&mem.lock);
        return ref;
    }
    pthread_rwlock_unlock(&mem.lock);
    pthread_rwlock_wrlock(&mem.lock);
    ref = get_ref(str);
    if(ref >= 0) {
        pthread_rwlock_unlock(&mem.lock);
        return ref;
    }

    if(mem.banks == 0 || mem.bank_size - mem.free_offset < len+1) {
        add_bank();
    }
    uintptr_t addr_start = (uintptr_t)mem.banks[mem.banks_used-1] + mem.free_offset;
    uintptr_t addr_end = (uintptr_t)mem.banks[mem.banks_used-1] + mem.free_offset+len;

    memcpy((char *)addr_start, str, len);
    memset((char *)addr_end, 0, 1);

    mem.free_offset += len+1;

    ref = mem.refs_created;

    set_ref(str, ref, addr_start);

    mem.refs_created++;
    pthread_rwlock_unlock(&mem.lock);
    return ref;
}

int stringmem_get_alloc() {
    pthread_rwlock_rdlock(&mem.lock);
    int total = mem.banks_used * mem.bank_size;
    pthread_rwlock_unlock(&mem.lock);
    return total;
}

extern int get_len(uint32_t);

int string_len(uint32_t ref) {
    pthread_rwlock_rdlock(&mem.lock);
    int len = get_len(ref);
    pthread_rwlock_unlock(&mem.lock);
    return len;
}

extern char * ref_ptr_cc(uint32_t);

char * ref_ptr(uint32_t ref) {
    pthread_rwlock_rdlock(&mem.lock);
    char *p = ref_ptr_cc(ref);
    pthread_rwlock_unlock(&mem.lock);
    return p;
}
