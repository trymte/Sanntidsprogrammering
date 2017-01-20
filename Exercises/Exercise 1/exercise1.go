// go run Exercise1.go

package main

import (
	. "fmt"
	"runtime"
	"time"
)

var i int

func thread_1_function() {
	Println("Hello from thread 1!")
	for j := 0; j < 1000000; j++ {
		i++
	}
}

func thread_2_function() {
	Println("Hello from thread 2!")
	for k := 0; k < 1000000; k++ {
		i--
	}
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU()) // I guess this is a hint to what GOMAXPROCS does...
	// Try doing the exercise both with and without it!
	go thread_1_function() // This spawns someGoroutine() as a goroutine
	go thread_2_function()
	// We have no way to wait for the completion of a goroutine (without additional syncronization of some sort)
	// We'll come back to using channels in Exercise 2. For now: Sleep.
	time.Sleep(100 * time.Millisecond)
	Println(i)
}
