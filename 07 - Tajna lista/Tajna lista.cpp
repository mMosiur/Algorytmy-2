#include <iostream>

typedef unsigned short ushort;
typedef unsigned int uint;

// Klasa drzewa czerwono-czarnego z wbudowan� list�
class RedBlackListTree {
    // Struktura w�z�a w drzewie czerwono czarnym z wbudowanym w�z�em listy
    struct RedBlackListTreeNode {
        enum class Color { RED, BLACK }; // Enum koloru w�z�a
        std::string key; // Klucz w�z�a
        Color color; // Kolor w�z�a
        RedBlackListTreeNode* parent; // Wska�nik na rodzica w�z�a
        RedBlackListTreeNode* left; // Wska�nik na lewe dziecko w�z�a
        RedBlackListTreeNode* right; // Wska�nik na prawe dziecko w�z�a
        RedBlackListTreeNode* prev; // Wska�nik na poprzedni element listy
        RedBlackListTreeNode* next; // Wska�nik na nast�pny element listy

        // Konstruktor przyjmuj�cy klucz i warto�� w�z�a oraz inicjalizuj�cy zmienne w w�le
        RedBlackListTreeNode(std::string key) : key(key), color(RedBlackListTreeNode::Color::RED), parent(nullptr), left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {}

        // Funkcja zwracaj�ca, czy w�ze� jest lewym dzieckiem (false gdy nie ma rodzica)
        bool is_left() {
            if(parent && this == parent->left) return true;
            return false;
        }

        // Funkcja zwracaj�ca, czy w�ze� jest prawym dzieckiem (false gdy nie ma rodzica)
        bool is_right() {
            if(parent && this == parent->right) return true;
            return false;
        }

        // Funkcja zwracaj�ca wska�nik na brata tego w�z�a (nullptr gdy nie ma brata)
        RedBlackListTreeNode* brother() {
            if(!parent) return nullptr;
            if(is_left()) return parent->right;
            return parent->left;
        }
        
        // Funkcja dodaj�ca dziecko do tego w�z�a, lub do jednego z dzieci tego w�z�a
        void add_child(RedBlackListTreeNode*& node) {
            if(node->key < key) { // Klucz mniejszy od tego w�z�a
                if(left) left->add_child(node);
                else {
                    node->parent = this;
                    left = node;
                }
            } else { // Klucz wi�kszy ni� tego w�z�a
                if(right) right->add_child(node);
                else {
                    node->parent = this;
                    right = node;
                }
            }
        }
    };
    typedef RedBlackListTreeNode Node;

    Node* tree_root; // Wska�nik na korze� drzewa
    Node* list_first; // Wska�nik na pierwszy element listy
    Node* list_last; // Wska�nik na ostatni element listy

    // Funkcja wykonuj�ca rotacj� w lewo danego w�z�a
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

    // Funkcja wykonuj�ca rotacj� w prawo danego w�z�a
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

    // Funkcja zwracaj�ca wska�nik na w�ze� o podanym kluczu (nullptr gdy nie znaleziono)
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

    // Operacja wstawienia w�z�a o podanym kluczu do drzewa
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

    // Operacja zamieniaj�ca pozycjami w�z�y o podanych kluczach w li�cie
    void swap_nodes_in_list(std::string key1, std::string key2) {
        Node* node1 = find(key1);
        Node* node2 = find(key2);
        if(node1 == node2->next || node2 == node1->next) { // W�z�y s� s�siaduj�ce
            Node* first = (node1 == node2->next ? node2 : node1);
            Node* second = (node1 == node2->next ? node1 : node2);
            second->prev = first->prev;
            first->prev = second;
            first->next = second->next;
            second->next = first;
        } else { // W�z�y nie s� s�siaduj�ce
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

    // Przesuwa w�ze� o podanym kluczu o podan� liczb� miejsc (ujemne w lewo, dodatnie w prawo)
    void move_key_by(std::string key, int offset) {
        Node* node = find(key);
        Node* new_next_node = node;
        // Znalezienie w�z�a, kt�ry b�dzie nowym nast�pcom przesuwanego w�z�a (nullptr oznacza, �e przesuwamy na koniec)
        if(offset < 0) {
            offset = -offset;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->prev;
        } else {
            new_next_node = new_next_node->next;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->next;
        }
        // Wypinamy przesuwany w�ze� z listy
        if(node->prev) node->prev->next = node->next;
        else list_first = node->next;
        if(node->next) node->next->prev = node->prev;
        else if(node->prev) list_last = node->prev;
        else throw;
        // Wpinamy przesuwany w�ze� w odpowiednie miejsce
        if(new_next_node == nullptr) { // Wpinamy na koniec
            list_last->next = node;
            node->prev = list_last;
            list_last = node;
        } else { // Wpinamy przed nowy nast�pny w�ze�
            node->next = new_next_node;
            node->prev = new_next_node->prev;
            if(new_next_node->prev) new_next_node->prev->next = node;
            else list_first = node;
            new_next_node->prev = node;
        }
    }

    // Wypisujemy list�
    void print() const {
        Node* pos = list_first;
        while(pos) {
            std::cout << pos->key << std::endl;
            pos = pos->next;
        }
    }
};

// Klasa listy os�b 
class List {
    RedBlackListTree tree; // Drzewo czerwono czarne z wbudowan� list�

    // Funkcja wykonuj�ca komend� 'a' - dodaj�ca do drzewa osob� o podanym pseudonimie
    void add(std::string name) {
        tree.insert(name);
    }

    // Funkcja wykonuj�ca komend� 'm' - przesuwaj�ca osob� o podanym pseudonimie o dan� liczb� miejsc
    void move(std::string name, int offset) {
        tree.move_key_by(name, -offset);
    }

    // Funkcja wykonuj�ca komend� 'r' - zamieniaj�ca osoby o podanych pseudonimach miejscami w li�cie
    void swap(std::string name1, std::string name2) {
        tree.swap_nodes_in_list(name1, name2);
    }

public:

    // Konstruktor przujmyj�cy liczb� os�b i wczytuj�cy ich pseudonimy do drzewa
    List(ushort nof_people) {
        for(ushort i = 0; i < nof_people; i++) {
            std::string name;
            std::cin >> name;
            add(name);
        }
    }

    // Funkcja przyjmuj�ca liczb� operacji do wykonania, nast�pnie wczytujaca dane tych operacji i wykonuj�ca je
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

    // Funkcja wypisuj�ca list�
    void print() {
        tree.print();
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    ushort n; // Pocz�tkowa liczba os�b na li�cie
    std::cin >> n;
    List lista(n); // Obiekt listy
    ushort m; // Liczba operacji
    std::cin >> m;
    lista.execute_operations(m); // Wykonaj operacje
    lista.print(); // Wypisz zawarto�� listy

    return 0;
}