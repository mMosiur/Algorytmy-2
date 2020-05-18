#include <iostream>
#include <array>
//#include <vector>

void ASSERT(bool condition) {
    if(!condition) throw "Assertion error";
}

void ASSERTEXIT(bool condition) {
    if(!condition) exit(1);
}

typedef unsigned short ushort;
typedef unsigned int uint;

constexpr ushort T = 2;
constexpr ushort MIN_ITEMS = T - 1;
constexpr ushort MAX_ITEMS = 2 * T - 1;
constexpr ushort MIN_CHILDREN = T;
constexpr ushort MAX_CHILDREN = 2 * T;


struct Item {
    const double key;
    const std::string value;

    Item(const double key, const std::string value) : key(key), value(value) {}

    bool operator <(const Item& other) const {
        return this->key < other.key;
    }

    void print_if_between(const double lower_bound, const double upper_bound) const {
        if(key < lower_bound) return;
        if(key > upper_bound) return;
        std::cout << value << "\n";
    }
};

class Node {
    std::array<const Item*, MAX_ITEMS> items;
    ushort nof_items;
    std::array<Node*, MAX_CHILDREN> children;
    Node* parent;
    bool leaf;

    void insert_nullptr_at(ushort position, bool most_left_child_inclusive = false) {
        ASSERT(position < MAX_ITEMS);
        ASSERTEXIT(items[position] != nullptr);
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
        nof_items++;
    }

    void fill_nullptr_at(ushort position) {
        ASSERT(position < nof_items);
        ASSERT(items[position] == nullptr);
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

    int pos_in_parent() {
        if(!parent) return -1;
        int pos = 0;
        while(parent->children[pos] != this) pos++;
        return pos;
    }

    void split() {
        ASSERT(nof_items == MAX_ITEMS);
        Node* new_node = new Node();
        new_node->leaf = this->leaf;
        ushort sep = nof_items / 2;
        // Przesuniêcie kluczy po prawej od œrodka do nowego wêz³a
        new_node->nof_items = sep;
        for(ushort i = 0; i < new_node->nof_items; i++) {
            new_node->items[i] = this->items[sep + 1 + i];
            this->items[sep + 1 + i] = nullptr;
        }
        this->nof_items -= sep;
        if(!leaf) {
            // Przesuniêcie dzieci po prawej od œrodka do nowego wêz³a
            for(ushort i = 0; i <= new_node->nof_items; i++) {
                new_node->children[i] = this->children[sep + 1 + i];
                ASSERT(new_node->children[i] != nullptr);
                new_node->children[i]->parent = new_node;
                this->items[sep + 1 + i] = nullptr;
            }
        }
        // Przesuniêcie œrodkowego klucza do rodzica
        if(parent) {
            if(parent->full()) parent->split();
            ushort pos = this->pos_in_parent();
            parent->insert_nullptr_at(pos);
            parent->children[pos + 1] = new_node;
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
            new_parent->leaf = false;
            this->parent = new_parent;
            new_node->parent = new_parent;
        }
    }

    void take_key_from_left(int pos_in_parent = -1) {
        ASSERT(this->nof_items < MAX_ITEMS);
        if(pos_in_parent < 0) pos_in_parent = this->pos_in_parent();
        ASSERT(pos_in_parent > 0);
        Node* brother = parent->children[pos_in_parent - 1];
        ASSERT(brother->nof_items > MIN_ITEMS);
        this->insert_nullptr_at(0, true);
        this->children[0] = brother->children[nof_items + 1];
        if(this->children[0]) this->children[0]->parent = this;
        brother->children[nof_items + 1] = nullptr;
        this->items[0] = parent->items[pos_in_parent - 1];
        this->nof_items++;
        parent->items[pos_in_parent - 1] = brother->items[nof_items - 1];
        brother->items[nof_items - 1] = nullptr;
        brother->nof_items--;
    }

    void take_key_from_right(int pos_in_parent = -1) {
        ASSERT(this->nof_items < MAX_ITEMS);
        if(pos_in_parent < 0) pos_in_parent = this->pos_in_parent();
        ASSERT(pos_in_parent < parent->nof_items);
        Node* brother = parent->children[pos_in_parent + 1];
        ASSERT(brother->nof_items > MIN_ITEMS);
        this->children[nof_items + 1] = brother->children[0];
        if(this->children[nof_items + 1]) this->children[nof_items + 1]->parent = this;
        brother->children[0] = nullptr;
        this->items[nof_items] = parent->items[pos_in_parent];
        this->nof_items++;
        parent->items[pos_in_parent] = brother->items[0];
        brother->items[0] = nullptr;
        brother->fill_nullptr_at(0); // nof_items-- inside
    }

    void merge_children(ushort pos_left, ushort pos_right) {
        ASSERT(pos_left + 1 == pos_right);
        ASSERT(children[pos_left]->nof_items == MIN_ITEMS);
        ASSERT(children[pos_right]->nof_items == MIN_ITEMS);
        Node* left = children[pos_left];
        left->items[nof_items] = this->items[pos_left];
        this->items[pos_left] = nullptr;
        Node* right = children[pos_right];
        for(ushort r = 0; r < right->nof_items; r++) {
            ushort l = r + left->nof_items;
            if(right->children[r]) {
                left->children[l] = right->children[r];
                right->children[r] = nullptr; // TODO Remove
                left->children[l]->parent = left;
            }
            left->items[l] = right->items[r];
            right->items[r] = nullptr; // TODO Remove
        }
        left->nof_items += right->nof_items;
        left->children[left->nof_items] = right->children[right->nof_items];
        delete right;
        this->children[pos_right] = left;
        this->children[pos_left] = nullptr;
        this->fill_nullptr_at(pos_left); // nof_items-- inside
    }

    void remove(const Item* const item) {
        ushort pos = 0;
        while(pos < nof_items) {
            if(items[pos] == item) break;
            pos++;
        }
        ASSERT(pos < nof_items);
        if(this->leaf) {
            ushort last = nof_items - 1;
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
                    // Oba maj¹ minimum kluczy
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
                    // Oba maj¹ wystarczaj¹c¹ liczbê kluczy
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

public:

    Node() : leaf(true), parent(nullptr), nof_items(0) {
        items.fill(nullptr);
        children.fill(nullptr);
    }

    bool full() {
        return nof_items == items.size();
    }

    void insert(const Item* const item) {
        if(full()) {
            this->split();
            parent->insert(item);
        } else {
            if(leaf) { // Wêze³ jest liœciem
                ushort pos = 0;
                while(items[pos] && items[pos]->key <= item->key) pos++;
                for(ushort end_pos = nof_items; end_pos > pos; end_pos--)
                    items[end_pos] = items[end_pos - 1];
                items[pos] = item;
                nof_items++;
            } else { // Wêze³ nie jest liœciem
                ushort pos = 0;
                while(pos < nof_items && items[pos]->key <= item->key) pos++;
                ASSERT(children[pos]);
                children[pos]->insert(item);
            }
        }
    }

    void print_if_between(const double lower_bound, const double upper_bound) {
        if(this->leaf) {
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

    friend class BTree;
};

class BTree {
    Node* root;

public:

    BTree() : root(nullptr) {}

    void insert(const double key, const std::string value) {
        const Item* new_item = new Item(key, value);
        if(root == nullptr) { // Drzewo jest puste
            root = new Node();
        }
        root->insert(new_item);
        if(root->parent) root = root->parent;
    }

    const Item* remove(const double key) {
        Node* pos = root;
        const Item* item = nullptr;
        while(pos) {
            for(ushort i = 0; i < pos->nof_items; i++) {
                if(key > pos->items[i]->key) continue;
                if(key == pos->items[i]->key) {
                    item = pos->items[i];
                    break;
                } else {
                    Node* child = pos->children[i];
                    if(child->nof_items == MIN_ITEMS) {
                        if(i == 0) {
                            Node* brother = pos->children[1];
                            if(brother->nof_items == MIN_ITEMS) {
                                pos->merge_children(0, 1);
                            } else {
                                child->take_key_from_right(i);
                            }
                        } else {
                            Node* brother = pos->children[i - 1];
                            if(brother->nof_items == MIN_ITEMS) {
                                pos->merge_children(i - 1, i);
                            } else {
                                child->take_key_from_left(i);
                            }
                        }
                    }
                    pos = pos->children[i];
                    break;
                }
            }
            if(item) break;
            ushort i = pos->nof_items;
            if(pos->children[i]->nof_items == MIN_ITEMS) {
                if(i == 0) {
                    Node* brother = pos->children[1];
                    if(brother->nof_items == MIN_ITEMS) {
                        pos->merge_children(0, 1);
                    } else {
                        pos->children[i]->take_key_from_right(i);
                    }
                } else {
                    Node* brother = pos->children[i - 1];
                    if(brother->nof_items == MIN_ITEMS) {
                        pos->merge_children(i - 1, i);
                    } else {
                        pos->children[i]->take_key_from_left(i);
                    }
                }
            }
            pos = pos->children[i];
        }
        if(item) {
            pos->remove(item);
        }

        return item;
    }

    void print_between(const double lower_bound, const double upper_bound) const {
        root->print_if_between(lower_bound, upper_bound);
    }
};

class Ranking {

    BTree tree;

    void add_person(const std::string& name, const double& factor) {
        tree.insert(factor, name);
    }

    void modify(const double old_key, const double new_key) {
        const Item* item = tree.remove(old_key);
        tree.insert(new_key, item->value);
        delete item;
    }

    void print_between(const double lower_bound, const double upper_bound) {
        tree.print_between(lower_bound, upper_bound);
    }

public:

    Ranking(uint nof_people) {
        for(uint i = 0; i < nof_people; i++) {
            std::string s; // Pseudonim
            double x; // Wspó³czynnik
            std::cin >> s >> x;
            add_person(s, x);
        }
    }

    void execute_operations(ushort nof_operations) {
        for(ushort i = 0; i < nof_operations; i++) {
            char op;
            std::cin >> op;
            switch(op) {
            case 'a': { // Operacja 'a' - dodaj now¹ osobê
                std::string s;
                double x;
                std::cin >> s >> x;
                add_person(s, x);
                break;
            }
            case 'm': { // Operacja 'm' - zmieñ wartoœæ wspó³czynnika
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

    uint n; // Pocz¹tkowa liczba osób na liœcie
    std::cin >> n;

    Ranking ranking(n);

    ushort m; // Iloœæ operacji do wykonania
    std::cin >> m;

    ranking.execute_operations(m);

    return 0;
}