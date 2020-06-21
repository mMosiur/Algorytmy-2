#include <iostream>
#include <array>

typedef unsigned short ushort;
typedef unsigned int uint;

constexpr ushort T = 16; // Parametr T charakterystyczny dla b-drzewa
constexpr ushort MIN_ITEMS = T - 1; // Minimalna liczba kluczy dla danego węzła (nie licząc korzenia)
constexpr ushort MAX_ITEMS = 2 * T - 1; // Maksymalna liczba kluczy dla danego węzła
constexpr ushort MIN_CHILDREN = T; // Minimalna liczba dzieci danego węzła (nie licząc korzenia)
constexpr ushort MAX_CHILDREN = 2 * T; // Maksymalna liczba dzieci danego węzła

// Struktura reprezentująca pojedynczy element przechowywany w węźle b-drzewa
struct Item {
    const double key; // Klucz elementu
    const std::string value; // Wartość elementu

    // Konstruktor przyjmujący i inicjalizujący zmienne
    Item(const double key, const std::string value) : key(key), value(value) {}

    // Funkcja wypisująca wartość elementu, jeżeli jej klucz mieści się między podanymi wartościami
    void print_if_between(const double lower_bound, const double upper_bound) const {
        if(key < lower_bound) return;
        if(key > upper_bound) return;
        std::cout << value << "\n";
    }
};

// Klasa reprezentująca b-drzewo
class BTree {

    // Struktura węzeła b-drzewa
    struct Node {
        std::array<const Item*, MAX_ITEMS> items; // Tablica wskaźników na elementy trzymane w danym węźle
        ushort nof_items; // Ilość elementów aktualnie znajdujących się w węźle
        std::array<Node*, MAX_CHILDREN> children; // Tablica wskaźników na dzieci danego węzła
        Node* parent; // Wskaźnik na rodzica danego węzła
        bool is_leaf; // Zmienna wskazująca, czy dany węzeł jest liściem

        // Konstruktor przyjmujący dane i inicjalizujący zmienne
        Node() : is_leaf(true), parent(nullptr), nof_items(0) {
            items.fill(nullptr);
            children.fill(nullptr);
        }

        // Funkcja wstawiająca w daną pozycję w węźle nullptr, włącznie/wyłącznie z najbardziej lewym dzieckiem
        void insert_nullptr_at(ushort position, bool most_left_child_inclusive = false) {
            if(items[position] == nullptr) return;
            for(ushort last = nof_items; last > position; last--) {
                items[last] = items[last - 1];
                children[last + 1] = children[last];
            }
            items[position] = nullptr;
            if(most_left_child_inclusive) {
                children[position + 1] = children[position];
                children[position] = nullptr;
            } else {
                children[position + 1] = nullptr;
            }
        }

        // Funkcja wypełniająca nullptr na danej pozycji, przesuwająca elementy w lewo (wraz z dekrementacją ilości elementów)
        void fill_nullptr_at(ushort position) {
            nof_items--;
            while(position < nof_items) {
                items[position] = items[position + 1];
                children[position] = children[position + 1];
                position++;
            }
            children[position] = children[position + 1];
            items[position] = nullptr;
            children[position + 1] = nullptr;
        }

        // Funkcja dzieląca dany węzeł na dwa
        void split() {
            Node* new_node = new Node();
            new_node->is_leaf = this->is_leaf;
            ushort sep = nof_items / 2;
            // Przesunięcie kluczy po prawej od środka do nowego węzła
            new_node->nof_items = sep;
            for(ushort i = 0; i < new_node->nof_items; i++) {
                new_node->items[i] = this->items[sep + 1 + i];
                this->items[sep + 1 + i] = nullptr;
            }
            this->nof_items -= sep;
            if(!is_leaf) {
                // Przesunięcie dzieci po prawej od środka do nowego węzła
                for(ushort i = 0; i <= new_node->nof_items; i++) {
                    new_node->children[i] = this->children[sep + 1 + i];
                    new_node->children[i]->parent = new_node;
                    this->children[sep + 1 + i] = nullptr;
                }
            }
            // Przesunięcie środkowego klucza do rodzica
            if(parent) {
                ushort pos = 0;
                while(parent->children[pos] != this) pos++;
                parent->insert_nullptr_at(pos);
                parent->children[pos + 1] = new_node;
                parent->nof_items++;
                new_node->parent = this->parent;
                parent->items[pos] = this->items[sep];
                this->items[sep] = nullptr;
                this->nof_items--;
            } else { // Brak rodzica
                Node* new_parent = new Node();
                new_parent->items[0] = items[sep];
                new_parent->nof_items = 1;
                items[sep] = nullptr;
                this->nof_items--;
                new_parent->children[0] = this;
                new_parent->children[1] = new_node;
                new_parent->is_leaf = false;
                this->parent = new_parent;
                new_node->parent = new_parent;
            }
        }

        // Funkcja przesuwająca element z brata po lewej do tego węzła
        void take_key_from_left(ushort pos_in_parent) {
            Node* brother = parent->children[pos_in_parent - 1];
            this->insert_nullptr_at(0, true);
            if(!is_leaf) {
                this->children[0] = brother->children[brother->nof_items];
                if(this->children[0]) this->children[0]->parent = this;
                brother->children[brother->nof_items] = nullptr;
            }
            this->items[0] = parent->items[pos_in_parent - 1];
            this->nof_items++;
            parent->items[pos_in_parent - 1] = brother->items[brother->nof_items - 1];
            brother->items[brother->nof_items - 1] = nullptr;
            brother->nof_items--;
        }

        // Funkcja przesuwająca element z brata po prawej do tego węzła
        void take_key_from_right(ushort pos_in_parent) {
            Node* brother = parent->children[pos_in_parent + 1];
            if(!is_leaf) {
                this->children[nof_items + 1] = brother->children[0];
                if(this->children[nof_items + 1]) this->children[nof_items + 1]->parent = this;
                brother->children[0] = nullptr;
            }
            this->items[nof_items] = parent->items[pos_in_parent];
            this->nof_items++;
            parent->items[pos_in_parent] = brother->items[0];
            brother->items[0] = nullptr;
            brother->fill_nullptr_at(0); // nof_items-- wewnątrz
        }

        // Funkcja scalająca dwójkę dzieci danego węzła na podanych pozycjach
        void merge_children(ushort pos_left, ushort pos_right) {
            Node* left = children[pos_left];
            Node* right = children[pos_right];
            left->items[left->nof_items] = this->items[pos_left];
            left->nof_items++;
            this->items[pos_left] = nullptr;
            for(ushort r = 0; r < right->nof_items; r++) {
                ushort l = r + left->nof_items;
                if(right->children[r]) {
                    left->children[l] = right->children[r];
                    left->children[l]->parent = left;
                }
                left->items[l] = right->items[r];
            }
            left->nof_items += right->nof_items;
            if(!left->is_leaf) {
                left->children[left->nof_items] = right->children[right->nof_items];
                left->children[left->nof_items]->parent = left;
            }
            delete right;
            this->children[pos_right] = left;
            this->children[pos_left] = nullptr;
            this->fill_nullptr_at(pos_left); // nof_items-- wewnątrz
        }
    
        // Funkcja usuwająca podany element (przesuwająca do liścia i usuwająca)
        void remove(const Item* const item) {
            ushort pos = 0;
            while(pos < nof_items) {
                if(items[pos] == item) break;
                pos++;
            }
            if(this->is_leaf) {
                while(pos < nof_items - 1) {
                    items[pos] = items[pos + 1];
                    pos++;
                }
                items[pos] = nullptr;
                nof_items--;
            } else {
                ushort left = pos;
                ushort right = left + 1;
                if(children[left]->nof_items == MIN_ITEMS) {
                    if(children[right]->nof_items == MIN_ITEMS) {
                        // Oba mają minimum kluczy
                        this->merge_children(left, right);
                        children[left]->remove(item);
                    } else {
                        // Tylko lewy ma minimum kluczy
                        std::swap(this->children[right]->items[0], this->items[pos]);
                        this->children[right]->remove(item);
                    }
                } else {
                    if(children[right]->nof_items == MIN_ITEMS) {
                        // Tylko prawy ma minimum kluczy
                        std::swap(this->children[left]->items[this->children[left]->nof_items-1], this->items[pos]);
                        this->children[left]->remove(item);
                    } else {
                        // Oba mają wystarczającą liczbę kluczy
                        ushort left_difference = abs(item->key - this->children[left]->items[this->children[left]->nof_items - 1]->key);
                        ushort right_difference = abs(item->key - this->children[right]->items[0]->key);
                        if(left_difference < right_difference) {
                            std::swap(this->children[right]->items[0], this->items[pos]);
                            this->children[right]->remove(item);
                        } else {
                            std::swap(this->children[left]->items[this->children[left]->nof_items - 1], this->items[pos]);
                            this->children[left]->remove(item);
                        }
                    }
                }
            }
        }

        // Funkcja usuwająca element o podanym kluczu
        const Item* remove(const double key) {
            ushort pos = 0;
            while(pos < nof_items && items[pos]->key < key) pos++;
            if(pos < nof_items && items[pos]->key == key) {
                const Item* item = items[pos];
                remove(item);
                return item;
            } else {
                if(is_leaf) return nullptr;
                if(children[pos]->nof_items == MIN_ITEMS) {
                    if(pos > 0 && children[pos - 1]->nof_items > MIN_ITEMS) {
                        children[pos]->take_key_from_left(pos);
                    } else if(pos < nof_items && children[pos + 1]->nof_items > MIN_ITEMS) {
                        children[pos]->take_key_from_right(pos);
                    } else { // Nie da się pożyczyć od braci
                        if(pos == nof_items) {
                            merge_children(pos - 1, pos);
                            pos--;
                        } else {
                            merge_children(pos, pos + 1);
                        }
                    }
                }
                return children[pos]->remove(key);
            }
        }

        // Funkcja zwracająca, czy dany węzeł jest pełny
        bool is_full() {
            return nof_items == items.size();
        }

        // Funkcja wstawiająca podany element do węzła (albo jednego z jego dzieci) w odpowiednie miejsce
        void insert(const Item* const item) {
            if(is_full()) {
                this->split();
                parent->insert(item);
            } else {
                if(is_leaf) { // Węzeł jest liściem
                    ushort pos = 0;
                    while(items[pos] && items[pos]->key <= item->key) pos++;
                    for(ushort end_pos = nof_items; end_pos > pos; end_pos--) items[end_pos] = items[end_pos - 1];
                    items[pos] = item;
                    nof_items++;
                } else { // Węzeł nie jest liściem
                    ushort pos = 0;
                    while(pos < nof_items && items[pos]->key <= item->key) pos++;
                    children[pos]->insert(item);
                }
            }
        }

        // Funkcja rekurencyjnie wypisująca wszysktie elementy tego węzła i jego dzieci, które mieszczą się w podanym przedziale w kolejności malejącej
        void print_if_between(const double lower_bound, const double upper_bound) const {
            if(this->is_leaf) {
                for(int pos = nof_items - 1; pos >= 0; pos--) {
                    items[pos]->print_if_between(lower_bound, upper_bound);
                }
            } else {
                children[nof_items]->print_if_between(lower_bound, upper_bound);
                for(int pos = nof_items - 1; pos >= 0; pos--) {
                    items[pos]->print_if_between(lower_bound, upper_bound);
                    children[pos]->print_if_between(lower_bound, upper_bound);
                }
            }
        }
    };
    
    Node* root; // Wskaźnik na korzeń drzewa

public:

    // Konstruktor inicjalizujący zmienne
    BTree() : root(nullptr) {}

    // Funkcja wstawiająca do drzewa węzeł o podanym kluczu i wartości
    void insert(const double key, const std::string value) {
        const Item* new_item = new Item(key, value);
        if(root == nullptr) { // Drzewo jest puste
            root = new Node();
        }
        root->insert(new_item);
        if(root->parent) root = root->parent;
    }

    // Funkcja usuwająca z drzewa element o podanym kluczu i zwracająca go
    const Item* remove(const double key) {
        const Item* item = nullptr;
        if(root != nullptr) {
            item = root->remove(key);
            if(root->nof_items == 0) {
                if(root->is_leaf) {
                    delete root;
                    root = nullptr;
                } else {
                    root = root->children[0];
                    delete root->parent;
                    root->parent = nullptr;
                }
            }
        }
        return item;
    }

    // Funkcja wypisująca wszystkie elementy drzewa mieszczące się w podanym zakresie
    void print_between(const double lower_bound, const double upper_bound) const {
        root->print_if_between(lower_bound, upper_bound);
    }
    
};

// Klasa rankigu osób
class Ranking {

    BTree tree; // B-drzewo

    // Dodanie osoby o podanej nazwie i współczynniku niebezpieczeństwa
    void add_person(const std::string& name, const double& factor) {
        tree.insert(factor, name);
    }

    // Modyfikacja osoby o podanym współczynniku na nowy współczynnik
    void modify(const double old_key, const double new_key) {
        const Item* item = tree.remove(old_key);
        tree.insert(new_key, item->value);
        delete item;
    }

    // Wypisanie wszystkich osób w rankingu mieszczących się w podanym zakresie
    void print_between(const double lower_bound, const double upper_bound) {
        tree.print_between(lower_bound, upper_bound);
    }

public:

    // Konstruktor przyjmujący liczbę osób, wczytujący ich dane i dodający do drzewa
    Ranking(uint nof_people) {
        for(uint i = 0; i < nof_people; i++) {
            std::string s; // Pseudonim
            double x; // Współczynnik
            std::cin >> s >> x;
            add_person(s, x);
        }
    }

    // Funkcja przyjmująca liczbę operacji a następnie je wykonująca
    void execute_operations(ushort nof_operations) {
        for(ushort i = 0; i < nof_operations; i++) {
            char op;
            std::cin >> op;
            switch(op) {
            case 'a': { // Operacja 'a' - dodaj nową osobę
                std::string s;
                double x;
                std::cin >> s >> x;
                add_person(s, x);
                break;
            }
            case 'm': { // Operacja 'm' - zmień wartość współczynnika
                double x1, x2;
                std::cin >> x1 >> x2;
                modify(x1, x2);
                break;
            }
            case 's': { // Operacja 's' - wypisz osoby
                double x1, x2;
                std::cin >> x1 >> x2;
                print_between(x1, x2);
                break;
            }
            default: {
                exit(1);
                break;
            }
            }
        }
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    uint n; // Początkowa liczba osób na liście
    std::cin >> n;

    Ranking ranking(n);

    ushort m; // Ilość operacji do wykonania
    std::cin >> m;

    ranking.execute_operations(m);

    return 0;
}