package types

//#include <stdlib.h>
//#include <string.h>
//#include "str.h"
import "C"
import "unsafe"

const (
	StringRefDefault = StringRef(0)
)

func init() {
	C.init_stringmem(1e6) // 1MB
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
