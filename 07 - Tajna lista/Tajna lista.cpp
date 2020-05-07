#include <iostream>

typedef unsigned short ushort;
typedef unsigned int uint;

// Klasa drzewa czerwono-czarnego z wbudowan¹ list¹
class RedBlackListTree {
    // Struktura wêz³a w drzewie czerwono czarnym z wbudowanym wêz³em listy
    struct RedBlackListTreeNode {
        enum class Color { RED, BLACK }; // Enum koloru wêz³a
        std::string key; // Klucz wêz³a
        Color color; // Kolor wêz³a
        RedBlackListTreeNode* parent; // WskaŸnik na rodzica wêz³a
        RedBlackListTreeNode* left; // WskaŸnik na lewe dziecko wêz³a
        RedBlackListTreeNode* right; // WskaŸnik na prawe dziecko wêz³a
        RedBlackListTreeNode* prev; // WskaŸnik na poprzedni element listy
        RedBlackListTreeNode* next; // WskaŸnik na nastêpny element listy

        // Konstruktor przyjmuj¹cy klucz i wartoœæ wêz³a oraz inicjalizuj¹cy zmienne w wêŸle
        RedBlackListTreeNode(std::string key) : key(key), color(RedBlackListTreeNode::Color::RED), parent(nullptr), left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {}

        // Funkcja zwracaj¹ca, czy wêze³ jest lewym dzieckiem (false gdy nie ma rodzica)
        bool is_left() {
            if(parent && this == parent->left) return true;
            return false;
        }

        // Funkcja zwracaj¹ca, czy wêze³ jest prawym dzieckiem (false gdy nie ma rodzica)
        bool is_right() {
            if(parent && this == parent->right) return true;
            return false;
        }

        // Funkcja zwracaj¹ca wskaŸnik na brata tego wêz³a (nullptr gdy nie ma brata)
        RedBlackListTreeNode* brother() {
            if(!parent) return nullptr;
            if(is_left()) return parent->right;
            return parent->left;
        }
        
        // Funkcja dodaj¹ca dziecko do tego wêz³a, lub do jednego z dzieci tego wêz³a
        void add_child(RedBlackListTreeNode*& node) {
            if(node->key < key) { // Klucz mniejszy od tego wêz³a
                if(left) left->add_child(node);
                else {
                    node->parent = this;
                    left = node;
                }
            } else { // Klucz wiêkszy ni¿ tego wêz³a
                if(right) right->add_child(node);
                else {
                    node->parent = this;
                    right = node;
                }
            }
        }
    };
    typedef RedBlackListTreeNode Node;

    Node* tree_root; // WskaŸnik na korzeñ drzewa
    Node* list_first; // WskaŸnik na pierwszy element listy
    Node* list_last; // WskaŸnik na ostatni element listy

    // Funkcja wykonuj¹ca rotacjê w lewo danego wêz³a
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

    // Funkcja wykonuj¹ca rotacjê w prawo danego wêz³a
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

    // Funkcja zwracaj¹ca wskaŸnik na wêze³ o podanym kluczu (nullptr gdy nie znaleziono)
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

    // Operacja wstawienia wêz³a o podanym kluczu do drzewa
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

    // Operacja zamieniaj¹ca pozycjami wêz³y o podanych kluczach w liœcie
    void swap_nodes_in_list(std::string key1, std::string key2) {
        Node* node1 = find(key1);
        Node* node2 = find(key2);
        if(node1 == node2->next || node2 == node1->next) { // Wêz³y s¹ s¹siaduj¹ce
            Node* first = (node1 == node2->next ? node2 : node1);
            Node* second = (node1 == node2->next ? node1 : node2);
            second->prev = first->prev;
            first->prev = second;
            first->next = second->next;
            second->next = first;
        } else { // Wêz³y nie s¹ s¹siaduj¹ce
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

    // Przesuwa wêze³ o podanym kluczu o podan¹ liczbê miejsc (ujemne w lewo, dodatnie w prawo)
    void move_key_by(std::string key, int offset) {
        Node* node = find(key);
        Node* new_next_node = node;
        // Znalezienie wêz³a, który bêdzie nowym nastêpcom przesuwanego wêz³a (nullptr oznacza, ¿e przesuwamy na koniec)
        if(offset < 0) {
            offset = -offset;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->prev;
        } else {
            new_next_node = new_next_node->next;
            for(ushort i = 0; i < offset; i++) new_next_node = new_next_node->next;
        }
        // Wypinamy przesuwany wêze³ z listy
        if(node->prev) node->prev->next = node->next;
        else list_first = node->next;
        if(node->next) node->next->prev = node->prev;
        else if(node->prev) list_last = node->prev;
        else throw;
        // Wpinamy przesuwany wêze³ w odpowiednie miejsce
        if(new_next_node == nullptr) { // Wpinamy na koniec
            list_last->next = node;
            node->prev = list_last;
            list_last = node;
        } else { // Wpinamy przed nowy nastêpny wêze³
            node->next = new_next_node;
            node->prev = new_next_node->prev;
            if(new_next_node->prev) new_next_node->prev->next = node;
            else list_first = node;
            new_next_node->prev = node;
        }
    }

    // Wypisujemy listê
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
    RedBlackListTree tree; // Drzewo czerwono czarne z wbudowan¹ list¹

    // Funkcja wykonuj¹ca komendê 'a' - dodaj¹ca do drzewa osobê o podanym pseudonimie
    void add(std::string name) {
        tree.insert(name);
    }

    // Funkcja wykonuj¹ca komendê 'm' - przesuwaj¹ca osobê o podanym pseudonimie o dan¹ liczbê miejsc
    void move(std::string name, int offset) {
        tree.move_key_by(name, -offset);
    }

    // Funkcja wykonuj¹ca komendê 'r' - zamieniaj¹ca osoby o podanych pseudonimach miejscami w liœcie
    void swap(std::string name1, std::string name2) {
        tree.swap_nodes_in_list(name1, name2);
    }

public:

    // Konstruktor przujmyj¹cy liczbê osób i wczytuj¹cy ich pseudonimy do drzewa
    List(ushort nof_people) {
        for(ushort i = 0; i < nof_people; i++) {
            std::string name;
            std::cin >> name;
            add(name);
        }
    }

    // Funkcja przyjmuj¹ca liczbê operacji do wykonania, nastêpnie wczytujaca dane tych operacji i wykonuj¹ca je
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

    // Funkcja wypisuj¹ca listê
    void print() {
        tree.print();
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    ushort n; // Pocz¹tkowa liczba osób na liœcie
    std::cin >> n;
    List lista(n); // Obiekt listy
    ushort m; // Liczba operacji
    std::cin >> m;
    lista.execute_operations(m); // Wykonaj operacje
    lista.print(); // Wypisz zawartoœæ listy

    return 0;
}