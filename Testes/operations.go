package main

import "fmt"

func main() {

	var y float32;
	var h int;
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

	var j int;
	var l int;

	l = h - 2; // 3 - 2 
	j = int(2.9) - 5; // j = -3
	h = j + 7; // -3 + 7 = 4
	fmt.Println(l);
	fmt.Println(j);
	fmt.Println(h);

	y = float32(2); // y = 2.00
	fmt.Println(y);
	y = float32(h) * 3.5; // y = h * 3.5
	fmt.Println(y);
}