# Festiwal smaku

Jak wiadomo w Lublinie czêsto odbywaj¹ siê spotkania kulinarne, degustacyjne i ró¿ne festiwale smaku. Jedna z kole¿anek Partycji (z grupy spo³ecznej, której nie wykluczy³a:) ) zajmuje siê organizacj¹ festiwalu degustacji tradycyjnych polskich potraw. Chcia³aby, aby to wydarzenie by³o jednym z najlepszych. Zale¿y jej na tym, aby ka¿dy zjad³ to, na co ma ochotê.

W zwi¹zku z tym Jagoda, bo tak ma na imiê kole¿anka naszej bohaterki, poprosi³a wszystkich zaproszonych na festiwal o wype³nienie ankiety. Ankieta polega na tym, ¿e ka¿dy uczestnik wydarzenia musi wybraæ potrawy, które chcia³by skosztowaæ. Oczywiœcie taka osoba mo¿e zaznaczyæ dowoln¹ iloœæ potraw z listy, które chêtnie by zjad³a. Uczestnik mo¿e zaznaczyæ wszystkie potrawy, ale równie dobrze mo¿e nie zaznaczyæ ¿adnej - wtedy wiemy, ¿e nie bêdzie on zadowolony. Poniewa¿ s¹ to bardzo ekskluzywne potrawy i kunsztowne, ekskluzywne wydarzenie na ka¿dego uczestnika przypada tylko jedna degustacja. Niestety dobranie odpowiednich posi³ków dla ka¿dego z goœci, jest ogromnym wyzwaniem organizacyjnym. Wynika to przede wszystkim z tego, ¿e ka¿dej potrawy zostanie przygotowana taka sama, ograniczona iloœæ. Dodatkowo Jagoda chce aby, jak najwiêcej osób wysz³o z wydarzenia zadowolonych. To zadowolenie gwarantuje jedynie to, ¿e przybysze zjedz¹ potrawê, która by³a na ich liœcie ¿yczeñ.


## WEJŒCIE
W pierwszej linii wejœcia znajduj¹ siê liczby naturalne **n** **m** **l**, **n** - to liczba uczestników wydarzenia, **m** - to iloœæ dostêpnych potraw, zaœ **l** - to iloœæ zestawów degustacyjnych ka¿dej z potraw. Nastêpnie program powinien wczytaæ wyniki ankiety, które s¹ podane w macierzy o wymiarach **n x m**. Gdy uczestnik chce spróbowaæ potrawy wprowadzi³ ‘**x**’, a w przeciwnym wypadku ‘**o**’.

**0 <= n, m, l <= 2000000000**


## WYJŒCIE
Na wyjœciu algorytm powinien wypisaæ jedn¹ liczbê ca³kowit¹, która jest najwiêksz¹ mo¿liw¹ liczb¹ osób zadowolonych z uczestnictwa w wydarzeniu.


## PRZYK£ADOWE DANE WEJŒCIOWE
```
6 3 2
o o x
x x x
o o x
x o o
x o x
x o o
```

## PRZYK£ADOWE DANE WYJŒCIOWE
```
5
```

## UWAGI
Rozwi¹zane zadania powinno byæ implementacj¹ metody wyszukiwania maksymalnego skojarzenia w grafie dwudzielnym