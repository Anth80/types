package types

//#include "str.h"
import "C"

func init() {
	C.init_stringmem(1e6) // 1MB
}

func String(s string) string {
	ptr := C.string_add(C.CString(s), C.int(len(s)))
	return C.GoString(ptr)
}

func Hehe() {
	C.hehe()
}

type StringRef uint32

/*
var strings []string

func init() {
	strings = make([]string, 0)
}

func GetRef(s string) StringRef {
	for i, str := range strings {
		if str == s {
			return StringRef(i)
		}
	}
	strings = append(strings, s)
}

func (r StringRef) Get() string {
	return strings[r]
}

*/
