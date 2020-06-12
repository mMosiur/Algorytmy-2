# Defekt muzgó

Partycja ma już dość tego roku. Wydawałoby się, że kosmiczna katastrofa mogąca oznaczać koniec życia na ziemi to wystarczający powód by uznać rok za nie najlepszy. A tu do tego doszły pożary, pandemia i idąca za tym kwarantanna. Partycja siedząc w domu z nudów zaczęła słuchać starych kaset (dobrze, że magnetofonu nie wyrzuciła na śmieci) i przypomniała jej się jej buntownicza młodość, Ach gdyby zamiast chodzić na punkowe koncerty uczyła się przed maturą matematyki. Skończyłaby informtykę i żyła teraz jak królowa.

Partycja szybko przypomniała sobie, że to wszystko nie ma znaczenia, bo prawdopodobnie nie dożyje początku października. ,,No future'' pomyślała sobie i sięgnęła po kasetę The Exploited. A potem przypomniał się jej jeden z jej ulubionych punkowych numerów.

_,,Wszyscy jedziemy na tym samym wózku,<br>
od strachu ratuje nas tylko defekt mózgu''._

nuciła Partycja hit Defektu muzgó, ale przypomniała sobie, że jednak nie wszyscy jadą na tym samym wózku, bo wózki niektórych są nieco wygodniejsze. To jeszcze bardziej popsuło Partycji nastrój. Jednak, jako że w ciągu ostatnich kilku miesięcy Partycja przywykła do porządkowania wszystkiego, postanowiła zrobić porządek ze swoimi kasetami, żeby w razie potrzeby bez problemu odnaleźć ukochaną płytę.

## Wejście:
W pierwszej linii wejścia program otrzymuje liczbę **n** oznaczającą liczbę operacji na bazie kaset a następnie n opisów operacji z poniższej listy

* **d** – dodanie do bazy nowej kasety, w przypadku tej operacji w kolejnych dwóch liniach znajdowała się będzie nazwa zespołu i tytuł kasety.
* **w** – wypisanie w osobnych liniach tytułów kaset podanego zespołu. Nazwa zespołu zostanie podana w kolejnej linii wejścia. Zespołu należy wypisywać w kolejności ich dodawania do bazy.
* **z** – wypisanie w osobnych liniach zespołów, które nagrały kasetę o podanym tytule. Nazwa zespołu zostanie podana w kolejnej linii. Nazwy zespołów należy wypisywać w kolejności dodawania kaset o podanym tytule do bazy.

**UWAGA: w zestawach mogą pojawić się linie, które nie pasują do powyższego wzorca (zamiast jednoznakowego symbolu polecenia mogą pojawić się dłuższe linie). Takie linie program powinien ignorować.**
```
1<=n<=100000
```

## Wyjście:
Na standardowym wyjściu program powinien wypisać efekty działania operacji **w** i **z**. W przypadku gdy w bazie nie ma zespołu o podanej nazwie (operacja **w**) lub kasety o podanym tytule (operacja **z**) program nie powinien niczego wypisać.

### Przykładowe wejście:
```
5
d
Defekt muzgó
Wszyscy jedziemy...
d
Zielone żabki
Lekcja historii
d
Defekt muzgó
Lekcja historii
w
Defekt muzgó
z
Lekcja historii
z
Wszyscy pokutujemy
```

### Przykładowe wyjście:
```
Wszyscy jedziemy...
Lekcja historii
Zielone żabki
Defekt muzgó
```

## Uwaga:
**Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych drzew splay.**