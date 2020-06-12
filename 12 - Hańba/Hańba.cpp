#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <map>

typedef unsigned int uint;

// Klasa współrzędnych spaceru
class WalkPathPoints {

	//Struktura punktu
	struct Point {
		const int x; // Współrzędna x
		const int y; // Współrzędna y

		// Konstruktor przyjmujący współrzędne
		Point(int x, int y) : x(x), y(y) {}

		// Funkcja zwracająca odległość od początku układu współrzędnych
		double distance() const {
			return hypot(x, y);
		}

		// Funkcja zwracająca kąt względem dodatniej strony osi x układu współrzędnych
		double angle() const {
			double result = atan2((double)y, (double)x);
			if(result < 0) result += M_PI * 2; // Zamiana z ujemnej na dodatnią
			return result;
		}
	};

	std::map<double, Point*> points; // mapa punktów, gdzie kluczem jest ich kąt

public:

	// Konstruktor
	WalkPathPoints() {}

	// Destruktor usuwający dynamicznie stworzone punkty
	~WalkPathPoints() {
		for(auto& pair : points) {
			delete pair.second;
		}
	}

	// Funkcja dodająca punkt o podanych współrzędnych
	void add(int x, int y) {
		if(x == 0 && y == 0) return;
		Point* const point = new Point(x, y);
		double angle = point->angle();
		auto it = points.find(angle);
		if(it == points.end()) {
			// Jeżeli nie ma, wstawiamy
			points.emplace(angle, point);
		} else if(it->second->distance() < point->distance()){
			// Jeżeli jest, ale jest bliżej środka niż nowy, zamień
			delete it->second;
			it->second = point;
		}
	}
	// Funkcja wypisująca punkty w kolejności rosnącej względem kąta
	void print_outer_points() const {
		for(auto& pair : points) {
			std::cout << pair.second->x << " " << pair.second->y << std::endl;
		}
	}
};

int main() {
	uint n; // Liczba punktów w zbiorze
	std::cin >> n;

	WalkPathPoints points;

	for(uint i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		points.add(x, y);
	}

	points.print_outer_points();

	return 0;
}