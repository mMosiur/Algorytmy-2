#include <iostream>
#include <vector>

typedef unsigned int uint;
const uint NONE = UINT32_MAX;

// Struktura reprezentująca uczestnika festiwalu
struct Participant {
    uint number; // Numer uczestnika
    std::vector<uint> dish_numbers; // Wektor numerów potraw, które uczestnik zadeklarował chęć spróbowania
    uint assigned_dish_number; // Numer dania przypisanego uczestnikowi (NONE dla braku przypisania)

    // Konstruktor inicjalizujący zmienne
    Participant() : number(NONE), assigned_dish_number(NONE) {}
};

// Struktura reprezentująca potrawę na festiwalu
struct Dish {
    uint number; // Numer potrawy
    std::vector<uint> guest_numbers; // Wektor numerów uczestników, którzy zadeklarowi chęć spróbowania tej potrawy
    uint meals_left; // Liczba pozostałych posiłków dla danej potrawy

    // Konstruktor przyjmujący liczbę posiłków danej potrawy i inicjalizujący zmienne
    Dish(uint nof_meals) : number(NONE), meals_left(nof_meals) {}
};

// Klasa reprezentująca festiwal
class Festival {
    std::vector<Participant> participants; // Wektor uczestników festiwalu
    std::vector<Dish> dishes; // Wektor potraw na festiwalu

    // Funkcja zwracająca, czy znaleziono alternatywną ścieżkę dla danej potrawy i zapisująca ją w zmiennej z argumentu
    bool find_alternative_path_from(Dish& dish, std::pair<uint, uint>& alternative_path) {
        for(uint guest_number : dish.guest_numbers) {
            Participant& participant = participants[guest_number];
            if(participant.assigned_dish_number != dish.number) continue;
            for(uint dish_number : participant.dish_numbers) {
                if(dish_number == participant.assigned_dish_number) continue;
                Dish& alternative_dish = dishes[dish_number];
                if(alternative_dish.meals_left == 0) continue;
                alternative_path = { guest_number, dish_number };
                return true; // Znaleziono ścieżkę alternatywną
            }
        }
        return false; // Nie znaleziono ścieżki alternatywnej
    }

public:

    // Konstruktor przyjmujący ilość uczestników, potraw i posiłków, inicjalizujący zmienne oraz wczytujący dane z anket
    Festival(uint nof_guests, uint nof_dishes, uint nof_meals) : participants(nof_guests), dishes(nof_dishes, Dish(nof_meals)) {
        for(uint d = 0; d < nof_dishes; d++) dishes[d].number = d;
        for(uint g = 0; g < nof_guests; g++) {
            participants[g].number = g;
            for(uint d = 0; d < nof_dishes; d++) {
                char c;
                std::cin >> c;
                if(c == 'x') {
                    participants[g].dish_numbers.push_back(d);
                    dishes[d].guest_numbers.push_back(g);
                }
            }
        }
    }

    // Funkcja zwracająca maksymalną liczbę zadowolonych uczestników festiwalu
    uint max_content_guests() {
        for(auto& guest : participants) {
            for(uint dish_number : guest.dish_numbers) {
                Dish& dish = dishes[dish_number];
                if(dish.meals_left == 0) continue;
                guest.assigned_dish_number = dish_number;
                dish.meals_left--;
                break;
            }
            if(guest.assigned_dish_number == NONE) { // Jeśli nie udało się połączyć
                for(uint dish_number : guest.dish_numbers) {
                    Dish& dish = dishes[dish_number];
                    std::pair<uint, uint> alternative_path;
                    if(find_alternative_path_from(dish, alternative_path)) {
                        uint alternative_guest_number = alternative_path.first;
                        uint alternative_dish_number = alternative_path.second;
                        participants[alternative_guest_number].assigned_dish_number = alternative_dish_number;
                        dishes[alternative_dish_number].meals_left--;
                        guest.assigned_dish_number = dish.number;
                        break;
                    }
                }
            }
        }
        // Zliczanie połączonych gości
        uint nof_content_guests = 0;
        for(auto& guest : participants) {
            if(guest.assigned_dish_number != NONE) nof_content_guests++;
        }
        return nof_content_guests;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    uint n, m, l;
    std::cin >> n >> m >> l;

    Festival festival(n, m, l);

    std::cout << festival.max_content_guests() << std::endl;

    return 0;
}