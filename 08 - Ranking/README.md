# Ranking

Partycja stwierdziła, że prowadzenie listy zagrażających jej osób w tradycyjny sposób nie wyczerpuje problemu. Ponieważ nie ma systemu oceniania, jak bardzo dana osoba jest niebezpieczna w pewnej skali, nie da się jednoznacznie stwierdzić kto jest naprawdę istotny. Partycja postanowiła stworzyć ranking. Według znanych tylko jej wzorów wyznacza każdej osobie wartość liczbową określaną jako „współczynnik zagrożenia”. Im współczynnik jest wyższy tym dana osoba jest bardziej niebezpieczna. Oczywiście jego wartość może ulec zmianie z biegiem czasu. Patrycja chciałaby mieć program który pomógł by jej w wyszukaniu wszystkich osób w podanym przedziale niebezpieczeństwa. Co ważne nasza bohaterka dba o to aby nie pojawiły się dwie osoby o takim samym współczynniku. Pomóż Partycji stworzyć taki ranking.

## Wejście:

W pierwszej linii wejścia program otrzymuje liczbę **n** oznaczającą początkową liczbę osób na liście. Następnie w n liniach program otrzymuje pary składające się z pseudonimu **s** oraz współczynnika **x** przedstawionego w formie liczby rzeczywistej. W kolejnym kroku program otrzymuje liczbę **m** będącą ilością operacji do wykonania. Na koniec w m liniach program otrzymuje opis operacji. Pierwszy znak zawsze oznacza akcję do wykonania a po nim pojawiają się stosowne dane zgodnie z poniższym opisem:

**a** **s** **x** – dodanie nowej osoby o pseudonimie s ze współczynnikiem x
**m** **x1** **x2** – zmiana wartości współczynnika z x1 na x2
**s** **x1** **x2** – wypisanie wszystkich osób których wartość współczynnika zawiera się między x1 a x2 (przedział domknięty, poczynając od osoby najbardziej niebezpiecznej)

## Wyjście:

Na wyjściu program powinien wypisać pseudonimy osób dla każdego zapytania **s**.

**1 < n ≤ 75000**

**1 < m ≤ 5000**

## Przykładowe wejście:
```
5
Okruszek 0.5
Tester 0.7
Interfejs 0.2
Agent 0.4
Scyzoryk 0.3
3
a Kontakt 0.6
m 0.7 0.8
s 0.3 0.7
```

## Przykładowe wyjście:
```
Kontakt
Okruszek
Agent
Scyzoryk
```

## Uwaga:

**Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych B-drzew, gdzie parametr T charakterystyczny dla B-drzewa zawiera się w przedziale \[10,20\].**