package main

import "fmt"

func add(x int, y int) int {
    var z int;
    z = x + y;
    var str string;
    str = "Estamos na funcao add";
    fmt.Println(str);
	z = returnBool();
	return z;
}

func returnBool() bool {
    var x int;
    x = add(4,5);
    if x > 1 {
        return true;
    }
	return false;
}

func main() {
	var x float32;
	var y string;
	var z bool;
	var w int;
	var recebeFunc bool;
	var soma int;
	soma = add(x,w);
	recebeFunc = returnBool();
}