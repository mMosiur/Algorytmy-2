#include <iostream>
#include <vector>
#include <array>

typedef unsigned int uint;

// Struktora reprezentująca znak w tekście wraz z dodaktowymi parametrami
struct Character {
	char ascii; // Znak ascii
	uint hash; // Hash dla podciągu o początku w tym znaku
	std::pair<uint, uint> pair; // Para haszy dla tego i kolejnego do podłączenia podciągu
	uint position; // Początkowa pozycja w tekście

	// Konstruktor przyjmujący i inicjalizujący wymagane zmienne
	Character(uint position, char character) : position(position), ascii(character), hash(0) {}
};

// Klasa reprezentująca tekst do przetworzenia
class Text {

	std::vector<Character> text; // Wektor znaków reprezentujący otrzymany tekst
	uint last_max_hash; // Najwyższy hash, jaki pojawił się w poprzednim hashowaniu

	// Funkcja sortująca liniowo znaki względem ich wartości ascii (bucket sort)
	void sort_by_ascii() {
		std::array<std::vector<Character>, 256> buckets;
		for(auto& character : text)
			buckets[character.ascii].push_back(character);
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}

	// Funkcja sortująca liniowo znaki pod względem ich pozycji w tekście (ustawia tekst z powrotem do jego pierwotnej formy)
	void sort_by_position() {
		std::vector<Character> new_text(text.size(), Character(0, 0));
		for(auto& ascii : text) {
			new_text[ascii.position] = ascii;
		}
		text = new_text;
	}

	// Funkcja sortująca liniowo znaki względem ich pary wewnątrz (radix sort)
	void sort_by_pairs() {
		std::vector<std::vector<Character>> buckets(last_max_hash+1);
		for(auto& character : text) {
			buckets[character.pair.second].push_back(character);
		}
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
			bucket.clear();
		}
		for(auto& character : text) {
			buckets[character.pair.first].push_back(character);
		}
		pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}

	// Funkcja sortująca liniowo znaki na bazie ich aktualnego hashu (bucket sort)
	void sort_by_hash() {
		std::vector<std::vector<Character>> buckets(last_max_hash + 1);
		for(auto& character : text) {
			buckets[character.hash].push_back(character);
		}
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}

public:

	// Konstruktor przyjmujący string do przetworzenia i wczytujący go do formy struktur znaków
	Text(std::string str) : last_max_hash(0) {
		for(uint i = 0; i < str.length(); i++) {
			text.push_back(Character(i, str[i]));
		}
	}
	
	// Funkcja sortująca przez pozycję i budująca dla znaków ich nowe pary dla podanego dystansu między znakami
	void construct_new_pairs(uint distance) {
		sort_by_position();
		for(uint i = 0; i < text.size(); i++) {
			uint other_hash = (i + distance >= text.size() ? 0 : text[i + distance].hash);
			text[i].pair = std::make_pair(text[i].hash, other_hash);
		}
	}

	// Funkcja sortująca przez pary i generująca dla znaków nowe hashe
	void generate_hashes() {
		sort_by_pairs();
		std::pair<uint, uint> prev_pair = { 0, 0 };
		last_max_hash = 0;
		for(auto& character : text) {
			if(character.pair != prev_pair) {
				character.hash = ++last_max_hash;
				prev_pair = character.pair;
			} else character.hash = last_max_hash;
		}
	}

	// Funkcja zwracająca liczbę unikalnych podciągów z teksu o długości podanej w parametrze
	uint nof_unique_hashes(uint substr_len) {
		uint position = 0;
		last_max_hash = 0;
		sort_by_ascii();
		for(auto& character : text) {
			if(character.ascii != last_max_hash) {
				character.hash = ++position;
				last_max_hash = character.ascii;
			} else character.hash = position;
		}
		sort_by_position();
		uint hash_length = 1;

		while(2 * hash_length <= substr_len) {
			construct_new_pairs(hash_length);
			generate_hashes();
			hash_length *= 2;
		};
		if(hash_length < substr_len) {
			uint diff = substr_len - hash_length;
			construct_new_pairs(diff);
			generate_hashes();
			hash_length += diff;
		}
		sort_by_hash();
		uint unique_hashes = 0;
		uint last_hash = 0;
		for(auto& character : text) {
			if(character.position > text.size() - hash_length) continue;
			if(character.hash != last_hash) {
				unique_hashes++;
				last_hash = character.hash;
			}
		}
		return unique_hashes;
	}
};

// Klasa licząca podciągi w tekście
class SubstringCounter {
	Text text; // Tekst w formie specjalnej klasy
public:

	// Konstruktor przyjmujący string i inicjalizujący nim wewnętrzą strukturę tekstu
	SubstringCounter(std::string str) : text(str) {}

	// Funkcja zwracająca liczbę unikalnych podciągów  w tekście o długości podanej w parametrze
	uint nof_unique_substrings(uint substring_length) {
		return text.nof_unique_hashes(substring_length);
	}
};

int main() {
	uint n; // Liczba słów
	uint m; // Długośc podciągów
	std::cin >> n >> m;

	std::string text;
	for(uint i = 0; i < n; i++) {
		std::string word;
		std::cin >> word;
		text += word;
	}

	Text counter(text);

	std::cout << counter.nof_unique_hashes(m) << std::endl;

	return 0;
}