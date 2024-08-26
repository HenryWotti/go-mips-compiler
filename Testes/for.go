package main

import "fmt"

func main() {

	var x int;
	for i:= 2; i < 5; i++{
		x = i;
        fmt.Println(x);
    }
	
	/* Erros estão comentados */
	/*
	for j := 1; j + 4; j++ {
		fmt.Println(j);
	}
	
	for j := 1.2; j < 4; j++ {
		fmt.Println(j);
	}
	*/
}