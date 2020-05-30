#include <iostream>
#include <string>

typedef unsigned int uint;


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