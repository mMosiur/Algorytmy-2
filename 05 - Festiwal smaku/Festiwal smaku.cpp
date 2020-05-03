#include <iostream>
#include <vector>

// Struktura reprezentuj¹ca uczestnika festiwalu
struct Participant {
    int number; // Numer uczestnika
    std::vector<int> dish_numbers; // Wektor numerów potraw, które uczestnik zadeklarowa³ chêæ spróbowania
    int assigned_dish_number; // Numer dania przypisanego uczestnikowi (-1 dla braku przypisania)

    // Konstruktor inicjalizuj¹cy zmienne
    Participant() : number(-1), assigned_dish_number(-1) {}
};

// Struktura reprezentuj¹ca potrawê na festiwalu
struct Dish {
    int number; // Numer potrawy
    std::vector<int> guest_numbers; // Wektor numerów uczestników, którzy zadeklarowi chêæ spróbowania tej potrawy
    int meals_left; // Liczba pozosta³ych posi³ków dla danej potrawy

    // Konstruktor przyjmuj¹cy liczbê posi³ków danej potrawy i inicjalizuj¹cy zmienne
    Dish(int nof_meals) : number(-1), meals_left(nof_meals) {}
};

// Klasa reprezentuj¹ca festiwal
class Festival {
    std::vector<Participant> participants; // Wektor uczestników festiwalu
    std::vector<Dish> dishes; // Wektor potraw na festiwalu

    // Funkcja zwracaj¹ca, czy znaleziono alternatywn¹ œcie¿kê dla danej potrawy i zapisuj¹ca j¹ w zmiennej z argumentu
    bool find_alternative_path_from(Dish& dish, std::pair<int, int>& alternative_path) {
        for(int guest_number : dish.guest_numbers) {
            Participant& participant = participants[guest_number];
            if(participant.assigned_dish_number != dish.number) continue;
            for(int dish_number : participant.dish_numbers) {
                if(dish_number == participant.assigned_dish_number) continue;
                Dish& alternative_dish = dishes[dish_number];
                if(alternative_dish.meals_left == 0) continue;
                alternative_path = { guest_number, dish_number };
                return true; // Znaleziono œcie¿kê alternatywn¹
            }
        }
        return false; // Nie znaleziono œcie¿ki alternatywnej
    }

public:

    // Konstruktor przyjmuj¹cy iloœæ uczestników, potraw i posi³ków, inicjalizuj¹cy zmienne oraz wczytuj¹cy dane z anket
    Festival(int nof_guests, int nof_dishes, int nof_meals) : participants(nof_guests), dishes(nof_dishes, Dish(nof_meals)) {
        for(int d = 0; d < nof_dishes; d++) dishes[d].number = d;
        for(int g = 0; g < nof_guests; g++) {
            participants[g].number = g;
            for(int d = 0; d < nof_dishes; d++) {
                char c;
                std::cin >> c;
                if(c == 'x') {
                    participants[g].dish_numbers.push_back(d);
                    dishes[d].guest_numbers.push_back(g);
                }
            }
        }
    }

    // Funkcja zwracaj¹ca maksymaln¹ liczbê zadowolonych uczestników festiwalu
    int max_content_guests() {
        for(auto& guest : participants) {
            for(int dish_number : guest.dish_numbers) {
                Dish& dish = dishes[dish_number];
                if(dish.meals_left == 0) continue;
                guest.assigned_dish_number = dish_number;
                dish.meals_left--;
                break;
            }
            if(guest.assigned_dish_number == -1) { // Jeœli nie uda³o siê po³¹czyæ
                for(int dish_number : guest.dish_numbers) {
                    Dish& dish = dishes[dish_number];
                    std::pair<int, int> alternative_path;
                    if(find_alternative_path_from(dish, alternative_path)) {
                        int alternative_guest_number = alternative_path.first;
                        int alternative_dish_number = alternative_path.second;
                        participants[alternative_guest_number].assigned_dish_number = alternative_dish_number;
                        dishes[alternative_dish_number].meals_left--;
                        guest.assigned_dish_number = dish.number;
                        break;
                    }
                }
            }
        }
        // Zliczanie po³¹czonych goœci
        int nof_content_guests = 0;
        for(auto& guest : participants) {
            if(guest.assigned_dish_number != -1) nof_content_guests++;
        }
        return nof_content_guests;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, l;
    std::cin >> n >> m >> l;

    Festival festival(n, m, l);

    std::cout << festival.max_content_guests() << std::endl;

    return 0;
}