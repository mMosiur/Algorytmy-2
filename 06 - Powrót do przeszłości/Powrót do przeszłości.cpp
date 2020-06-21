#include <iostream>
#include <vector>
#include <unordered_set>

typedef unsigned int uint;

// Struktura reprezentująca węzeł drzewa
struct Node {
    uint key; // Klucz węzła

    // Konstruktor przyjmujący wartość klucza i incjalizujący pola
    Node(uint key) : key(key), parent(nullptr), left_child(nullptr), right_child(nullptr) {}

    friend class ClueSearcher; // Zaprzyjaźnienie z klasą poszukiwacza, żeby miał dostęp do metod prywatych

private:

    Node* parent; // Wskaźnik na węzęł rodzica
    Node* left_child; // Wskaźnik na węzeł lewego dziecka
    Node* right_child; // Wskaźnik na węzeł prawego dziecka

    // Funkcja zwracająca największego mniejszego potomka tego węzła
    Node* biggest_lower_descendant() {
        if(left_child == nullptr) return nullptr;
        Node* pos = left_child;
        while(pos->right_child) {
            pos = pos->right_child;
        }
        return pos;
    }

    // Funkcja dodająca dany węzeł jako dziecko (lub dalszy potomek)
    void add_child(Node*& node) {
        if(node->key <= key) { // Klucz mniejszy bądź równy temu węzłowi
            if(left_child) left_child->add_child(node);
            else {
                node->parent = this;
                left_child = node;
            }
        } else { // Klucz większy niż tego węzła
            if(right_child) right_child->add_child(node);
            else {
                node->parent = this;
                right_child = node;
            }
        }
    }

    // Funkcja znajdująca węzeł z argumentu w dzieciach i odpinająca go od tego węzła
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

    // Funkcja zwracająca następnika danego węzła (następny węzeł co do wielkości)
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

    // Funkcja zawracająca poprzednika danego węzła (poprzedni węzeł co do wielkości
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

// Klasa reprezentujaca poszukiwacz pary tropów
class ClueSearcher {

    Node* root; // Wskaźnik na korzeń drzewa BST
    std::pair<uint, uint> bounds; // Para liczb będąca granicami drzewa
    uint estimate; // Szacowana wartość docelowa

    // Funkcja zwracająca wskaźnik na węzeł o podanym kluczu
    Node* find_node(uint key) {
        Node* pos = root;
        while(pos && pos->key != key) {
            pos = (pos->key < key ? pos->right_child : pos->left_child);
        }
        return pos;
    }

    // Funkcja dodająca do drzewa nowy węzeł o podanym kluczu
    void add_node(uint key) {
        Node* new_node = new Node(key);
        if(root == nullptr) root = new_node;
        else root->add_child(new_node);
    }

    // Funkcja usuwająca węzeł o podanym kluczu z drzewa
    void delete_node(uint key) {
        Node* node = find_node(key);
        if(node == nullptr) exit(1);
        if(node->left_child && node->right_child) { // Dwójka dzieci
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

    // Funkcja usuwająca podany w argumencie węzeł wrac ze wszysktimi jego potomkami
    void delete_subtree(Node* node) {
        if(node == nullptr) return;
        if(node->left_child) delete_subtree(node->left_child);
        if(node->right_child) delete_subtree(node->right_child);
        if(node->parent) node->parent->detach_child(node);
        delete node;
    }

    // Funkcja przycinająca węzeł i wszystkich jego potomków oraz zwracająca wskaźnik na nowy węzeł w jego miejscu
    Node* trimmed_node(Node* node) {
        if(node == nullptr) return nullptr;
        if(node->key < bounds.first) { // Klucz mniejszy niż dolna granica
            delete_subtree(node->left_child);
            Node* trimmed_right = trimmed_node(node->right_child);
            if(trimmed_right) trimmed_right->parent = node->parent;
            delete node;
            return trimmed_right;
        } else if(node->key > bounds.second) { // Klucz większy niż górna granica
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

    // Funkcja zamieniająca miejscami dwa węzły
    void swap_nodes(Node*& a, Node*& b) {
        uint tkey = a->key;
        a->key = b->key;
        b->key = tkey;
        Node* tnode = a;
        a = b;
        b = tnode;
    }

    // Funkcja zwracająca, czy znaleziono parę dla danego węzła lub węzła potomnego i wypisująca ją w takowym przypadku
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

    // Kontruktor przyjmujący liczbę tropów i wczytujący resztę danych
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

    // Funkcja wypisująca parę liczb będących kluczami dwóch poszukiwanych tropów
    // Wypisuje NIE ZNALEZIONO gdy takie nie będą znalezione
    void print_pair() {
        std::unordered_set<uint> checked;
        if(!find_pair(root, checked)) {
            std::cout << "NIE ZNALEZIONO" << std::endl;
        }
    }
};

int main() {
    uint n; // Liczba tropów politycznych

    std::cin >> n;

    ClueSearcher searcher(n);

    searcher.print_pair();

    return 0;
}