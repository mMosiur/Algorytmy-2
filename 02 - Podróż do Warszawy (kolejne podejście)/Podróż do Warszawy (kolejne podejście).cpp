#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <map>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Stop;

// Struktura reprezentuj�ca kraw�d� mi�dzy postojami
struct Edge {
    Stop* const stop_a; // Wska�nik na post�j
    Stop* const stop_b; // Wska�nik na post�j
    const uint weight;  // Waga kraw�dzi

    // Konstruktor kraw�dzi inicjalizuj�cy zmienne
    Edge(Stop* a, Stop* b, uint w) : stop_a(a), stop_b(b), weight(w) {}
};

// Struktura reprezentuj�ca post�j
struct Stop {
    const ushort number; // Numer postoju
    const uint x, y; // Koordynaty postoju
    std::vector<Edge*> edges; // Wektor kraw�dzi tego wierzcho�ka - postoju
    uint shortest_path;

    // Konstruktor przyjmuj�cy numer i koordynaty, i inicjalizuj�cy zmienne
    Stop(ushort number, uint x, uint y) : number(number), x(x), y(y), shortest_path(-1) {}

    // Funkcja zwracaj�ca odleg�o�� do postoju podanego w argumencie
    uint distance_to(const Stop& other) const {
        return std::min(abs((int)this->x - (int)other.x), abs((int)this->y - (int)other.y));
    }

    // Funkcja tworz�ca kraw�d� do podanego postoju i zwracaj�ca na ni� wska�nik
    Edge* connect_to(Stop& other) {
        Edge* edge = new Edge(this, &other, distance_to(other));
        this->edges.push_back(edge);
        other.edges.push_back(edge);
        return edge;
    }
};

// Klasa reprezentuj�ca kopiec Fibonacciego
class FibonacciHeap {

    // Struktura reprezentuj�ca w�ze� kopca
    struct Node {
        ushort degree; // Stopie� w�z�a (wysoko�� jego drzewa)
        Node* parent; // Wska�nik na w�z� b�d�cy rodzicem tego w�z�a
        std::list<Node*> children; // Lista wska�nik�w na dzieci tego w�z�a
        bool looser; // Flaga utraty jednego dziecka
        uint key; // Klucz (waga) w�z�a, odleglo�� postoju od postoju startowego
        Stop* value; // Warto�� przechowywana przez w�ze�, wska�nik na post�j

        // Funkcja dodaj�ca wska�nik na w�ze� w argumencie do listy dziedzi
        void add_child(Node* other) {
            children.push_back(other);
            other->parent = this;
            other->looser = false;
            degree++;
        }

        // Konstruktor inicjalizuj�cy zmienne
        Node(uint key, Stop* value) : degree(0), key(key), value(value), parent(nullptr), looser(false) {}
    };

    uint nof_elements; // Liczba element�w w kopcu
    std::list<Node*> roots; // Lista korzeni drzew kopca
    std::list<Node*>::iterator minimum; // Iterator kopca wskazuj�cy element minimalny
    std::map<Stop*, Node*> stops; // Mapa przechowuj�ca wska�niki na w�z�y dla konkretnych wska�nik�w na postoje

    // Operacja przywr�cenia w�a�ciwo�ci kopca Fibonnaciego
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

    // Funkcja odczepiaj�ca w�z� od rodzica i wrzucaj�ca go do korzeni, powtarzaj�ca czynno�� je�li trzeba dla ojca
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

    // Konstruktor inicjalizuj�cy zmienne
    FibonacciHeap() : nof_elements(0) {}

    // Funkcja zwracaj�ca, czy kopiec jest pusty
    bool empty() {
        return nof_elements == 0;
    }

    // Funkcja tworz�ca nowy w�z� o podanych atrybutach
    void push(uint key, Stop* value) {
        Node* new_node = new Node(key, value);
        stops[value] = new_node;
        roots.push_front(new_node);
        if(roots.size() == 1 || roots.front()->key < (*minimum)->key) minimum = roots.begin();
        nof_elements++;
    }
    
    // Funkcja zwracaj�ca wska�nik na post�j w minimalnym w�le
    Stop* top() {
        if(empty()) return nullptr;
        return (*minimum)->value;
    }

    // Funkcja usuwaj�ca minimalny w�z� z kopca
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

    // Funkcja zmniejszaj�ca klucz dla danego postoju
    void decrease_key(uint new_key, Stop* value) {
        Node* node = stops[value];
        Node* parent = node->parent;
        node->key = new_key;
        if(parent == nullptr || parent->key <= node->key) return;
        detach_node(node);
    }
};

// Klasa reprezentuj�ca tras� Partycji
class Route {
    std::vector<Stop> stops; // Wektor postoj�w
    std::vector<Edge*> edges; // Wektor wska�nik�w na wszystkie kraw�dzie
    Stop* start; // Wska�nik na post�j startowy
    Stop* destination; // Wska�nik na post�j docelowy

public:

    // Konstrutkor przyjmuj�cy liczb� postoj�w, wczytuj�cy dane oraz generuj�cy na ich podstawie graf
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

    // Destruktor usuwaj�cy dynamicznie stworzone kraw�dzie
    ~Route() {
        for(auto& edge : edges) {
            delete edge;
        }
    }

    // Funkcja zwracaj�ca nakr�tsz� odleg�o�� od postoju pocz�tkowego do docelowego
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

    ushort n; // Liczba postoj�w

    std::cin >> n;

    Route route(n);

    std::cout << route.shortest_path() << std::endl;

    return 0;
}