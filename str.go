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
	C.init_stringmem(C.int(bank_size))
	NewStringRef("")
}

type StringRef uint32

func NewStringRef(s string) StringRef {
	c_str := C.CString(s)
	ref := C.string_ref(c_str, C.int(len(s)))
	C.free(unsafe.Pointer(c_str))
	return StringRef(ref)
}

func (s StringRef) String() string {
	str_p := C.ref_ptr(C.uint(s))
	return C.GoString(str_p)
}

func (s StringRef) Len() int {
	l := C.string_len(C.uint(s))
	return int(l)
}
