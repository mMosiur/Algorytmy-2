#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <map>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Stop;

// Struktura reprezentuj¹ca krawêdŸ miêdzy postojami
struct Edge {
    Stop* const stop_a; // WskaŸnik na postój
    Stop* const stop_b; // WskaŸnik na postój
    const uint weight;  // Waga krawêdzi

    // Konstruktor krawêdzi inicjalizuj¹cy zmienne
    Edge(Stop* a, Stop* b, uint w) : stop_a(a), stop_b(b), weight(w) {}
};

// Struktura reprezentuj¹ca postój
struct Stop {
    const ushort number; // Numer postoju
    const uint x, y; // Koordynaty postoju
    std::vector<Edge*> edges; // Wektor krawêdzi tego wierzcho³ka - postoju
    uint shortest_path;

    // Konstruktor przyjmuj¹cy numer i koordynaty, i inicjalizuj¹cy zmienne
    Stop(ushort number, uint x, uint y) : number(number), x(x), y(y), shortest_path(-1) {}

    // Funkcja zwracaj¹ca odleg³oœæ do postoju podanego w argumencie
    uint distance_to(const Stop& other) const {
        return std::min(abs((int)this->x - (int)other.x), abs((int)this->y - (int)other.y));
    }

    // Funkcja tworz¹ca krawêdŸ do podanego postoju i zwracaj¹ca na ni¹ wskaŸnik
    Edge* connect_to(Stop& other) {
        Edge* edge = new Edge(this, &other, distance_to(other));
        this->edges.push_back(edge);
        other.edges.push_back(edge);
        return edge;
    }
};

// Klasa reprezentuj¹ca kopiec Fibonacciego
class FibonacciHeap {

    // Struktura reprezentuj¹ca wêze³ kopca
    struct Node {
        ushort degree; // Stopieñ wêz³a (wysokoœæ jego drzewa)
        Node* parent; // WskaŸnik na wêzê³ bêd¹cy rodzicem tego wêz³a
        std::list<Node*> children; // Lista wskaŸników na dzieci tego wêz³a
        bool looser; // Flaga utraty jednego dziecka
        uint key; // Klucz (waga) wêz³a, odlegloœæ postoju od postoju startowego
        Stop* value; // Wartoœæ przechowywana przez wêze³, wskaŸnik na postój

        // Funkcja dodaj¹ca wskaŸnik na wêze³ w argumencie do listy dziedzi
        void add_child(Node* other) {
            children.push_back(other);
            other->parent = this;
            other->looser = false;
            degree++;
        }

        // Konstruktor inicjalizuj¹cy zmienne
        Node(uint key, Stop* value) : degree(0), key(key), value(value), parent(nullptr), looser(false) {}
    };

    uint nof_elements; // Liczba elementów w kopcu
    std::list<Node*> roots; // Lista korzeni drzew kopca
    std::list<Node*>::iterator minimum; // Iterator kopca wskazuj¹cy element minimalny
    std::map<Stop*, Node*> stops; // Mapa przechowuj¹ca wskaŸniki na wêz³y dla konkretnych wskaŸników na postoje

    // Operacja przywrócenia w³aœciwoœci kopca Fibonnaciego
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

    // Funkcja odczepiaj¹ca wêzê³ od rodzica i wrzucaj¹ca go do korzeni, powtarzaj¹ca czynnoœæ jeœli trzeba dla ojca
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

    // Konstruktor inicjalizuj¹cy zmienne
    FibonacciHeap() : nof_elements(0) {}

    // Funkcja zwracaj¹ca, czy kopiec jest pusty
    bool empty() {
        return nof_elements == 0;
    }

    // Funkcja tworz¹ca nowy wêzê³ o podanych atrybutach
    void push(uint key, Stop* value) {
        Node* new_node = new Node(key, value);
        stops[value] = new_node;
        roots.push_front(new_node);
        if(roots.size() == 1 || roots.front()->key < (*minimum)->key) minimum = roots.begin();
        nof_elements++;
    }
    
    // Funkcja zwracaj¹ca wskaŸnik na postój w minimalnym wêŸle
    Stop* top() {
        if(empty()) return nullptr;
        return (*minimum)->value;
    }

    // Funkcja usuwaj¹ca minimalny wêzê³ z kopca
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

    // Funkcja zmniejszaj¹ca klucz dla danego postoju
    void decrease_key(uint new_key, Stop* value) {
        Node* node = stops[value];
        Node* parent = node->parent;
        node->key = new_key;
        if(parent == nullptr || parent->key <= node->key) return;
        detach_node(node);
    }
};

// Klasa reprezentuj¹ca trasê Partycji
class Route {
    std::vector<Stop> stops; // Wektor postojów
    std::vector<Edge*> edges; // Wektor wskaŸników na wszystkie krawêdzie
    Stop* start; // WskaŸnik na postój startowy
    Stop* destination; // WskaŸnik na postój docelowy

public:

    // Konstrutkor przyjmuj¹cy liczbê postojów, wczytuj¹cy dane oraz generuj¹cy na ich podstawie graf
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

    // Destruktor usuwaj¹cy dynamicznie stworzone krawêdzie
    ~Route() {
        for(auto& edge : edges) {
            delete edge;
        }
    }

    // Funkcja zwracaj¹ca nakrótsz¹ odleg³oœæ od postoju pocz¹tkowego do docelowego
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