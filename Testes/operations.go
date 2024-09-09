package main

import "fmt"

func main() {

	var y float32;
	var z float32;
	var x float32;
	var h int;
	var j int;
	var w bool;
	var str string;

	fmt.Scanf("%d", &h);
	fmt.Println(h);
	fmt.Scanf("%g", &y);
	fmt.Println(y);
	fmt.Scanf("%t", &w);
	fmt.Println(w);
	fmt.Scanf("%s", &str);
	fmt.Println(str);
	j = int(2.9) + 5;
	h = j + 7;
	fmt.Println(j);
	fmt.Println(h);


	y = float32(2);
	fmt.Println(y);
	y = float32(h) + 3.2;
	fmt.Println(y);
	/*h = j + 3;
	fmt.Println("h:");
	fmt.Println(h);
	h = 5 * j;
	fmt.Println(h);
	h = 6 - 3;
	fmt.Println(h);
	h = 7 % 2;
	fmt.Println(h);

	z = 2.7;
	fmt.Println("z:");
	fmt.Println(z);
	y = z + 3.4;
	fmt.Println("y:");
	fmt.Println(y);
	y = 6.8 + 3.2;
	fmt.Println(y);*/
}