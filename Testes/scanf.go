package main

import "fmt"

func main() {
	var a int;
    var b float32;

    var str string;
    str = "Hello World";

    fmt.Scanf("%s", &str);
    fmt.Scanf("%d", &a);
	fmt.Scanf("%g", &b);

    /* Erros estão comentados */
    //fmt.Scanf("%s", &b);
    //fmt.Scanf("%d", &str);
	//fmt.Scanf("%g", &a);
}