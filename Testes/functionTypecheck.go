package main

import "fmt"
/*
func add(x float32) float32 {
	var b float32;
	b = x + x;
	return b;
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
}*/

func noReturn() void {
	var a int;
	var b float32;
	var somaInt int;
	somaInt = a + int(7.2);
}

func noRetur2() void {
	var a int;
}

func noRetur3() void {
	var a int;
}

func main() {
	var y float32;
	var z float32;
	var somaFloat float32;
	//var str string;
	//var k bool;
	//somaFloat = add(y,z);
	//var j bool;
	noReturn();
	//j = variosArgumentos(7.2,"test",true,7);
	//j = variosArgumentos(y,str,k,x);

	/* Erros estão comentados */
	//somaFloat = add(y,z,x);
	//somaFloat = add(x,5.3);
	//somaFloat = add(3,5.3);
	//somaFloat = add(5.3,3);
}