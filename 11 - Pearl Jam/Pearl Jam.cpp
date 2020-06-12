#include <iostream>
#include <string>
#include <list>
#include <vector>

typedef unsigned int uint;

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

template<class T>
// Klasa tablicy haszującej
class HashTable {
	std::vector<std::list<T*>> table; // tablica

	// Funkcja haszująca string używająca algorytmu wielomianowego o wykładniku p = 29
	uint hash_string(const std::string key) const {
		constexpr uint p = 29;
		const uint m = (uint)table.size();
		uint result = 0;
		uint power = 1;
		for(const char c : key) {
			result = (result + c * power) % m;
			power = (power * p) % m;
		}
		return result;
	}

public:

	static uint size; // Statyczne pole wielkości tablicy haszującej

	// Konstruktor tablicy ustawiający jej wielkość na wcześniej ustawione statyczne pole
	HashTable() : table(size) {}

	// Funkcja wstawiająca klucz o podanej nazwie jeżeli jeszcze nie istnieje i zwracająca go
	T* const insert(const std::string name) {
		uint hash = hash_string(name);
		for(auto& element : table[hash]) {
			if(element == name) return element;
		}
		T* const new_element = new T(name);
		table[hash].push_back(new_element);
		return new_element;
	}

	// Funkcja zwracająca klucz o podanej nazwie
	T* const find(const std::string name) const {
		uint hash = hash_string(name);
		for(auto& element : table[hash]) {
			if(element == name) return element;
		}
		return nullptr;
	}
};
// Inicjalizacja statycznej zmiennej wielkości tablicy haszującej
template<class T> uint HashTable<T>::size = 100;

// Klasa wyszukiwarki zespołów i albumów
class BandAlbumSearcher {
	HashTable<Band> bands; // Tablica haszująca z zespołami
	HashTable<Album> albums; // Tablica haszująca z albumami

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

	uint nof_operations; // Liczba operacji do wykonania
	std::cin >> nof_operations;
	// Ustawienie wielkości tablic haszujących na ilość operacji
	HashTable<Album>::size = nof_operations;
	HashTable<Band>::size = nof_operations;

	BandAlbumSearcher searcher; // wyszukiwarka

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