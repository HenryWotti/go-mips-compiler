package main

import "fmt"

func main() {
    var x int;
    x = 4;

    if x + 1 > 5 {
        fmt.Println("x eh maior que 5");
    } else {
        fmt.Println("x eh menor ou igual a 5");
    }
}