package types

//#include <stdlib.h>
//#include "str.h"
import "C"
import "unsafe"

func init() {
	C.init_stringmem(10)
	//C.init_stringmem(1e6) // 1MB
}

type stringRef uint32

func StringRef(s string) stringRef {
	c_str := C.CString(s)
	ref := C.string_ref(c_str, C.int(len(s)))
	C.free(unsafe.Pointer(c_str))
	return stringRef(ref)
}

//#//go:noescape
//#func string_ref(*C.char, C.int) C.uint

/*func String(s string) string {
	ptr := C.string_add(C.CString(s), C.int(len(s)))
	return C.GoString(ptr)
}*/

func Hehe() {
	C.hehe()
}
