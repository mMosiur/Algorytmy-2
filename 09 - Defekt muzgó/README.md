# Defekt muzgó
Partycja ma ju¿ doœæ tego roku. Wydawa³oby siê, ¿e kosmiczna katastrofa mog¹ca oznaczaæ koniec ¿ycia na ziemi to wystarczaj¹cy powód by uznaæ rok za nie najlepszy. A tu do tego dosz³y po¿ary, pandemia i id¹ca za tym kwarantanna. Partycja siedz¹c w domu z nudów zaczê³a s³uchaæ starych kaset (dobrze, ¿e magnetofonu nie wyrzuci³a na œmieci) i przypomnia³a jej siê jej buntownicza m³odoœæ, Ach gdyby zamiast chodziæ na punkowe koncerty uczy³a siê przed matur¹ matematyki. Skoñczy³aby informtykê i ¿y³a teraz jak królowa.

Partycja szybko przypomnia³a sobie, ¿e to wszystko nie ma znaczenia, bo prawdopodobnie nie do¿yje pocz¹tku paŸdziernika. ,,No future'' pomyœla³a sobie i siêgnê³a po kasetê The Exploited. A potem przypomnia³ siê jej jeden z jej ulubionych punkowych numerów.

,,Wszyscy jedziemy na tym samym wózku,
od strachu ratuje nas tylko defekt mózgu''.

nuci³a Partycja hit Defektu muzgó, ale przypomnia³a sobie, ¿e jednak nie wszyscy jad¹ na tym samym wózku, bo wózki niektórych s¹ nieco wygodniejsze.  To jeszcze bardziej popsu³o Partycji nastrój. Jednak, jako ¿e w ci¹gu ostatnich kilku miesiêcy Partycja przywyk³a do porz¹dkowania wszystkiego, postanowi³a  zrobiæ porz¹dek ze swoimi kasetami, ¿eby w razie potrzeby bez problemu odnaleŸæ ukochan¹ p³ytê.

## Wejœcie:

W pierwszej linii wejœcia program otrzymuje liczbê **n** oznaczaj¹c¹ liczbê operacji na bazie kaset a nastêpnie n opisów operacji z poni¿szej listy

**d** – dodanie do bazy nowej kasety, w przypadku tej operacji w kolejnych dwóch liniach znajdowa³a siê bêdzie nazwa zespo³u i tytu³ kasety.
**w** – wypisanie w osobnych liniach tytu³ów kaset podanego zespo³u. Nazwa zespo³u zostanie podana w kolejnej linii wejœcia. Zespo³u nale¿y wypisywaæ w kolejnoœci ich dodawania do bazy.
**z**– wypisanie w osobnych liniach zespo³ów, które nagra³y kasetê o  podanym tytule. Nazwa zespo³u zostanie podana w kolejnej linii. Nazwy zespo³ów nale¿y wypisywaæ w kolejnoœci dodawania kaset o podanym tytule do bazy.

```
1<=n<=100000
```

## Wyjœcie:

Na standardowym wyjœciu program powinien wypisaæ efekty dzia³ania operacji **w** i **z**. W przypadku gdy w bazie nie ma zespo³u o podanej nazwie (operacja **w**) lub kasety o podanym tytule (operacja **z**) program nie powinien niczego wypisaæ.

## Przyk³adowe wejœcie:
```
5
d
Defekt muzgó
Wszyscy jedziemy...
d
Zielone ¿abki
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

## Przyk³adowe wyjœcie:
```
Wszyscy jedziemy...
Lekcja historii
Zielone ¿abki
Defekt muzgó
```

## Uwaga:
**Zadanie ma zostaæ rozwi¹zane przy pomocy samodzielnie zaimplementowanych drzew splay.**