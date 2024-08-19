package main

import "fmt"

func variosArgumentos(x float32, y string, z bool, w int) bool {
    var soma float32;
	soma = x + w;
	fmt.Println(soma);
	var aux bool;
	aux = z;
	fmt.Println(y);
    return aux;
}

func main() {
	var x float32;
	var y string;
	var z bool;
	var w int;
	var recebeFunc bool;
	recebeFunc = variosArgumentos(x, "ola", 4, y, z);
}