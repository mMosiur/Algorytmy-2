#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Stop;

// Struktura reprezentuj�ca kraw�d� mi�dzy postojami
struct Edge {
    Stop* const from; // Wka�nik na post�j pocz�tkowy kraw�dzi
    Stop* const to;   // Wska�nik na post�j ko�cowy kraw�dzi
    const int weight; // Waga kraw�dzi

    // Konstruktor kraw�dzi inicjalizuj�cy zmienne
    Edge(Stop* from, Stop* to, int weight) : from(from), to(to), weight(weight) {}
};

// Struktura reprezentuj�ca post�j
struct Stop {
    const ushort number;        // Numer postoju
    const uint x, y;            // Koordynaty postoju
    std::list<Edge> edges;     // Lista kraw�dzi wychodz�cych z tego wierzcho�ka (postoju)
    uint stress_reduce_value; // Warto�� redukuj�ca stres
    int shortest_path;          // Warto�� przechowuj�ca najkr�tsz� tras� z punktu pocz�tkowego

    // Konstruktor przyjmuj�cy numer i koordynaty, i inicjalizuj�cy zmienne
    Stop(const ushort number, const uint x, const uint y, const uint v)
        : number(number), x(x), y(y), stress_reduce_value(v), shortest_path(INT32_MAX) {}

    // Funkcja zwracaj�ca odleg�o�� do postoju podanego w argumencie
    int distance_to(const Stop& other) const {
        return std::min(abs((int)this->x - (int)other.x), abs((int)this->y - (int)other.y)) - other.stress_reduce_value;
    }

    // Funkcja tworz�ca kraw�d� do podanego postoju je�eli jeszcze ona nie istnieje
    void connect_to(Stop& other) {
        if(connected_to(other)) return;
        this->edges.push_back(Edge(this, &other, distance_to(other)));
    }

    // Funkcja zwracaj�ca, czy dany post�j jest ju� po��czony z postojem podanym w argumencie
    bool connected_to(const Stop& other) const {
        for(auto& edge : edges) {
            if(edge.to == &other) return true;
        }
        return false;
    }
};

// Klasa reprezentuj�ca tras� Partycji
class Route {
    std::vector<Stop> stops;   // Wektor postoj�w
    Stop* start;               // Wska�nik na post�j startowy
    Stop* destination;         // Wska�nik na post�j docelowy

    // Funkcja ��cz�ca kraw�dziami s�siaduj�ce wierzcho�ki (optymalizuj�ca ich liczb�)
    void connect_neighbours() {
        std::vector<Stop*> neighbours(stops.size(), nullptr);
        for(ushort i = 0; i < stops.size(); i++) neighbours[i] = &stops[i];
        // Sortowanie po wsp�rz�dnej x
        std::sort(neighbours.begin(), neighbours.end(),
                  [](const auto& a, const auto& b) {
                      return a->x < b->x;
                  }
        );
        for(ushort i = 1; i < neighbours.size(); i++) {
            connect(neighbours[i - 1], neighbours[i]);
        }
        // Sortowanie po wsp�rz�dnej
        std::sort(neighbours.begin(), neighbours.end(),
                  [](const auto& a, const auto& b) {
                      return a->y < b->y;
                  }
        );
        for(ushort i = 1; i < neighbours.size(); i++) {
            connect(neighbours[i - 1], neighbours[i]);
        }
    }

    // Funkcja ��cz�ca ze sob� dwa postoje kraw�dziami w obie strony
    void connect(Stop* a, Stop* b) {
        a->connect_to(*b);
        b->connect_to(*a);
    }

public:
    // Konstruktor przyjmuj�cy liczb� postoj�w, wczytuj�cy dane oraz generuj�cy na ich podstawie graf
    Route(ushort nof_stops) : start(nullptr), destination(nullptr) {
        stops.reserve(nof_stops);
        for(ushort i = 0; i < nof_stops; i++) {
            uint x, y, v;
            std::cin >> x >> y >> v;
            stops.push_back(Stop(i, x, y, v));
        }
        {
            ushort s, d;
            std::cin >> s >> d;
            start = &stops[s];
            destination = &stops[d];
        }
        connect_neighbours();
    }

    // Funkcja zwracaj�ca nakr�tsz� odleg�o�� od postoju pocz�tkowego do docelowego
    int shortest_path() const {
        start->shortest_path = 0;
        for(ushort i = 0; i < stops.size(); i++) {
            bool unchanged = true;
            for(auto& stop : stops) {
                if(stop.shortest_path == INT32_MAX) continue;
                for(auto& edge : stop.edges) {
                    int new_path = stop.shortest_path + edge.weight;
                    if(new_path < edge.to->shortest_path) {
                        edge.to->shortest_path = new_path;
                        unchanged = false;
                    }
                }
            }
            if(unchanged || destination->shortest_path < 0) return destination->shortest_path;
        }
        return INT32_MIN;
    }
};

int main() {

    ushort n; // Liczba postoj�w

    std::cin >> n;

    Route route(n);

    int path = route.shortest_path();

    if(path < 0) {
        std::cout << "NIE ZA DOBRZE?" << std::endl;
    } else {
        std::cout << path << std::endl;
    }

    return 0;
}