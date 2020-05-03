#include <iostream>

typedef unsigned short ushort;
typedef unsigned int uint;

class RBTree {
    enum Color { RED, BLACK };
    struct Node {
        Color color;
        Node* parent;
        Node* left;
        Node* right;
        Node(Node* initializer) :parent(initializer), left(initializer), right(initializer), color(BLACK) {}
        Node(Node* parent, Node* left, Node* right) : parent(parent), left(left), right(right), color(BLACK) {}
    };

    Node* nullnode;

    Node* root;

public:
    RBTree(ushort nof_people) : nullnode(new Node(nullptr)), root(nullnode) {}
};

int main() {

    ushort n; // Pocz¹tkowa liczba osób na liœcie

    std::cin >> n;

    RBTree tree(n);

    return 0;
}