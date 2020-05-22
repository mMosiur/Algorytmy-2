# Tajna lista

Partycja spędza ostatnio bardzo dużo czasu na analizowaniu listy potencjalnie zagrażających jej osób. Są wśród nich politycy, ukryci agenci specjalni a nawet pani z pobliskiego warzywniaka. Jak wszyscy wiemy, nasza bohaterka lubi porządek. Właśnie dlatego jej lista jest uszeregowana od osób najniebezpieczniejszych do tych mniej niebezpiecznych. Co ważne, miejsca na liście dynamicznie się zmieniają, np. jeżeli pani Krysia z warzywniaka podejrzanie długo wydaje resztę, to po chwili Partycja musi przepisywać listę przenosząc ją o kilka miejsc w górę. Oczywiście czasami wykonuje również inne operacje, takie jak zamiana osób miejscami czy dopisanie nowej. Nasza bohaterka obawia się jednak, że jej notes może wpaść w niepowołane ręce. Właśnie dlatego nadała wszystkim osobom unikalne pseudonimy. Jak można się domyślić prowadzenie takiego notatnika jest bardzo trudne i pracochłonne. Partycja chciałaby mieć program, który pomoże jej z tym zadaniem.

## Wejście:

W pierwszej linii wejścia program otrzymuje liczbę **n** oznaczającą początkową liczbę osób na liście. Następnie w n liniach program otrzymuje ciągi znaków **s** będących pseudonimami osób. Zakładamy, że pierwsza osoba na liście najbardziej zagraża Partycji. W kolejnym kroku program otrzymuje liczbę **m** będącą ilością operacji do wykonania. Na koniec w m liniach program otrzymuje opisy operacji. Pierwszy znak zawsze oznacza akcję do wykonania, a po nim pojawiają się stosowne dane zgodnie z poniższym opisem:

__**a**__ **s** – dodanie osoby o pseudonimie s na koniec listy, gdzie s jest ciągiem znaków
__**m**__ **s** **x** – przesunięcie osoby o pseudonimie s na liście o x miejsc, gdzie s jest ciągiem znaków, a x liczbą całkowitą (jeżeli x jest dodatnie to przesuwamy osobę w górę listy, w przeciwnym wypadku w dół)
__**r**__ **s1** **s2** – zamiana miejscami osoby o pseudonimie s1 z osobą o pseudonimie s2, gdzie s1 i s2 są ciągiem znaków

## Wyjście:

Na wyjściu program powinien wypisać listę pseudonimów poczynając od osoby najniebezpieczniejszej.

**1 < n ≤ 50000**

**1 < m ≤ 10000**

## Przykładowe wejście:

```
5
Okruszek
Tester
Interfejs
Agent
Scyzoryk
4
r Okruszek Interfejs
a Kontakt
m Kontakt 2
m Interfejs -1
```

## Przykładowe wyjście:

```
Tester
Interfejs
Okruszek
Kontakt
Agent
Scyzoryk
```

## Uwaga:
**Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych drzew czerwono-czarnych bez wykorzystania bibliotek STL.**