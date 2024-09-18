package main

import "fmt"

func main() {
	var aux int;
	var len int;
	len = 5;
	var arr[5] int;
	arr[0] = 70;
    arr[1] = 35;
    arr[2] = 10;
    arr[3] = 42;
    arr[4] = 29;

	for k := 0; k < len; k++ {
		fmt.Println(arr[k]);
	}

	fmt.Println("Print 1 concluido");

	for i := 0; i < len-1; i++ {
		for j := 0; j < len-i-1; j++ {
			if arr[j] > arr[j+1] {
                // Troca os elementos se o anterior for maior que o próximo
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
		}
    }

	fmt.Println("Bubble sort concluido, imprimindo resultados:");

	for w := 0; w < len; w++ {
		fmt.Println(arr[w]);
	}
}