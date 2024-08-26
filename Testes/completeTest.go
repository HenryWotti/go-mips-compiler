// Online Go compiler to run Golang program online
// Print "Try programiz.pro" message

package main

import "fmt"

func add(x float32, y float32) float32 {
    var z float32;
    z = x + y;
    var str string;
    str = "Estamos na funcao add";
    fmt.Println(str);
	return z;
}

func returnBool() bool {
    var x float32;
    x = add(4.6,5.7);
    if x > 1 {
        return true;
    }
	return false;
}

func variosArgumentos(x float32, y string, z bool, w int) bool {
	var aux bool;
    return aux;
}

func noReturn() void {
    fmt.Println("Voce esta no noReturn");
}

/* oi tudo bom*/

//tudo sim

func main() {
    var x int;
    x = 20 + 30;
    
    var a int;
    var b string;

    var g float32;
    var h float32;

    g = float32(1);
    h = 1.3;

    var str string;
    str = "Hello World";

    fmt.Scanf("%s", &str);
    fmt.Scanf("%d", &a);
    fmt.Scanf("%s", &b);
    
    fmt.Println("Esta eh nossa string:");
    fmt.Println(str);
    fmt.Println(a);
    fmt.Println(b);

    noReturn();

    var soma float32;
    soma = add(g,h);
    fmt.Println("Soma:");
    fmt.Println(soma);

    var j bool;
    j = returnBool();
    fmt.Println(j);

	var test bool;
	test = variosArgumentos(g,str,true,x);
    fmt.Println(test);
    
    if 7 % 2 == 0 {
        fmt.Println("7 is even");
        x = 7;
        fmt.Println("Is even:");
        fmt.Println(x);
    } else {
        fmt.Println("7 is uneven");
    }

    var arr [5]int;

    for i:= 0; i < 5; i++{
        arr[i]=i;
        fmt.Println(arr[i]);
        fmt.Println("Valor:");
        fmt.Println(arr[i]);
    }
}