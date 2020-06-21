#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <map>

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

    // Funkcja tworząca krawędź do podanego postoju i zwracająca na nią wskaźnik
    Edge* connect_to(Stop& other) {
        Edge* edge = new Edge(this, &other, distance_to(other));
        this->edges.push_back(edge);
        other.edges.push_back(edge);
        return edge;
    }
};

// Klasa reprezentująca kopiec Fibonacciego
class FibonacciHeap {

    // Struktura reprezentująca węzeł kopca
    struct Node {
        ushort degree; // Stopień węzła (wysokość jego drzewa)
        Node* parent; // Wskaźnik na węzęł będący rodzicem tego węzła
        std::list<Node*> children; // Lista wskaźników na dzieci tego węzła
        bool looser; // Flaga utraty jednego dziecka
        uint key; // Klucz (waga) węzła, odleglość postoju od postoju startowego
        Stop* value; // Wartość przechowywana przez węzeł, wskaźnik na postój

        // Funkcja dodająca wskaźnik na węzeł w argumencie do listy dziedzi
        void add_child(Node* other) {
            children.push_back(other);
            other->parent = this;
            other->looser = false;
            degree++;
        }

        // Konstruktor inicjalizujący zmienne
        Node(uint key, Stop* value) : degree(0), key(key), value(value), parent(nullptr), looser(false) {}
    };

    uint nof_elements; // Liczba elementów w kopcu
    std::list<Node*> roots; // Lista korzeni drzew kopca
    std::list<Node*>::iterator minimum; // Iterator kopca wskazujący element minimalny
    std::map<Stop*, Node*> stops; // Mapa przechowująca wskaźniki na węzły dla konkretnych wskaźników na postoje

    // Operacja przywrócenia właściwości kopca Fibonnaciego
    void consolidate() {
        if(nof_elements < 2) return;
        std::vector<Node*> trees(floor(std::log2(nof_elements)) + 2, nullptr);
        while(roots.size() > 0) {
            ushort degree = roots.back()->degree;
            if(trees[degree] == nullptr) {
                trees[degree] = roots.back();
                roots.pop_back();
            } else {
                if(trees[degree]->key < roots.back()->key) {
                    trees[degree]->add_child(roots.back());
                    roots.pop_back();
                    roots.push_back(trees[degree]);
                } else {
                    roots.back()->add_child(trees[degree]);
                }
                trees[degree] = nullptr;
            }
        }
        for(auto& tree : trees) {
            if(tree == nullptr) continue;
            roots.push_back(tree);
        }
        minimum = roots.begin();
        for(auto it = roots.begin(); it != roots.end(); ++it) {
            if((*it)->key < (*minimum)->key) minimum = it;
        }
    }

    // Funkcja odczepiająca węzęł od rodzica i wrzucająca go do korzeni, powtarzająca czynność jeśli trzeba dla ojca
    void detach_node(Node* node) {
        Node* parent = node->parent;
        if(parent == nullptr) return;
        parent->children.remove(node);
        node->parent = nullptr;
        roots.push_front(node);
        if(parent->looser) detach_node(parent);
        else if(parent->parent != nullptr) parent->looser = true;
    }

public:

    // Konstruktor inicjalizujący zmienne
    FibonacciHeap() : nof_elements(0) {}

    // Funkcja zwracająca, czy kopiec jest pusty
    bool empty() {
        return nof_elements == 0;
    }

    // Funkcja tworząca nowy węzęł o podanych atrybutach
    void push(uint key, Stop* value) {
        Node* new_node = new Node(key, value);
        stops[value] = new_node;
        roots.push_front(new_node);
        if(roots.size() == 1 || roots.front()->key < (*minimum)->key) minimum = roots.begin();
        nof_elements++;
    }

    // Funkcja zwracająca wskaźnik na postój w minimalnym węźle
    Stop* top() {
        if(empty()) return nullptr;
        return (*minimum)->value;
    }

    // Funkcja usuwająca minimalny węzęł z kopca
    void pop() {
        if(empty()) return;
        Node* min_node = (*minimum);
        for(auto& child : min_node->children) {
            child->parent = nullptr;
            roots.push_front(child);
        }
        stops.erase(min_node->value);
        delete min_node;
        roots.erase(minimum);
        nof_elements--;
        consolidate();
    }

    // Funkcja zmniejszająca klucz dla danego postoju
    void decrease_key(uint new_key, Stop* value) {
        Node* node = stops[value];
        Node* parent = node->parent;
        node->key = new_key;
        if(parent == nullptr || parent->key <= node->key) return;
        detach_node(node);
    }
};

// Klasa reprezentująca trasę Partycji
class Route {
    std::vector<Stop> stops; // Wektor postojów
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
        //std::priority_queue<std::pair<uint, Stop*>, std::vector<std::pair<uint, Stop*>>, std::greater<std::pair<uint, Stop*>>> queue;
        FibonacciHeap queue;
        start->shortest_path = 0;
        Stop* pos = start;
        while(pos != destination) {
            for(auto& edge : pos->edges) {
                Stop* const other = ((edge->stop_a == pos) ? edge->stop_b : edge->stop_a);
                if(other->shortest_path == (uint)-1) {
                    other->shortest_path = pos->shortest_path + edge->weight;
                    queue.push(other->shortest_path, other);
                } else {
                    uint new_path = pos->shortest_path + edge->weight;
                    if(new_path < other->shortest_path) {
                        other->shortest_path = new_path;
                        //queue.push(new_path, other);
                        queue.decrease_key(new_path, other);
                    }
                }
            }
            pos = queue.top();
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