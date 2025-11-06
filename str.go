package types

import (
	"os"
	"strconv"
	"unsafe"
)

//#include <stdlib.h>
//#include <string.h>
//#include "str.h"
import "C"

const (
	StringRefDefault = StringRef(0)
)

func init() {
	var bank_size int = 1e6 // 1 MB
	if os.Getenv("STRINGREF_BANK_SIZE") != "" {
		if v, err := strconv.Atoi(os.Getenv("STRINGREF_BANK_SIZE")); err == nil {
			bank_size = v
		} else {
			panic("invalid STRINGREF_BANK_SIZE")
		}
	}
	C.stringmem_init(C.int(bank_size))
}

type stringStruct struct {
	str unsafe.Pointer
	len int
}

type StringRef uint32

func NewStringRef(s string) StringRef {
	c_str := C.CString(s)
	ref := C.string_ref(c_str, C.int(len(s)))
	C.free(unsafe.Pointer(c_str))
	//&ss := *(*stringStruct)(unsafe.Pointer(&s))
	//ref := C.string_ref((*C.char)(ss.str), C.int(ss.len))
	return StringRef(ref)
}

func NewStringRefFromBytes(bytes []byte, len int) StringRef {
	ss := *(*stringStruct)(unsafe.Pointer(&bytes))
	ref := C.string_ref((*C.char)(ss.str), C.int(len))
	return StringRef(ref)
}

func (s StringRef) String() string {
	str_p := C.ref_ptr(C.uint(s))
	ss := stringStruct{str: unsafe.Pointer(str_p), len: int(C.strlen(str_p))}
	str := *(*string)(unsafe.Pointer(&ss))
	return str
}

func (s StringRef) Len() int {
	l := C.string_len(C.uint(s))
	return int(l)
}

func GetAlloc() int {
	l := C.stringmem_get_alloc()
	return int(l)
}

func Close() {
	C.stringmem_free()
}
