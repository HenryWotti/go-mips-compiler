package main

import "fmt"

func add(x float32, y float32) float32 {
	var soma float32;
	soma = x + y;
	return soma;
}

func noReturn() void {
	fmt.Println("Voce estah na funcao noReturn");
}

func main() {
	var x float32;
	var y float32;
	var somaFloat float32;
	x = 3.02;
	y = 4.5;
	somaFloat = add(x,y);
	fmt.Println(somaFloat);
	noReturn();
}