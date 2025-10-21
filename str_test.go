package types

import (
	"runtime"
	"strconv"
	"sync"
	"testing"
)

var once sync.Once

func setup() {
	once.Do(func() {
		var wg sync.WaitGroup
		n := runtime.NumCPU()
		for i := 0; i < n; i++ {
			wg.Add(1)
			i := i
			go func() {
				for j := i; j < 1e6; j += n {
					s := strconv.Itoa(j)
					_ = NewStringRef(s)
				}
				wg.Done()
			}()
		}
		wg.Wait()
	})
}
func TestStringRefDefault(t *testing.T) {
	if StringRefDefault.String() != "" {
		t.Errorf("got %s expected empty string", StringRefDefault)
	}
}

func TestStringRefExists(t *testing.T) {
	setup()
	for i := 0; i < 1e6; i += 123 {
		r := NewStringRef(strconv.Itoa(i))
		if strconv.Itoa(i) != r.String() {
			t.Errorf("got %s expected %s", r, strconv.Itoa(i))
		}
	}
}

func TestStringRefLen(t *testing.T) {
	s := ""
	for i := 0; i < 1000; i++ {
		s += "a"
		r := NewStringRef(s)
		if r.Len() != len(s) {
			t.Errorf("got len %d expected %d", r.Len(), len(s))
		}
	}
}

func BenchmarkStringRefExists(b *testing.B) {
	setup()
	for i := 0; i < b.N; i++ {
		j := (i * 123) % 1e6
		_ = NewStringRef(strconv.Itoa(j))
	}
}

func BenchmarkStringRefNew(b *testing.B) {
	setup()
	j := int(1e6)
	for i := 0; i < b.N; i++ {
		j += 1
		_ = NewStringRef(strconv.Itoa(j))
	}
}
