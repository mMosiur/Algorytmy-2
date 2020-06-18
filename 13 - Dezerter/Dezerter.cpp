#include <iostream>
#include <vector>
#include <array>

typedef unsigned int uint;

struct Character {
	char ascii;
	uint hash;
	std::pair<uint, uint> pair;
	uint initial_position;

	Character(uint initial_position, char character)
		: initial_position(initial_position),
		ascii(character),
		hash(0) {}
};

class Text {
public:
	enum class Sort {
		Position,
		Ascii,
		Pair,
		Hash
	};
private:
	std::vector<Character*> text;
	Sort last_sort;
	uint last_max_hash;
	void sort_by_ascii() {
		std::array<std::vector<Character*>, 256> buckets;
		for(auto& character : text)
			buckets[character->ascii].push_back(character);
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}
	void sort_by_position() {
		std::vector<Character*> new_text(text.size());
		for(auto& ascii : text) {
			new_text[ascii->initial_position] = ascii;
		}
		text = new_text;
	}
	void sort_by_pairs() {
		std::vector<std::vector<Character*>> buckets(last_max_hash+1);
		for(auto& character : text) {
			buckets[character->pair.second].push_back(character);
		}
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
			bucket.clear();
		}
		for(auto& character : text) {
			buckets[character->pair.first].push_back(character);
		}
		pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}
	void sort_by_hash() {
		std::vector<std::vector<Character*>> buckets(last_max_hash + 1);
		for(auto& character : text) {
			buckets[character->hash].push_back(character);
		}
		uint pos = 0;
		for(auto& bucket : buckets) {
			for(auto& character : bucket) {
				text[pos++] = character;
			}
		}
	}
public:
	Text(std::string str) : text(str.length()), last_sort(Sort::Position), last_max_hash(0) {
		for(uint i = 0; i < str.length(); i++) {
			text[i] = new Character(i, str[i]);
		}
	}
	std::vector<Character*>::const_iterator begin() const {
		return text.begin();
	}
	std::vector<Character*>::const_iterator end() const {
		return text.end();
	}
	bool sort_by(Sort sort_type) {
		if(sort_type == last_sort) return true;
		switch(sort_type) {
		case Sort::Position:
			sort_by_position();
			break;
		case Sort::Ascii:
			sort_by_ascii();
			break;
		case Sort::Pair:
			sort_by_pairs();
			break;
		case Sort::Hash:
			sort_by_hash();
			break;
		default:
			return false;
		}
		last_sort = sort_type;
		return true;
	}
	void construct_new_pairs(uint distance) {
		sort_by(Text::Sort::Position);
		for(uint i = 0; i < text.size(); i++) {
			uint other_hash = (i + distance >= text.size() ? 0 : text[i + distance]->hash);
			text[i]->pair = std::make_pair(text[i]->hash, other_hash);
		}
	}
	void generate_hashes() {
		sort_by(Text::Sort::Pair);
		std::pair<uint, uint> prev_pair = { 0, 0 };
		last_max_hash = 0;
		for(auto& character : text) {
			if(character->pair != prev_pair) {
				character->hash = ++last_max_hash;
				prev_pair = character->pair;
			} else character->hash = last_max_hash;
		}
	}
	uint nof_unique_hashes(uint substr_len) {
		uint position = 0;
		last_max_hash = 0;
		sort_by(Text::Sort::Ascii);
		for(auto& character : text) {
			if(character->ascii != last_max_hash) {
				character->hash = ++position;
				last_max_hash = character->ascii;
			} else character->hash = position;
		}
		sort_by(Text::Sort::Position);
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
		sort_by(Text::Sort::Hash);
		uint unique_hashes = 0;
		uint last_hash = 0;
		for(auto& character : text) {
			if(character->initial_position > text.size() - hash_length) continue;
			if(character->hash != last_hash) {
				unique_hashes++;
				last_hash = character->hash;
			}
		}
		return unique_hashes;
	}
};

class SubstringCounter {
	Text text;
public:
	SubstringCounter(std::string str) : text(str) {}
	uint nof_unique_substrings(uint substring_length) {
		return text.nof_unique_hashes(substring_length);
	}
};

int main() {
	uint n;
	uint m;
	std::cin >> n >> m;

	std::string text;
	for(uint i = 0; i < n; i++) {
		std::string word;
		std::cin >> word;
		text += word;
	}
	SubstringCounter counter(text);

	std::cout << counter.nof_unique_substrings(m) << std::endl;

	return 0;
}