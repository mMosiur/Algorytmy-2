#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Stop;

// Struktura reprezentująca krawędź między postojami
struct Edge {
    Stop* const from; // Wkaźnik na postój początkowy krawędzi
    Stop* const to;   // Wskaźnik na postój końcowy krawędzi
    const int weight; // Waga krawędzi

    // Konstruktor krawędzi inicjalizujący zmienne
    Edge(Stop* from, Stop* to, int weight) : from(from), to(to), weight(weight) {}
};

// Struktura reprezentująca postój
struct Stop {
    const ushort number;        // Numer postoju
    const uint x, y;            // Koordynaty postoju
    std::list<Edge> edges;     // Lista krawędzi wychodzących z tego wierzchołka (postoju)
    uint stress_reduce_value; // Wartość redukująca stres
    int shortest_path;          // Wartość przechowująca najkrótszą trasę z punktu początkowego

    // Konstruktor przyjmujący numer i koordynaty, i inicjalizujący zmienne
    Stop(const ushort number, const uint x, const uint y, const uint v)
        : number(number), x(x), y(y), stress_reduce_value(v), shortest_path(INT32_MAX) {}

    // Funkcja zwracająca odległość do postoju podanego w argumencie
    int distance_to(const Stop& other) const {
        return std::min(abs((int)this->x - (int)other.x), abs((int)this->y - (int)other.y)) - other.stress_reduce_value;
    }

    // Funkcja tworząca krawędź do podanego postoju jeżeli jeszcze ona nie istnieje
    void connect_to(Stop& other) {
        if(connected_to(other)) return;
        this->edges.push_back(Edge(this, &other, distance_to(other)));
    }

    // Funkcja zwracająca, czy dany postój jest już połączony z postojem podanym w argumencie
    bool connected_to(const Stop& other) const {
        for(auto& edge : edges) {
            if(edge.to == &other) return true;
        }
        return false;
    }
};

// Klasa reprezentująca trasę Partycji
class Route {
    std::vector<Stop> stops;   // Wektor postojów
    Stop* start;               // Wskaźnik na postój startowy
    Stop* destination;         // Wskaźnik na postój docelowy

    // Funkcja łącząca krawędziami sąsiadujące wierzchołki (optymalizująca ich liczbę)
    void connect_neighbours() {
        std::vector<Stop*> neighbours(stops.size(), nullptr);
        for(ushort i = 0; i < stops.size(); i++) neighbours[i] = &stops[i];
        // Sortowanie po współrzędnej x
        std::sort(neighbours.begin(), neighbours.end(),
                  [](const auto& a, const auto& b) {
                      return a->x < b->x;
                  }
        );
        for(ushort i = 1; i < neighbours.size(); i++) {
            connect(neighbours[i - 1], neighbours[i]);
        }
        // Sortowanie po współrzędnej y
        std::sort(neighbours.begin(), neighbours.end(),
                  [](const auto& a, const auto& b) {
                      return a->y < b->y;
                  }
        );
        for(ushort i = 1; i < neighbours.size(); i++) {
            connect(neighbours[i - 1], neighbours[i]);
        }
    }

    // Funkcja łącząca ze sobą dwa postoje krawędziami w obie strony
    void connect(Stop* a, Stop* b) {
        a->connect_to(*b);
        b->connect_to(*a);
    }

public:
    // Konstruktor przyjmujący liczbę postojów, wczytujący dane oraz generujący na ich podstawie graf
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

    // Funkcja zwracająca nakrótszą odległość od postoju początkowego do docelowego
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

    ushort n; // Liczba postojów

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