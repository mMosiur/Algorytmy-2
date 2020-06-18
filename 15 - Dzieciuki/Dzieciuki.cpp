#include <iostream>

/*
Dowód sprowadza się do tego, że ciało (Z2 ,+,*) to tak na prawdę zbiór działań wykonywanych na liczbach binarnych.
Co za tym idzie można liczby te sprowadzić do zmiennych logiczny, a działania na nie do operacji logicznych.
W ten sposób przekształcić wielomian można do CNF, co, jak już zostało udowodnione, jest problemem NP-zupełnym.
Operacje przydatne i ich przkształcenia do CNF
P = Q		P <=> Q		(~P or Q) & (~Q or P)
P + Q		P xor Q		~(P <=> Q)		...
P * Q		P and Q
*/

int main() {
	std::cout << "Chcę bronić" << std::endl;
	return 0;
}