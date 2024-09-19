package main

import "fmt"

func fatorial(n int) int {
	var aux int;
	var aux2 int;
	var aux3 int;
	//fmt.Println("Entrou na funcao fatorial com n =");
	//fmt.Println(n);
	if n == 0 {
		//fmt.Println("n == 0, retornando 1");
        return 1;
    }
	aux = n-1;
	//fmt.Println("aux (n-1) =");
	//fmt.Println(aux);
	aux2 = fatorial(aux);
	//fmt.Println("Resultado da chamada recursiva fatorial(aux):");
	//fmt.Println(aux2);
	aux3 = n * aux2;
	//fmt.Println("aux3 (n * aux2) =");
	//fmt.Println(aux3);
    return aux3;
}

func main() {
	var fac int;
	fac = fatorial(5);
	fmt.Println("Resultado Final: ");
	fmt.Println(fac);
}