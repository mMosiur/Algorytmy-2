#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Stop;

// Struktura reprezentująca krawędź między postojami
struct Edge {
    Stop* const stop_a; // Wskaźnik na postój
    Stop* const stop_b; // Wskaźnik na postój
    const uint weight;  // Waga krawędzi

    // Konstruktor krawędzi inicjalizujący zmienne
    Edge(Stop* a, Stop* b, uint w) : stop_a(a), stop_b(b), weight(w) {}
};

// Struktura reprezentująca postój
struct Stop {
    const ushort number; // Numer postoju
    const uint x, y; // Koordynaty postoju
    std::vector<Edge*> edges; // Wektor krawędzi tego wierzchołka - postoju
    uint shortest_path;

    // Konstruktor przyjmujący numer i koordynaty, i inicjalizujący zmienne
    Stop(ushort number, uint x, uint y) : number(number), x(x), y(y), shortest_path(-1) {}

    // Funkcja zwracająca odległość do postoju podanego w argumencie
    uint distance_to(const Stop& other) const {
        return std::min(abs((int)this->x - (int)other.x), abs((int)this->y - (int)other.y));
    }

    // Funkcja tworząca krawędź do podanego postoju i zwracająa na nią wskaźnik
    Edge* connect_to(Stop& other) {
        Edge* edge = new Edge(this, &other, distance_to(other));
        this->edges.push_back(edge);
        other.edges.push_back(edge);
        return edge;
    }
};

// Klasa reprezentująca trasę Partycji
class Route {
    std::vector<Stop> stops; // Wektor postojó
    std::vector<Edge*> edges; // Wektor wskaźników na wszystkie krawędzie
    Stop* start; // Wskaźnik na postój startowy
    Stop* destination; // Wskaźnik na postój docelowy

public:

    // Konstrutkor przyjmujący liczbę postojów, wczytujący dane oraz generujący na ich podstawie graf
    Route(ushort nof_stops) : start(nullptr), destination(nullptr) {
        std::vector<std::pair<ushort, uint>> x_neighbours;
        std::vector<std::pair<ushort, uint>> y_neighbours;
        for(ushort i = 0; i < nof_stops; i++) {
            uint x, y;
            std::cin >> x >> y;
            stops.emplace_back(i, x, y);
            x_neighbours.emplace_back(i, x);
            y_neighbours.emplace_back(i, y);
        }
        ushort s, d;
        std::cin >> s >> d;
        start = &stops[s];
        destination = &stops[d];
        std::sort(x_neighbours.begin(), x_neighbours.end(),
                  [](auto& a, auto& b) {
                      return a.second < b.second;
                  });
        std::sort(y_neighbours.begin(), y_neighbours.end(),
                  [](auto& a, auto& b) {
                      return a.second < b.second;
                  });
        for(ushort i = 1; i < nof_stops; i++) {
            ushort prev = x_neighbours[i - 1].first;
            ushort curr = x_neighbours[i].first;
            edges.push_back(stops[prev].connect_to(stops[curr]));
            prev = y_neighbours[i - 1].first;
            curr = y_neighbours[i].first;
            edges.push_back(stops[prev].connect_to(stops[curr]));
        }
    }

    // Destruktor usuwający dynamicznie stworzone krawędzie
    ~Route() {
        for(auto& edge : edges) {
            delete edge;
        }
    }

    // Funkcja zwracająca nakrótszą odległość od postoju początkowego do docelowego
    uint shortest_path() const {
        std::priority_queue<std::pair<uint, Stop*>, std::vector<std::pair<uint, Stop*>>, std::greater<std::pair<uint, Stop*>>> queue;
        start->shortest_path = 0;
        Stop* pos = start;
        while(pos != destination) {
            for(auto& edge : pos->edges) {
                Stop* const other = ((edge->stop_a == pos) ? edge->stop_b : edge->stop_a);
                if(other->shortest_path == (uint)-1) {
                    other->shortest_path = pos->shortest_path + edge->weight;
                    queue.emplace(other->shortest_path, other);
                } else {
                    uint new_path = pos->shortest_path + edge->weight;
                    if(new_path < other->shortest_path) {
                        other->shortest_path = new_path;
                        queue.emplace(other->shortest_path, other);
                    }
                }
            }
            pos = queue.top().second;
            queue.pop();
        }
        return destination->shortest_path;
    }

};

int main() {

    ushort n; // Liczba postojów

    std::cin >> n;

    Route route(n);

    std::cout << route.shortest_path() << std::endl;

    return 0;
}