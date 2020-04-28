#include <iostream>
#include <vector>
#include <unordered_set>

typedef unsigned int uint;

// Struktura reprezentuj�ca w�ze� drzewa
struct Node {
    uint key; // Klucz w�z�a

    // Konstruktor przyjmuj�cy warto�� klucza i incjalizuj�cy pola
    Node(uint key) : key(key), parent(nullptr), left_child(nullptr), right_child(nullptr) {}

    friend class ClueSearcher; // Zaprzyja�nienie z klas� poszukiwacza, �eby mia� dost�p do metod prywatych

private:

    Node* parent; // Wska�nik na w�z� rodzica
    Node* left_child; // Wska�nik na w�ze� lewego dziecka
    Node* right_child; // Wska�nik na w�ze� prawego dziecka

    // Funkcja zwracaj�ca najwi�kszego mniejszego potomka tego w�z�a
    Node* biggest_lower_descendant() {
        if(left_child == nullptr) return nullptr;
        Node* pos = left_child;
        while(pos->right_child) {
            pos = pos->right_child;
        }
        return pos;
    }

    // Funkcja dodaj�ca dany w�ze� jako dziecko (lub dalszy potomek)
    void add_child(Node*& node) {
        if(node->key <= key) { // Klucz mniejszy b�d� r�wny temu w�z�owi
            if(left_child) left_child->add_child(node);
            else {
                node->parent = this;
                left_child = node;
            }
        } else { // Klucz wi�kszy ni� tego w�z�a
            if(right_child) right_child->add_child(node);
            else {
                node->parent = this;
                right_child = node;
            }
        }
    }

    // Funkcja znajduj�ca w�ze� z argumentu w dzieciach i odpinaj�ca go od tego w�z�a
    void detach_child(Node* child) {
        if(child == nullptr) exit(1);
        if(child == left_child) {
            left_child->parent = nullptr;
            left_child = nullptr;
        } else if(child == right_child) {
            right_child->parent = nullptr;
            right_child = nullptr;
        }
    }

    // Funkcja zwracaj�ca nast�pnika danego w�z�a (nast�pny w�ze� co do wielko�ci)
    Node* successor() {
        if(right_child) {
            Node* pos = right_child;
            while(pos->left_child) pos = pos->left_child;
            return pos;
        } else {
            uint key = this->key;
            Node* pos = parent;
            while(pos != nullptr && pos->key < key) pos = pos->parent;
            return pos;
        }
    }

    // Funkcja zawracaj�ca poprzednika danego w�z�a (poprzedni w�ze� co do wielko�ci
    Node* predecessor() {
        if(left_child) {
            Node* pos = left_child;
            while(pos->right_child) pos = pos->right_child;
            return pos;
        } else {
            Node* pos = parent;
            uint key = this->key;
            while(pos != nullptr && pos->key > key) pos = pos->parent;
            return pos;
        }
    }

};

// Klasa reprezentujaca poszukiwacz pary trop�w
class ClueSearcher {

    Node* root; // Wska�nik na korze� drzewa BST
    std::pair<uint, uint> bounds; // Para liczb b�d�ca granicami drzewa
    uint estimate; // Szacowana warto�� docelowa

    // Funkcja zwracaj�ca wska�nik na w�ze� o podanym kluczu
    Node* find_node(uint key) {
        Node* pos = root;
        while(pos && pos->key != key) {
            pos = (pos->key < key ? pos->right_child : pos->left_child);
        }
        return pos;
    }

    // Funkcja dodaj�ca do drzewa nowy w�ze� o podanym kluczu
    void add_node(uint key) {
        Node* new_node = new Node(key);
        if(root == nullptr) root = new_node;
        else root->add_child(new_node);
    }

    // Funkcja usuwaj�ca w�ze� o podanym kluczu z drzewa
    void delete_node(uint key) {
        Node* node = find_node(key);
        if(node == nullptr) exit(1);
        if(node->left_child && node->right_child) { // Dw�jka dzieci
            Node* highest_left_child = node->biggest_lower_descendant();
            swap_nodes(node, highest_left_child);
        }
        if(node->left_child == nullptr && node->right_child == nullptr) { // Brak dzieci
            if(node == root) root = nullptr;
            else if(node == node->parent->left_child) node->parent->left_child = nullptr;
            else node->parent->right_child = nullptr;
        } else { // Jedno dziecko
            Node* child = (node->left_child ? node->left_child : node->right_child);
            if(node == root) {
                child->parent = nullptr;
                root = child;
            } else {
                child->parent = node->parent;
                if(node == node->parent->left_child) node->parent->left_child = child;
                else node->parent->right_child = child;
            }
        }
        delete node;
    }

    // Funkcja usuwaj�ca podany w argumencie w�ze� wrac ze wszysktimi jego potomkami
    void delete_subtree(Node* node) {
        if(node == nullptr) return;
        if(node->left_child) delete_subtree(node->left_child);
        if(node->right_child) delete_subtree(node->right_child);
        if(node->parent) node->parent->detach_child(node);
        delete node;
    }

    // Funkcja przycinaj�ca w�ze� i wszystkich jego potomk�w oraz zwracaj�ca wska�nik na nowy w�ze� w jego miejscu
    Node* trimmed_node(Node* node) {
        if(node == nullptr) return nullptr;
        if(node->key < bounds.first) { // Klucz mniejszy ni� dolna granica
            delete_subtree(node->left_child);
            Node* trimmed_right = trimmed_node(node->right_child);
            if(trimmed_right) trimmed_right->parent = node->parent;
            delete node;
            return trimmed_right;
        } else if(node->key > bounds.second) { // Klucz wi�kszy ni� g�rna granica
            delete_subtree(node->right_child);
            Node* trimmed_left = trimmed_node(node->left_child);
            if(trimmed_left) trimmed_left->parent = node->parent;
            delete node;
            return trimmed_left;
        } else { // Klucz w granicach
            node->left_child = trimmed_node(node->left_child);
            if(node->left_child) node->left_child->parent = node;
            node->right_child = trimmed_node(node->right_child);
            if(node->right_child) node->right_child->parent = node;
            return node;
        }
    }

    // Funkcja zamieniaj�ca miejscami dwa w�z�y
    void swap_nodes(Node*& a, Node*& b) {
        uint tkey = a->key;
        a->key = b->key;
        b->key = tkey;
        Node* tnode = a;
        a = b;
        b = tnode;
    }

    // Funkcja zwracaj�ca, czy znaleziono par� dla danego w�z�a lub w�z�a potomnego i wypisuj�ca j� w takowym przypadku
    bool find_pair(Node* node, std::unordered_set<uint>& checked) {
        if(node == nullptr) return false;
        if(find_pair(node->left_child, checked)) return true;
        uint pair = estimate - node->key;
        if(checked.find(pair) == checked.end()) {
            checked.insert(node->key);
        } else {
            if(pair < node->key) {
                std::cout << pair << " " << node->key << std::endl;
            } else {
                std::cout << node->key << " " << pair << std::endl;
            }
            return true;
        }
        return find_pair(node->right_child, checked);
    }

public:

    // Kontruktor przyjmuj�cy liczb� trop�w i wczytuj�cy reszt� danych
    ClueSearcher(uint nof_clues) : root(nullptr) {
        for(uint i = 0; i < nof_clues; i++) {
            uint key;
            std::cin >> key;
            add_node(key);
        }
        std::cin >> bounds.first >> bounds.second;
        std::cin >> estimate;
        root = trimmed_node(root);
    }

    // Funkcja wypisuj�ca par� liczb b�d�cych kluczami dw�ch poszukiwanych trop�w
    // Wypisuje NIE ZNALEZIONO gdy takie nie b�d� znalezione
    void print_pair() {
        std::unordered_set<uint> checked;
        if(!find_pair(root, checked)) {
            std::cout << "NIE ZNALEZIONO" << std::endl;
        }
    }
};

int main() {
    uint n; // Liczba trop�w politycznych

    std::cin >> n;

    ClueSearcher searcher(n);

    searcher.print_pair();

    return 0;
}