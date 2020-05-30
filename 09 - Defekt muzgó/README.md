# Defekt muzg�
Partycja ma ju� do�� tego roku. Wydawa�oby si�, �e kosmiczna katastrofa mog�ca oznacza� koniec �ycia na ziemi to wystarczaj�cy pow�d by uzna� rok za nie najlepszy. A tu do tego dosz�y po�ary, pandemia i id�ca za tym kwarantanna. Partycja siedz�c w domu z nud�w zacz�a s�ucha� starych kaset (dobrze, �e magnetofonu nie wyrzuci�a na �mieci) i przypomnia�a jej si� jej buntownicza m�odo��, Ach gdyby zamiast chodzi� na punkowe koncerty uczy�a si� przed matur� matematyki. Sko�czy�aby informtyk� i �y�a teraz jak kr�lowa.

Partycja szybko przypomnia�a sobie, �e to wszystko nie ma znaczenia, bo prawdopodobnie nie do�yje pocz�tku pa�dziernika. ,,No future'' pomy�la�a sobie i si�gn�a po kaset� The Exploited. A potem przypomnia� si� jej jeden z jej ulubionych punkowych numer�w.

,,Wszyscy jedziemy na tym samym w�zku,
od strachu ratuje nas tylko defekt m�zgu''.

nuci�a Partycja hit Defektu muzg�, ale przypomnia�a sobie, �e jednak nie wszyscy jad� na tym samym w�zku, bo w�zki niekt�rych s� nieco wygodniejsze.  To jeszcze bardziej popsu�o Partycji nastr�j. Jednak, jako �e w ci�gu ostatnich kilku miesi�cy Partycja przywyk�a do porz�dkowania wszystkiego, postanowi�a  zrobi� porz�dek ze swoimi kasetami, �eby w razie potrzeby bez problemu odnale�� ukochan� p�yt�.

## Wej�cie:

W pierwszej linii wej�cia program otrzymuje liczb� **n** oznaczaj�c� liczb� operacji na bazie kaset a nast�pnie n opis�w operacji z poni�szej listy

**d** � dodanie do bazy nowej kasety, w przypadku tej operacji w kolejnych dw�ch liniach znajdowa�a si� b�dzie nazwa zespo�u i tytu� kasety.
**w** � wypisanie w osobnych liniach tytu��w kaset podanego zespo�u. Nazwa zespo�u zostanie podana w kolejnej linii wej�cia. Zespo�u nale�y wypisywa� w kolejno�ci ich dodawania do bazy.
**z**� wypisanie w osobnych liniach zespo��w, kt�re nagra�y kaset� o  podanym tytule. Nazwa zespo�u zostanie podana w kolejnej linii. Nazwy zespo��w nale�y wypisywa� w kolejno�ci dodawania kaset o podanym tytule do bazy.

```
1<=n<=100000
```

## Wyj�cie:

Na standardowym wyj�ciu program powinien wypisa� efekty dzia�ania operacji **w** i **z**. W przypadku gdy w bazie nie ma zespo�u o podanej nazwie (operacja **w**) lub kasety o podanym tytule (operacja **z**) program nie powinien niczego wypisa�.

## Przyk�adowe wej�cie:
```
5
d
Defekt muzg�
Wszyscy jedziemy...
d
Zielone �abki
Lekcja historii
d
Defekt muzg�
Lekcja historii
w 
Defekt muzg�
z
Lekcja historii
z
Wszyscy pokutujemy
```

## Przyk�adowe wyj�cie:
```
Wszyscy jedziemy...
Lekcja historii
Zielone �abki
Defekt muzg�
```

## Uwaga:
**Zadanie ma zosta� rozwi�zane przy pomocy samodzielnie zaimplementowanych drzew splay.**