#include <iostream>
#include <vector>
#include <list>
#include <map>

typedef unsigned int uint;

// Klasa reprezentuj¹ca strukturê zbiorów roz³¹cznych
class DisjointSets {
    // Struktura reprezentuj¹ca element struktury zbiorów roz³¹cznych
    struct Element {
        uint id; // Id elementu
        uint parent_id; // Id rodzica elementu
        uint subtree_size; // Wielkoœæ tworzonego poddrzewa
    };
    
    std::vector<Element> sets; // Wektor elementów struktury zbiorów roz³¹cznych

public:

    // Kontruktor przyjmuj¹cy iloœæ elementów i inicjalizuj¹cy ich zmienne
    DisjointSets(uint nof_elements) {
        sets.reserve(nof_elements);
        for(uint i = 0; i < nof_elements; i++) {
            sets.push_back({ i, i, 1 });
        }
    }

    // Funkcja zwracaj¹ca wskaŸnik na rodzica elementu o id podanym w argumencie
    Element* find_root(uint id) {
        while(sets[id].parent_id != id) {
            id = sets[id].parent_id;
        }
        return &sets[id];
    }

    // Funkcja wykonuj¹ca uniê dwóch elementów o podanych id
    // Zwraca true jeœli elementy s¹ ju¿ w tym samym drzewie i false, jeœli wykonana zosta³a unia
    bool union_roots(uint x, uint y) {
        Element* x_root = find_root(x);
        Element* y_root = find_root(y);
        if(x_root == y_root) return true;
        if(x_root->subtree_size < y_root->subtree_size) { // y wiêksze od x
            x_root->parent_id = y_root->id;
            y_root->subtree_size += x_root->subtree_size;
        } else { // x wiêksze od (lub równe) y
            y_root->parent_id = x_root->id;
            x_root->subtree_size += y_root->subtree_size;
        }
        return false;
    }

};

// Klasa reprezentuj¹ca graf
class Graph {
    const uint nof_members; // Liczba cz³onków portalu spo³ecznoœciowego
    std::list<std::pair<uint, uint>> edges; // Lista krawêdzi reprezentowanych przez parê (id, id)

public:

    // Kontruktor przyjmuj¹cy liczbê cz³onków portalu, wczytuj¹cy odpowiednio dane i generuj¹cy na ich podstawie krawêdzie grafu
    Graph(const uint nof_members) : nof_members(nof_members) {
        std::map<uint, std::list<uint>> interest_groups;
        for(uint member = 0; member < nof_members; member++) {
            uint nof_interests;
            std::cin >> nof_interests;
            for(uint i = 0; i < nof_interests; i++) {
                uint interest;
                std::cin >> interest;
                interest_groups[interest].push_back(member);
            }
        }
        for(const auto& interest_group : interest_groups) {
            for(auto it1 = interest_group.second.begin(); it1 != interest_group.second.end(); ++it1) {
                for(auto it2 = it1; it2 != interest_group.second.end(); ++it2) {
                    if(it1 == it2) continue;
                    edges.emplace_back((*it1), (*it2));
                }
            }
        }
    }

    // Funkcja zwracaj¹ca, czy dany graf jest cykliczny
    bool has_cycle() {
        DisjointSets sets(nof_members);
        for(auto& edge : edges) {
            if(sets.union_roots(edge.first, edge.second)) return true;
        }
        return false;
    }
};

int main() {

    uint n; // Iloœæ osób w grupie spo³ecznej

    std::cin >> n;

    Graph graph(n);

    std::cout << (graph.has_cycle() ? "TAK" : "NIE") << std::endl;

    return 0;
}