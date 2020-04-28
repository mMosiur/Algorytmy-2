#include <iostream>
#include <vector>
#include <unordered_set>

typedef unsigned int uint;

// Struktura reprezentuj¹ca wêze³ drzewa
struct Node {
    uint key; // Klucz wêz³a

    // Konstruktor przyjmuj¹cy wartoœæ klucza i incjalizuj¹cy pola
    Node(uint key) : key(key), parent(nullptr), left_child(nullptr), right_child(nullptr) {}

    friend class ClueSearcher; // ZaprzyjaŸnienie z klas¹ poszukiwacza, ¿eby mia³ dostêp do metod prywatych

private:

    Node* parent; // WskaŸnik na wêzê³ rodzica
    Node* left_child; // WskaŸnik na wêze³ lewego dziecka
    Node* right_child; // WskaŸnik na wêze³ prawego dziecka

    // Funkcja zwracaj¹ca najwiêkszego mniejszego potomka tego wêz³a
    Node* biggest_lower_descendant() {
        if(left_child == nullptr) return nullptr;
        Node* pos = left_child;
        while(pos->right_child) {
            pos = pos->right_child;
        }
        return pos;
    }

    // Funkcja dodaj¹ca dany wêze³ jako dziecko (lub dalszy potomek)
    void add_child(Node*& node) {
        if(node->key <= key) { // Klucz mniejszy b¹dŸ równy temu wêz³owi
            if(left_child) left_child->add_child(node);
            else {
                node->parent = this;
                left_child = node;
            }
        } else { // Klucz wiêkszy ni¿ tego wêz³a
            if(right_child) right_child->add_child(node);
            else {
                node->parent = this;
                right_child = node;
            }
        }
    }

    // Funkcja znajduj¹ca wêze³ z argumentu w dzieciach i odpinaj¹ca go od tego wêz³a
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

    // Funkcja zwracaj¹ca nastêpnika danego wêz³a (nastêpny wêze³ co do wielkoœci)
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

    // Funkcja zawracaj¹ca poprzednika danego wêz³a (poprzedni wêze³ co do wielkoœci
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

    Node* root; // WskaŸnik na korzeñ drzewa BST
    std::pair<uint, uint> bounds; // Para liczb bêd¹ca granicami drzewa
    uint estimate; // Szacowana wartoœæ docelowa

    // Funkcja zwracaj¹ca wskaŸnik na wêze³ o podanym kluczu
    Node* find_node(uint key) {
        Node* pos = root;
        while(pos && pos->key != key) {
            pos = (pos->key < key ? pos->right_child : pos->left_child);
        }
        return pos;
    }

    // Funkcja dodaj¹ca do drzewa nowy wêze³ o podanym kluczu
    void add_node(uint key) {
        Node* new_node = new Node(key);
        if(root == nullptr) root = new_node;
        else root->add_child(new_node);
    }

    // Funkcja usuwaj¹ca wêze³ o podanym kluczu z drzewa
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

    // Funkcja usuwaj¹ca podany w argumencie wêze³ wrac ze wszysktimi jego potomkami
    void delete_subtree(Node* node) {
        if(node == nullptr) return;
        if(node->left_child) delete_subtree(node->left_child);
        if(node->right_child) delete_subtree(node->right_child);
        if(node->parent) node->parent->detach_child(node);
        delete node;
    }

    // Funkcja przycinaj¹ca wêze³ i wszystkich jego potomków oraz zwracaj¹ca wskaŸnik na nowy wêze³ w jego miejscu
    Node* trimmed_node(Node* node) {
        if(node == nullptr) return nullptr;
        if(node->key < bounds.first) { // Klucz mniejszy ni¿ dolna granica
            delete_subtree(node->left_child);
            Node* trimmed_right = trimmed_node(node->right_child);
            if(trimmed_right) trimmed_right->parent = node->parent;
            delete node;
            return trimmed_right;
        } else if(node->key > bounds.second) { // Klucz wiêkszy ni¿ górna granica
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

    // Funkcja zamieniaj¹ca miejscami dwa wêz³y
    void swap_nodes(Node*& a, Node*& b) {
        uint tkey = a->key;
        a->key = b->key;
        b->key = tkey;
        Node* tnode = a;
        a = b;
        b = tnode;
    }

    // Funkcja zwracaj¹ca, czy znaleziono parê dla danego wêz³a lub wêz³a potomnego i wypisuj¹ca j¹ w takowym przypadku
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

    // Kontruktor przyjmuj¹cy liczbê tropów i wczytuj¹cy resztê danych
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

    // Funkcja wypisuj¹ca parê liczb bêd¹cych kluczami dwóch poszukiwanych tropów
    // Wypisuje NIE ZNALEZIONO gdy takie nie bêd¹ znalezione
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