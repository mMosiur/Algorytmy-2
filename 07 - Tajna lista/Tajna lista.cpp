#include <iostream>

typedef unsigned short ushort;
typedef unsigned int uint;

// Klasa drzewa czerwono-czarnego
class RBTree {

    // Struktura wêz³a w drzewie czerwono czarnym
    struct Node {
        enum class Color { RED, BLACK }; // Enum koloru wêz³a
        std::string key; // Klucz wêz³a
        uint value; // Wartoœæ wêz³a
        Color color; // Kolor wêz³a
        Node* parent; // WskaŸnik na rodzica wêz³a
        Node* left; // WskaŸnik na lewe dziecko wêz³a
        Node* right; // WskaŸnik na prawe dziecko wêz³a

        // Konstruktor przyjmuj¹cy klucz i wartoœæ wêz³a oraz inicjalizuj¹cy zmienne w wêŸle
        Node(std::string key, uint value) : key(key), value(value), color(Node::Color::RED), parent(nullptr), left(nullptr), right(nullptr) {}

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
        Node* brother() {
            if(!parent) return nullptr;
            if(is_left()) return parent->right;
            return parent->left;
        }
        
        // Funkcja dodaj¹ca dziecko do tego wêz³a, lub do jednego z dzieci tego wêz³a
        void add_child(Node*& node) {
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

    Node* root; // WskaŸnik na korzeñ drzewa
    uint nof_elements; // Iloœæ elementów w drzewie

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
            root = pivot;
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
            root = pivot;
        }
        pivot->right = node;
        node->parent = pivot;
    }

    // Funkcja dodaj¹ca do listy z pierwszego argumentu podany wêze³ i tworzone przez niego poddrzewo
    void add_to_list(std::string*& list, Node*& node) {
        list[node->value] = node->key;
        if(node->left) add_to_list(list, node->left);
        if(node->right) add_to_list(list, node->right);
    }

    // Funkcja zwracaj¹ca wskaŸnik na wêze³ o podanym kluczu (nullptr gdy nie znaleziono)
    Node* find(std::string key) {
        Node* pos = root;
        while(pos && pos->key != key) {
            if(key < pos->key) pos = pos->left;
            else pos = pos->right;
        }
        return pos;
    }

    // Funkcja usuwaj¹ca poddrzewo o korzeniu w podanym wêŸle
    void delete_subtree(Node*& node) {
        if(node->left) delete_subtree(node->left);
        if(node->right) delete_subtree(node->right);
        delete node;
    }

    // Funkcja inkrementuj¹ca wartoœci wszystkich wêz³ów w poddrzewie o podanym korzeniu
    void increment_subtree_if_value_between(Node* node, const uint lower, const uint upper) {
        if(lower <= node->value && node->value <= upper) node->value++;
        if(node->left) increment_subtree_if_value_between(node->left, lower, upper);
        if(node->right) increment_subtree_if_value_between(node->right, lower, upper);
    }

    void decrement_subtree_if_value_between(Node* node, const uint lower, const uint upper) {
        if(lower <= node->value && node->value <= upper) node->value--;
        if(node->left) decrement_subtree_if_value_between(node->left, lower, upper);
        if(node->right) decrement_subtree_if_value_between(node->right, lower, upper);
    }

public:
    RBTree() : root(nullptr), nof_elements(0) {}
    ~RBTree() { if(root) delete_subtree(root); }

    uint size() {
        return nof_elements;
    }

    void insert(std::string key, uint value) {
        Node* node = new Node(key, value);
        if(root == nullptr) {
            root = node;
            root->color = Node::Color::BLACK;
        } else {
            root->add_child(node);
            while(node != root && node->parent->color != Node::Color::BLACK) {
                Node* parent = node->parent;
                Node* grandparent = parent->parent;
                Node* uncle = parent->brother();
                if(uncle && uncle->color == Node::Color::RED) { // Uncle is RED
                    parent->color = Node::Color::BLACK;
                    uncle->color = Node::Color::BLACK;
                    grandparent->color = Node::Color::RED;
                    node = grandparent;
                } else { // Uncle is BLACK
                    if(parent->is_left()) { // Parent is a LEFT child
                        if(node->is_right()) rotate_left(parent);
                        rotate_right(grandparent);
                    } else { // Parent is a RIGHT child
                        if(node->is_left()) rotate_right(parent);
                        rotate_left(grandparent);
                    }
                    std::swap(grandparent->color, grandparent->parent->color);
                }
            }
            root->color = Node::Color::BLACK;
        }
        nof_elements++;
    }

    void swap_values(std::string key1, std::string key2) {
        Node* node1 = find(key1);
        Node* node2 = find(key2);
        std::swap(node1->value, node2->value);
    }

    void move_key_by(std::string key, int offset) {
        Node* node = find(key);
        uint lower, upper;
        if(offset < 0) {
            upper = node->value - 1;
            lower = node->value + offset;
            increment_subtree_if_value_between(root, lower, upper);
        } else {
            lower = node->value + 1;
            upper = node->value + offset;
            decrement_subtree_if_value_between(root, lower, upper);
        }
        node->value += offset;
    }

    void print() {
        std::string* list = new std::string[nof_elements];
        add_to_list(list, root);
        for(uint i = 0; i < nof_elements; i++) {
            std::cout << list[i] << std::endl;
        }
    }
};

class List {
    RBTree tree;

    void add(std::string name) { // Komenda 'a'
        tree.insert(name, tree.size());
    }

    void move(std::string name, int offset) { // Komenda 'm'
        tree.move_key_by(name, -offset);
    }

    void swap(std::string name1, std::string name2) { // Komenda 'r'
        tree.swap_values(name1, name2);
    }

public:

    List(ushort nof_people) {
        for(ushort i = 0; i < nof_people; i++) {
            std::string name;
            std::cin >> name;
            add(name);
        }
    }

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