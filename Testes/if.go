package main

import "fmt"

func main() {
    var y float32;
	var z float32;
	var x float32;
	var w bool;
	if x + y != z {
		fmt.Println("teste1");
	} else
	{
		fmt.Println("teste2");
	}

	if w {
		fmt.Println("teste1");
	}

	if x > 3 {
		fmt.Println("teste3");
	}

	/* Erros estão comentados */
	/*
	if y {
		fmt.Println("teste1");
	}
	
	if x + y {
		fmt.Println("teste1");
	}
	*/
}