package main

import (
	"fmt"
)

func main() {

	fmt.Println(swap("hello", "world"))
}

func swap(x, y string) (string, string) {
	return y, x
}
