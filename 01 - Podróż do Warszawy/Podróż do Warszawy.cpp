#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

typedef unsigned short ushort;
typedef unsigned int uint;

// Struktura reprezentuj�ca punkt postoju
struct Stop {
    ushort number;      // Numer postoju
    uint shortest_path; // Najkr�tsza odleg�o�� od postoju pocz�tkowego
    uint x, y;          // Koordynaty postoju
    std::map<Stop*, ushort> connections;

    // Konstruktor inicjalizuj�cy najkr�tsza tras� do wielko�ci maksymalnej
    Stop(ushort number) : shortest_path(-1), number(number) {}

    // Funkcja tworz�ca kraw�d� mi�dzy tym przystankiem a podanym w argumencie
    void connect_with(Stop*& other) {
        uint weight = std::min(abs((int)x - (int)other->x), abs((int)y - (int)other->y));
        connections[other] = weight;
        other->connections[this] = weight;
    }

    uint get_weight_to(Stop*& other) {
        if (other == this) return 0;
        auto pos = connections.find(other);
        if (pos == connections.end()) return -1;
        return pos->second;
    }
};

// Klasa reprezentuj�ca tras� przejazdu
class Route {
    std::vector<Stop*> stops; // Tablica wska�nik�w na postoje
    Stop* start;               // Wska�nik na post�j pocz�tkowy - punkt startowy
    Stop* end;                 // Wska�nik na post�j ko�cowy - punkt docelowy

public:
    // Konstruktor przyjmuj�cy liczb� postoj�w, wczytuj�cy potrzebne dane i inicjalizuj�cy zmienne
    Route(ushort nof_stops) : stops(nof_stops) {
        for (ushort i = 0; i < nof_stops; i++) {
            stops[i] = new Stop(i);
            std::cin >> stops[i]->x >> stops[i]->y;
        }
        ushort start_number, end_number;
        std::cin >> start_number >> end_number;
        start = stops[start_number];
        end = stops[end_number];
        std::sort(stops.begin(), stops.end(), [](Stop*& left, Stop*& right) {
            return left->x < right->x;
            });
        for (ushort i = 1; i < nof_stops - 1; i++) {
            stops[i - 1]->connect_with(stops[i]);
            stops[i]->connect_with(stops[i + 1]);
        }
        std::sort(stops.begin(), stops.end(), [](Stop*& left, Stop*& right) {
            return left->y < right->y;
            });
        for (ushort i = 1; i < nof_stops - 1; i++) {
            stops[i - 1]->connect_with(stops[i]);
            stops[i]->connect_with(stops[i + 1]);
        }
    }

    // Destruktor usuwaj�cy zmienne stworzone dynamicznie
    ~Route() {
        for (auto& stop : stops) {
            delete stop;
        }
    }

    // Funkcja zwracajaca d�ugo�� najkr�tszej drogi z postoju startowego do docelowego
    uint shortest_path() {
        auto cmp = [](Stop* left, Stop* right) {
            return left->shortest_path > right->shortest_path;
        };
        std::priority_queue<Stop*, std::vector<Stop*>, decltype(cmp)> queue(cmp);
        for (ushort i = 0; i < stops.size(); i++) {
            stops[i]->shortest_path = start->get_weight_to(stops[i]);
            if (stops[i] != start) queue.push(stops[i]);
        }
        Stop* current_stop = queue.top();
        while (current_stop != end) {
            if (current_stop->shortest_path < end->shortest_path) {
                for (auto& stop : stops) {
                    if (stop == start || stop == current_stop) continue;
                    uint current_stop_to_stop = current_stop->get_weight_to(stop);
                    if (current_stop_to_stop == (unsigned)-1) continue;
                    uint new_path = current_stop_to_stop + current_stop->shortest_path;
                    if (new_path < stop->shortest_path) {
                        stop->shortest_path = new_path;
                        queue.push(stop);
                    }
                }
            }
            queue.pop();
            current_stop = queue.top();
        }
        return end->shortest_path;
    }
};

int main() {
    ushort n; // Liczba postoj�w

    std::cin >> n;

    Route route(n); // Obiekt trasy przejazdu

    std::cout << route.shortest_path() << std::endl;

    return 0;
}