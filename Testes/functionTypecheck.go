package main

import "fmt"

func add(x float32, y float32) float32 {
	var z float32;
	z = x + y;
	return z;
}

func add2(x float32, y int) bool {
	return true;
}

func noReturn() void {
	fmt.Println("Funcao noReturn");
}

func variosArgumentos(x float32, y string, z bool, w int) bool {
	var aux bool;
    return aux;
}

func main() {
	var x int;
	var y float32;
	var z float32;
	var somaFloat float32;
	var str string;
	var k bool;
	somaFloat = add(y,z);
	var j bool;
	noReturn();
	j = variosArgumentos(7.2,"test",true,7);
	j = variosArgumentos(y,str,k,x);

	/* Erros estão comentados */
	//somaFloat = add(y,z,x);
	//somaFloat = add(x,5.3);
	//somaFloat = add(3,5.3);
	//somaFloat = add(5.3,3);
}