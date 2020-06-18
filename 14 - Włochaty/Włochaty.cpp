#include <iostream>
#include <vector>
#include <ctime>

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

static std::vector<std::vector<short>> power_table; // Globalna statycza tablica potęg

// Funkcja iniclazująca tablicę potęg do modulo o podanej wielkości
void initialize_power_table(ushort modulo) {
	power_table.resize(modulo);
	power_table[0].resize(modulo, 0);
	for(ushort i = 1; i < modulo; i++) {
		power_table[i].resize(modulo, -1);
		power_table[i][0] = 1;
	}
}

// Funkcja licząca potęgę modulo dla podanej liczby, potęgi i granicy przy użyciu cachu w formie tablicy potęg
static ushort get_power_modulo(ulong number, ushort power, ushort modulo) {
	number %= modulo;
	if(power_table[number][power] < 0) {
		if(power % 2 == 0) { // Liczba parzysta
			uint partial = get_power_modulo(number, power / 2, modulo);
			power_table[number][power] = (partial * partial) % modulo;
		} else { // Liczba nieparzysta
			power_table[number][power] = (number * get_power_modulo(number, power - 1, modulo)) % modulo;
		}
	}
	return power_table[number][power];
}

// Klasa reprezentująca wielomian
class Polynomial {

	// Struktura reprezentująca jednomian składowy wielomianu
	struct Monomial {
		const ushort constant; // Stała w jednomianie
		std::vector<std::pair<uint, ushort>> used_variable_numbers; // Wektor indeksów zmiennych w wielomianie oraz potęg, w jakich się znajdują

		// Konstruktor przyjmujący stałą oraz liczbę zmiennych w jednomianie, które następnie wczytuje
		Monomial(uint constant, uint nof_variables) : constant(constant), used_variable_numbers(nof_variables) {
			for(uint i = 0; i < nof_variables; i++)
				std::cin >> used_variable_numbers[i].first >> used_variable_numbers[i].second;
		}

		// Funkcja licząca wartość jednomiany dla wartości zmiennych podanych w argumencie
		ushort resolve(std::vector<ushort>& variables) const {
			ushort result = constant % modulo;
			for(auto& var : used_variable_numbers) {
				uint var_num = var.first;
				ushort pow = var.second;
				ushort partial = get_power_modulo(variables[var_num], pow, modulo);
				result = ((ulong)result * (ulong)partial) % modulo;
			}
			return result;
		}
	};

	// Funkcja randomizująca wartości zmiennych
	void randomize_variables() {
		for(auto& variable : variables) {
			variable = std::rand() % modulo;
		}
	}

	// Funkcja licząca wartość całego wielomianu dla aktualnych wartości zmiennych
	ushort resolve() {
		ushort result = 0;
		for(auto& monomial : monomials) {
			result = ((ulong)result + (ulong)monomial.resolve(variables)) % modulo;
		}
		return result;
	}

	std::vector<ushort> variables; // Wektor wartości zmiennych
	std::vector<Monomial> monomials; // Wektor obiektór jednomianów

	

public:

	static ushort modulo; // Statycznie pole mówiące o wielkości ciała

	// Konstruktor przyjmujący liczbę zmiennych, jednomianów i wielkość ciała oraz wczytujący dane do jednomianów
	Polynomial(ushort nof_variables, uint nof_monomials)
		: variables(nof_variables) {
		monomials.reserve(nof_monomials);
		for(uint i = 0; i < nof_monomials; i++) {
			uint z, c;
			std::cin >> z >> c;
			monomials.push_back(Monomial(c, z));
		}
	}

	// Funkcja zwracająca, czy możliwe jest takie dobranie zmiennych w jednomianie, aby otrzymać podaną stałą
	bool is_possible_output(uint constant) {
		uint nof_tries = 175 + variables.size() / 800;
		for(uint i = 0; i < nof_tries; i++) {
			randomize_variables();
			if(resolve() == constant) return true;
		}
		return false;
	}
};

ushort Polynomial::modulo = 0;

int main() {
	std::srand(time(NULL));
	std::ios::sync_with_stdio(false);

	ushort n; // Liczba zmiennych w wielomianie (0, 30000]
	uint m; // Ilośc jednomianów (0, 100000]
	ushort q; // Rozmiar ciała (liczba pierwsza) (0, 300)
	std::cin >> n >> m >> q;

	Polynomial::modulo = q;

	initialize_power_table(q);


	Polynomial polynomial(n, m);

	uint c; // Stała do sprawdzenia
	std::cin >> c;
	std::cout << (polynomial.is_possible_output(c) ? "TAK" : "NIE") << std::endl;

	return 0;
}