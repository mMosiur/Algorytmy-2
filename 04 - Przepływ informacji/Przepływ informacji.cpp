#include <iostream>
#include <vector>
#include <list>
#include <map>

typedef unsigned int uint;

// Klasa reprezentuj�ca struktur� zbior�w roz��cznych
class DisjointSets {
    // Struktura reprezentuj�ca element struktury zbior�w roz��cznych
    struct Element {
        uint id; // Id elementu
        uint parent_id; // Id rodzica elementu
        uint subtree_size; // Wielko�� tworzonego poddrzewa
    };
    
    std::vector<Element> sets; // Wektor element�w struktury zbior�w roz��cznych

public:

    // Kontruktor przyjmuj�cy ilo�� element�w i inicjalizuj�cy ich zmienne
    DisjointSets(uint nof_elements) {
        sets.reserve(nof_elements);
        for(uint i = 0; i < nof_elements; i++) {
            sets.push_back({ i, i, 1 });
        }
    }

    // Funkcja zwracaj�ca wska�nik na rodzica elementu o id podanym w argumencie
    Element* find(uint id) {
        while(sets[id].parent_id != id) {
            id = sets[id].parent_id;
        }
        return &sets[id];
    }

    // Funkcja wykonuj�ca uni� dw�ch element�w o podanych id
    // Zwraca true je�li elementy s� ju� w tym samym drzewie i false, je�li wykonana zosta�a unia
    bool union_roots(uint x, uint y) {
        Element* x_root = find(x);
        Element* y_root = find(y);
        if(x_root == y_root) return true;
        if(x_root->subtree_size < y_root->subtree_size) { // y wi�ksze od x
            x_root->parent_id = y_root->id;
            y_root->subtree_size += x_root->subtree_size;
        } else { // x wi�ksze od (lub r�wne) y
            y_root->parent_id = x_root->id;
            x_root->subtree_size += y_root->subtree_size;
        }
        return false;
    }

};

// Klasa reprezentuj�ca graf
class Graph {
    const uint nof_members; // Liczba cz�onk�w portalu spo�eczno�ciowego
    std::list<std::pair<uint, uint>> edges; // Lista kraw�dzi reprezentowanych przez par� (id, id)

public:

    // Kontruktor przyjmuj�cy liczb� cz�onk�w portalu, wczytuj�cy odpowiednio dane i generuj�cy na ich podstawie kraw�dzie grafu
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
            auto it2 = interest_group.second.begin();
            auto it1 = it2++;
            while(it2 != interest_group.second.end()) {
                edges.emplace_back((*it1), (*it2));
                it1 = it2++;
            }
        }
    }

    // Funkcja zwracaj�ca, czy dany graf jest cykliczny
    bool has_cycle() {
        DisjointSets sets(nof_members);
        for(auto& edge : edges) {
            if(sets.union_roots(edge.first, edge.second)) return true;
        }
        return false;
    }
};

int main() {

    uint n; // Ilo�� os�b w grupie spo�ecznej

    std::cin >> n;

    Graph graph(n);

    std::cout << (graph.has_cycle() ? "TAK" : "NIE") << std::endl;

    return 0;
}