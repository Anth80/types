package types

//#include <stdlib.h>
//#include "str.h"
import "C"
import "unsafe"

func init() {
	C.init_stringmem(1e6) // 1MB
}

type stringRef uint32

func StringRef(s string) stringRef {
	c_str := C.CString(s)
	ref := C.string_ref(c_str, C.int(len(s)))
	C.free(unsafe.Pointer(c_str))
	return stringRef(ref)
}

func (s stringRef) String() string {
	str_p := C.ref_ptr(C.uint(s))
	return C.GoString(str_p)
}
