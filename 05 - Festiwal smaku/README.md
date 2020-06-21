# Festiwal smaku

Jak wiadomo w Lublinie często odbywają się spotkania kulinarne, degustacyjne i różne festiwale smaku. Jedna z koleżanek Partycji (z grupy społecznej, której nie wykluczyła:) ) zajmuje się organizacją festiwalu degustacji tradycyjnych polskich potraw. Chciałaby, aby to wydarzenie było jednym z najlepszych. Zależy jej na tym, aby każdy zjadł to, na co ma ochotę.

W związku z tym Jagoda, bo tak ma na imię koleżanka naszej bohaterki, poprosiła wszystkich zaproszonych na festiwal o wypełnienie ankiety. Ankieta polega na tym, że każdy uczestnik wydarzenia musi wybrać potrawy, które chciałby skosztować. Oczywiście taka osoba może zaznaczyć dowolną ilość potraw z listy, które chętnie by zjadła. Uczestnik może zaznaczyć wszystkie potrawy, ale równie dobrze może nie zaznaczyć żadnej - wtedy wiemy, że nie będzie on zadowolony. Ponieważ są to bardzo ekskluzywne potrawy i kunsztowne, ekskluzywne wydarzenie na każdego uczestnika przypada tylko jedna degustacja. Niestety dobranie odpowiednich posiłków dla każdego z gości, jest ogromnym wyzwaniem organizacyjnym. Wynika to przede wszystkim z tego, że każdej potrawy zostanie przygotowana taka sama, ograniczona ilość. Dodatkowo Jagoda chce aby, jak najwięcej osób wyszło z wydarzenia zadowolonych. To zadowolenie gwarantuje jedynie to, że przybysze zjedzą potrawę, która była na ich liście życzeń.


## WEJŚCIE
W pierwszej linii wejścia znajdują się liczby naturalne **n** **m** **l**, **n** - to liczba uczestników wydarzenia, **m** - to ilość dostępnych potraw, zaś **l** - to ilość zestawów degustacyjnych każdej z potraw. Następnie program powinien wczytać wyniki ankiety, które są podane w macierzy o wymiarach **n x m**. Gdy uczestnik chce spróbować potrawy wprowadził ‘**x**’, a w przeciwnym wypadku ‘**o**’.

**0 <= n, m, l <= 2000000000**


## WYJŚCIE
Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest największą możliwą liczbą osób zadowolonych z uczestnictwa w wydarzeniu.


## PRZYKŁADOWE DANE WEJŚCIOWE
```
6 3 2
o o x
x x x
o o x
x o o
x o x
x o o
```

## PRZYKŁADOWE DANE WYJŚCIOWE
```
5
```

## UWAGI
Rozwiązane zadania powinno być implementacją metody wyszukiwania maksymalnego skojarzenia w grafie dwudzielnym