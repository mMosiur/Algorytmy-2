#include <iostream>
#include <list>
#include <map>
#include <string>

typedef unsigned short ushort;
typedef unsigned int uint;

ushort min(ushort x, ushort y) { return (x < y) ? x : y; }

ushort match(const std::string& str1, const std::string& str2) {
	ushort nof_matched_letters = 0;
	ushort size = min((ushort)str1.length(), (ushort)str2.length());
	for(ushort i = 0; i < size; i++) {
		if(str1[i] != str2[i]) break;
		else nof_matched_letters++;
	}
	return nof_matched_letters;
}

struct Album;

// Struktura reprezentująca zespół
struct Band {
	std::string name; // Nazwa zespołu
	std::list<Album*> albums; // Lista albumów powiązanych z tym zespołem

	// Kontruktor przyjmujący nazwę zespołu i inicjalizujący ją
	Band(const std::string& name) : name(name) {}
};
bool operator == (Band* const& band, const std::string& name) { return band->name == name; }

// Struktura reprezentująca album
struct Album {
	std::string title; // Tytuł albumu
	std::list<Band*> bands; // Lista zespołów powiązanych z tym albumem

	// Kontruktor przyjmujący tytuł albumu i inicjalizujący go
	Album(const std::string& title) : title(title) {}
};
bool operator == (Album* const& album, const std::string& title) { return album->title == title; }

template <class T>
class CompressedTrie {
	struct Node {
		std::map<std::string, Node*> children;
		T* key;
		Node(T* key = nullptr) : key(key) {}
		bool is_leaf() const { return key != nullptr; };
		T* insert(const std::string& name, ushort pos_in_name) {
			if(key && key == name) return key;
			for(auto it = children.begin(); it != children.end(); ++it) {
				ushort matched = match(it->first, name.substr(pos_in_name));
				if(matched == 0) continue;
				if(matched == it->first.length()) {
					if((size_t)pos_in_name + matched == name.length()) {
						// Jest to końcówka
						if(it->second->key == nullptr) it->second->key = new T(name);
						return it->second->key;
					}
					return it->second->insert(name, pos_in_name + matched);
				} else if(matched == name.length() - pos_in_name) {
					const std::string old_key = it->first;
					Node* const old_node = it->second;
					children.erase(it);
					T* const new_key = new T(name);
					Node* const new_node = new Node(new_key);
					children.emplace(name.substr(pos_in_name), new_node);
					new_node->children.emplace(old_key.substr(matched), old_node);
					return new_key;
				} else {
					const std::string old_key = it->first;
					Node* const old_node = it->second;
					children.erase(it);
					Node* const new_middle_node = new Node();
					children.emplace(old_key.substr(0, matched), new_middle_node);
					new_middle_node->children.emplace(old_key.substr(matched), old_node);
					T* new_key = new T(name);

					new_middle_node->children.emplace(name.substr((size_t)pos_in_name + (size_t)matched), new Node(new_key));
					return new_key;
				}
			}
			T* new_key = new T(name);
			children.emplace(name.substr(pos_in_name), new Node(new_key));
			return new_key;
		}
		T* find(const std::string& name, ushort pos) {
			if(key && key == name) return key;
			if(pos == name.length()) return nullptr;
			for(auto&& child : children) {
				ushort matched = match(child.first, name.substr(pos));
				if(matched == 0) continue;
				return child.second->find(name, pos + matched);
			}
			return nullptr;
		}
		ushort _subtree_size() const {
			ushort result = (this->key != nullptr);
			for(auto& child : children) {
				result += child.second->_subtree_size();
			}
			return result;
		}
		ushort _error() const {
			for(const auto& child : children) {
				if(child.first.empty())
					return true;
				if(child.second->_error()) return true;
			}
			return false;
		}
	};

	Node* const root;

public:
	CompressedTrie() : root(new Node()) {}
	T* insert(std::string& name) {
		return root->insert(name, 0);
	}
	T* find(std::string& name) const {
		return root->find(name, 0);
	}
};

// Klasa wyszukiwarki zespołów i albumów
class BandAlbumSearcher {
	CompressedTrie<Band> bands; // Skompresowane drzewo trie z zespołami
	CompressedTrie<Album> albums; // Skompresowane drzewo trie z albumami

public:

	// Funkcja dodająca powiązanie między zespołem a albumem
	void add(std::string band_name, std::string album_title) {
		Band* const band = bands.insert(band_name);
		Album* const album = albums.insert(album_title);
		band->albums.push_back(album);
		album->bands.push_back(band);
	}

	// Funkcja wypisująca albumy powiązane z danym zespołem
	void print_albums_of_band(std::string band_name) const {
		Band* const band = bands.find(band_name);
		if(band == nullptr) return;
		for(auto& album : band->albums) {
			std::cout << album->title << std::endl;
		}
	}

	// Funkcja wypisująca zespoły powiązane z danym albumem
	void print_bands_from_album(std::string album_name) const {
		Album* const album = albums.find(album_name);
		if(album == nullptr) return;
		for(auto& band : album->bands) {
			std::cout << band->name << std::endl;
		}
	}
};

int main() {
	std::ios::sync_with_stdio(false);

	BandAlbumSearcher searcher; // Wyszukiwarka

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