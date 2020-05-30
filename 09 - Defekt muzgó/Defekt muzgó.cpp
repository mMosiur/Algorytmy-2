#include <iostream>
#include <string>
#include <list>

typedef unsigned int uint;

struct Album;

// Struktura reprezentująca zespół
struct Band {
	std::string name; // Nazwa zespołu
	std::list<Album*> albums; // Lista albumów powiązanych z tym zespołem

	// Kontruktor przyjmujący nazwę zespołu i inicjalizujący ją
	Band(std::string& name) : name(name) {}

	// Operatory porównania z nazwą zespołu
	bool operator <(const std::string& other) const { return name < other; }
	bool operator >(const std::string& other) const { return name > other; }
};

// Struktura reprezentująca album
struct Album {
	std::string title; // Tytuł albumu
	std::list<Band*> bands; // Lista zespołów powiązanych z tym albumem

	// Kontruktor przyjmujący tytuł albumu i inicjalizujący go
	Album(std::string& title) : title(title) {}

	// Operatory porównania z tytułem albumu
	bool operator <(const std::string& other) const { return title < other; }
	bool operator >(const std::string& other) const { return title > other; }
};

// Klasa drzewa splay o kluczach T
template <class T>
class SplayTree {

	// Struktura Węzła w drzewie
	struct Node {
		T key; // Klucz węzła
		Node* parent; // Rodzic węzła
		Node* left; // Lewe dziecko węzła
		Node* right; // Prawe dziecko węzła

		// Kontruktor przyjmujący klucz i inicjalizujący zmienne
		Node(T&& key) : key(key), parent(nullptr), left(nullptr), right(nullptr) {}

		// Funkcja zwracająca, czy węzeł jest lewym dzieckiem swojego rodzica
		bool is_left() const {
			return parent && this == parent->left;
		}

		// Funkcja zwracająca, czy węzeł jest prawym dzieckiem swojego rodzica
		bool is_right() const {
			return parent && this == parent->right;
		}
	};

	Node* root; // Wskaźnik na korzeń drzewa

	// Funkcja wykonująca rotację w lewo danego węzła
	void rotate_left(Node* const node) {
		Node* const pivot = node->right;
		node->right = pivot->left;
		if(node->right != nullptr) node->right->parent = node;
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

	// Funkcja wykonująca rotację w prawo danego węzła
	void rotate_right(Node* const node) {
		Node* const pivot = node->left;
		node->left = pivot->right;
		if(node->left != nullptr) node->left->parent = node;
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

	// Funkcja splay przenosząca podany węzeł do pozycji korzenia w drzewie
	void splay(Node* const node) {
		while(node != root) {
			Node* parent = node->parent;
			Node* grandparent = parent->parent;
			if(parent->is_left()) {
				if(node->is_left()) {
					// ZIG-ZIG-LL
					rotate_right(grandparent);
					rotate_right(parent);
				} else { // node->is_right()
					// ZIG-ZAG-LR
					rotate_left(parent);
					rotate_right(grandparent);
				}
			} else if(parent->is_right()) {
				if(node->is_right()) {
					// ZIG-ZIG-RR
					rotate_left(grandparent);
					rotate_left(parent);
				} else { // node->is_left()
					// ZIG-ZAG-RL
					rotate_right(parent);
					rotate_left(grandparent);
				}
			} else { // grandparent == nullptr
				if(node->is_left()) {
					// ZIG-L
					rotate_right(parent);
				} else { // node->is_right()
					// ZIG-R
					rotate_left(parent);
				}
			}
		}
	}

public:

	// Kontruktor inicjalizujący korzeń
	SplayTree() : root(nullptr) {}

	// Funkcja wstawiająca nowy element o podanym kluczu do drzewa i zwracająca go
	// W przypadku, gdy podany klucz istnieje, zwraca znaleziony element o tym kluczu
	T* insert(std::string key) {
		if(root == nullptr) {
			root = new Node(T(key));
			return &root->key;
		}
		T* item = find(key);
		if(item == nullptr) {
			Node* new_node = new Node(T(key));
			if(root->key < key) {
				if(root->right) {
					new_node->right = root->right;
					root->right = nullptr;
					new_node->right->parent = new_node;
				}
				new_node->left = root;
				root->parent = new_node;
				root = new_node;
			} else { // root->key > key
				if(root->left) {
					new_node->left = root->left;
					root->left = nullptr;
					new_node->left->parent = new_node;
				}
				new_node->right = root;
				root->parent = new_node;
				root = new_node;
			}
			root = new_node;
			item = &new_node->key;
		}
		return item;
	}

	// Funkcja wyszukująca podany klucz w drzewie i zwracająca wskaźnik na element
	// W przypadku, gdy danego klucza nie ma, zwraca nullptr
	T* find(std::string key) {
		Node* prev = nullptr;
		Node* pos = root;
		while(pos != nullptr) {
			if(pos->key < key) {
				prev = pos;
				pos = pos->right;
			} else if(pos->key > key) {
				prev = pos;
				pos = pos->left;
			} else { // pos->key == key
				splay(pos);
				return &pos->key;
			}
		}
		splay(prev);
		return nullptr;
	}

};

// Klasa wyszukiwarki zespołów i albumów
class BandAlbumSearcher {
	SplayTree<Band> bands; // Drzewo splay z zespołami
	SplayTree<Album> albums; // Drzewo splay z albumami

public:

	// Funkcja dodająca powiązanie między zespołem a albumem
	void add(std::string band_name, std::string album_title) {
		Band* band = bands.insert(band_name);
		Album* album = albums.insert(album_title);
		band->albums.push_back(album);
		album->bands.push_back(band);
	}

	// Funkcja wypisująca albumy powiązane z danym zespołem
	void print_albums_of_band(std::string band_name) {
		Band* band = bands.find(band_name);
		if(band == nullptr) return;
		for(auto& album : band->albums) {
			std::cout << album->title << std::endl;
		}
	}

	// Funkcja wypisująca zespoły powiązane z danym albumem
	void print_bands_from_album(std::string album_name) {
		Album* album = albums.find(album_name);
		if(album == nullptr) return;
		for(auto& band : album->bands) {
			std::cout << band->name << std::endl;
		}
	}
};

int main() {
	std::ios::sync_with_stdio(false);

	BandAlbumSearcher searcher; // wyszukiwarka

	uint nof_operations; // Liczba operacji do wykonania
	std::cin >> nof_operations;

	for(uint i = 0; i < nof_operations; i++) {
		std::string operation; // Operacja do wykonania
		std::cin >> operation; 
		if(operation == "d") {
			std::string band, album;
			std::cin.ignore();
			std::getline(std::cin, band);
			std::getline(std::cin, album);
			searcher.add(band, album);
		} else if(operation == "w") {
			std::string band;
			std::cin.ignore();
			std::getline(std::cin, band);
			searcher.print_albums_of_band(band);
		} else if(operation == "z") {
			std::string album;
			std::cin.ignore();
			std::getline(std::cin, album);
			searcher.print_bands_from_album(album);
		}
	}

	return 0;
}