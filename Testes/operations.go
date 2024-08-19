package main

import "fmt"

func main() {
	var x float32;
	var y float32;

	var a int;
	var b int;

	var somafloat32 float32;
	var somaInt int;

	somafloat32 = y + x;
	somafloat32 = float32(a) - float32(b);
	somafloat32 = float32(a) * y;
	somafloat32 = x * float32(a);
	somafloat32 = 7.2 / 3.5;
	somafloat32 = float32(7) % 3.5;
	somafloat32 = 5.2 * float32(2);
	somafloat32 = float32(2) * float32(3);

	/* Erros estão comentados */
	//somafloat32 = y + a;
	//somafloat32 = a + x;
	//somafloat32 = a + b;
	//somafloat32 = a + float32(b);
	//somafloat32 = float32(a) + b;
	//somafloat32 = 2 + 7.5;
	//somafloat32 = 3 + 2;

	var str string;
	var bl bool;

	somaInt = a + b;
	somaInt = int(x) + int(y);
	somaInt = int(x) + b;
	somaInt = a + int(y);
	somaInt = 7 + 3;
	somaInt = int(7.2) + 3;
	somaInt = 5 + int(2.7);
	somaInt = int(2.5) + int(3.6);

	/* Erros estão comentados */
	//somaInt = a + y;
	//somaInt = x + b;
	//somaInt = x + y;
	//somaInt = x + int(y);
	//somaInt = int(x) + y;
	//somaInt = 2 + 7.5;
	//somaInt = 2 + int(bl);

}