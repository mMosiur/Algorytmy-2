#include <iostream>

typedef unsigned short ushort;
typedef unsigned int uint;

// Klasa drzewa czerwono-czarnego z wbudowaną listą
class RedBlackListTree {
    // Struktura węzła w drzewie czerwono czarnym z wbudowanym węzłem listy
    struct RedBlackListTreeNode {
        enum class Color { RED, BLACK }; // Enum koloru węzła
        std::string key; // Klucz węzła
        Color color; // Kolor węzła
        RedBlackListTreeNode* parent; // Wskaźnik na rodzica węzła
        RedBlackListTreeNode* left; // Wskaźnik na lewe dziecko węzła
        RedBlackListTreeNode* right; // Wskaźnik na prawe dziecko węzła
        RedBlackListTreeNode* prev; // Wskaźnik na poprzedni element listy
        RedBlackListTreeNode* next; // Wskaźnik na następny element listy

        // Konstruktor przyjmujący klucz i wartość węzła oraz inicjalizujący zmienne w węźle
        RedBlackListTreeNode(std::string key) : key(key), color(RedBlackListTreeNode::Color::RED), parent(nullptr), left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {}

        // Funkcja zwracająca, czy węzeł jest lewym dzieckiem (false gdy nie ma rodzica)
        bool is_left() {
            if(parent && this == parent->left) return true;
            return false;
        }

        // Funkcja zwracająca, czy węzeł jest prawym dzieckiem (false gdy nie ma rodzica)
        bool is_right() {
            if(parent && this == parent->right) return true;
            return false;
        }

        // Funkcja zwracająca wskaźnik na brata tego węzła (nullptr gdy nie ma brata)
        RedBlackListTreeNode* brother() {
            if(!parent) return nullptr;
            if(is_left()) return parent->right;
            return parent->left;
        }
        
        // Funkcja dodająca dziecko do tego węzła, lub do jednego z dzieci tego węzła
        void add_child(RedBlackListTreeNode*& node) {
            if(node->key < key) { // Klucz mniejszy od tego węzła
                if(left) left->add_child(node);
                else {
                    node->parent = this;
                    left = node;
                }
            } else { // Klucz większy niż tego węzła
                if(right) right->add_child(node);
                else {
                    node->parent = this;
                    right = node;
                }
            }
        }
    };
    typedef RedBlackListTreeNode Node;

    Node* tree_root; // Wskaźnik na korzeń drzewa
    Node* list_first; // Wskaźnik na pierwszy element listy
    Node* list_last; // Wskaźnik na ostatni element listy

    // Funkcja wykonująca rotację w lewo danego węzła
    void rotate_left(Node*& node) {
        Node* pivot = node->right;
        node->right = pivot->left;
        if(pivot->left) pivot->left->parent = node;
        pivot->parent = node->parent;
        if(node->is_right()) {
            node->parent->right = pivot;
        } else if(node->is_left()) {
            node->parent->left = pivot;
        } else { // node->parent == nullptr
            tree_root = pivot;
        }
        pivot->left = node;
        node->parent = pivot;
    }

    // Funkcja wykonująca rotację w prawo danego węzła
    void rotate_right(Node*& node) {
        Node* pivot = node->left;
        node->left = pivot->right;
        if(pivot->right) pivot->right->parent = node;
        pivot->parent = node->parent;
        if(node->is_left()) {
            node->parent->left = pivot;
        } else if(node->is_right()) {
            node->parent->right = pivot;
        } else { // node->parent == nullptr
            tree_root = pivot;
        }
        pivot->right = node;
        node->parent = pivot;
    }

    // Funkcja zwracająca wskaźnik na węzeł o podanym kluczu (nullptr gdy nie znaleziono)
    Node* find(std::string key) {
        Node* pos = tree_root;
        while(pos && pos->key != key) {
            if(key < pos->key) pos = pos->left;
            else pos = pos->right;
        }
        return pos;
    }

public:
    RedBlackListTree() : tree_root(nullptr), list_first(nullptr), list_last(nullptr) {}
    ~RedBlackListTree() {
        Node* pos = list_first;
        while(pos){
            Node* next = pos->next;
            delete pos;
            pos = next;
        }
    }

    // Operacja wstawienia węzła o podanym kluczu do drzewa
    void insert(std::string key) {
        Node* node = new Node(key);
        if(tree_root == nullptr) {
            // Lista
            list_first = node;
            list_last = node;
            // Drzewo
            tree_root = node;
            tree_root->color = Node::Color::BLACK;
        } else {
            // Lista
            list_last->next = node;
            node->prev = list_last;
            list_last = node;
            // Drzewo
            tree_root->add_child(node);
            while(node != tree_root && node->parent->color != Node::Color::BLACK) {
                Node* parent = node->parent;
                Node* grandparent = parent->parent;
                Node* uncle = parent->brother();
                if(uncle && uncle->color == Node::Color::RED) { // Wujek jest Czerwony
                    parent->color = Node::Color::BLACK;
                    uncle->color = Node::Color::BLACK;
                    grandparent->color = Node::Color::RED;
                    node = grandparent;
                } else { // Wujek jest Czarny
                    if(parent->is_left()) { // Rodzic jest lewym dzieckiem
                        if(node->is_right()) rotate_left(parent);
                        rotate_right(grandparent);
                    } else { // Rodzic jest prawym dzieckiem
                        if(node->is_left()) rotate_right(parent);
                        rotate_left(grandparent);
                    }
                    std::swap(grandparent->color, grandparent->parent->color);
                }
            }
            tree_root->color = Node::Color::BLACK;
        }
    }

    // Operacja zamieniająca pozycjami węzły o podanych kluczach w liście
    void swap_nodes_in_list(std::string key1, std::string key2) {
        Node* node1 = find(key1);
        Node* node2 = find(key2);
        if(node1 == node2->next || node2 == node1->next) { // Węzły są sąsiadujące
            Node* first = (node1 == node2->next ? node2 : node1);
            Node* second = (node1 == node2->next ? node1 : node2);
            second->prev = first->prev;
            first->prev = second;
            first->next = second->next;
            second->next = first;
        } else { // Węzły nie są sąsiadujące
            std::swap(node1->next, node2->next);
            std::swap(node1->prev, node2->prev);
        }
        if(node1->prev) node1->prev->next = node1;
        else list_first = node1;
        if(node1->next) node1->next->prev = node1;
        else list_last = node1;
        if(node2->prev) node2->prev->next = node2;
        else list_first = node2;
        if(node2->next) node2->next->prev = node2;
        else list_last = node2;
    }

    // Przesuwa węzeł o podanym kluczu o podaną liczbę miejsc (ujemne w lewo, dodatnie w prawo)
    void move_key_by(std::string key, int offset) {
        Node* node = find(key);
        Node* new_next_node = node;
        // Znalezienie węzła, który będzie nowym następcom przesuwanego węzła (nullptr oznacza, że przesuwamy na koniec)
        if(offset < 0) {
            offset = -offset;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->prev;
        } else {
            new_next_node = new_next_node->next;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->next;
        }
        // Wypinamy przesuwany węzeł z listy
        if(node->prev) node->prev->next = node->next;
        else list_first = node->next;
        if(node->next) node->next->prev = node->prev;
        else if(node->prev) list_last = node->prev;
        else throw;
        // Wpinamy przesuwany węzeł w odpowiednie miejsce
        if(new_next_node == nullptr) { // Wpinamy na koniec
            list_last->next = node;
            node->prev = list_last;
            list_last = node;
        } else { // Wpinamy przed nowy następny węzeł
            node->next = new_next_node;
            node->prev = new_next_node->prev;
            if(new_next_node->prev) new_next_node->prev->next = node;
            else list_first = node;
            new_next_node->prev = node;
        }
    }

    // Wypisujemy listę
    void print() const {
        Node* pos = list_first;
        while(pos) {
            std::cout << pos->key << std::endl;
            pos = pos->next;
        }
    }
};

// Klasa listy osób 
class List {
    RedBlackListTree tree; // Drzewo czerwono czarne z wbudowaną listą

    // Funkcja wykonująca komendę 'a' - dodająca do drzewa osobę o podanym pseudonimie
    void add(std::string name) {
        tree.insert(name);
    }

    // Funkcja wykonująca komendę 'm' - przesuwająca osobę o podanym pseudonimie o daną liczbę miejsc
    void move(std::string name, int offset) {
        tree.move_key_by(name, -offset);
    }

    // Funkcja wykonująca komendę 'r' - zamieniająca osoby o podanych pseudonimach miejscami w liście
    void swap(std::string name1, std::string name2) {
        tree.swap_nodes_in_list(name1, name2);
    }

public:

    // Konstruktor przujmyjący liczbę osób i wczytujący ich pseudonimy do drzewa
    List(ushort nof_people) {
        for(ushort i = 0; i < nof_people; i++) {
            std::string name;
            std::cin >> name;
            add(name);
        }
    }

    // Funkcja przyjmująca liczbę operacji do wykonania, następnie wczytujaca dane tych operacji i wykonująca je
    void execute_operations(ushort nof_operations) {
        for(ushort i = 0; i < nof_operations; i++) {
            char operation;
            std::cin >> operation;
            switch(operation) {
            case 'a': {
                std::string s;
                std::cin >> s;
                add(s);
                break;
            }
            case 'm': {
                std::string s;
                int x;
                std::cin >> s >> x;
                move(s, x);
                break;
            }
            case 'r': {
                std::string s1;
                std::string s2;
                std::cin >> s1 >> s2;
                swap(s1, s2);
                break;
            }
            }
        }
    }

    // Funkcja wypisująca listę
    void print() {
        tree.print();
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    ushort n; // Początkowa liczba osób na liście
    std::cin >> n;
    List lista(n); // Obiekt listy
    ushort m; // Liczba operacji
    std::cin >> m;
    lista.execute_operations(m); // Wykonaj operacje
    lista.print(); // Wypisz zawartość listy

    return 0;
}