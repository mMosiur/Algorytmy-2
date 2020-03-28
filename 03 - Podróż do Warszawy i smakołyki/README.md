# Podr� do Warszawy i smako�yki

Partycja Logiczna przemy�la�a swoje plany i dosz�a do wniosku, �e mo�e obni�y� sw�j stres na niekt�rych postojach. W ko�cu uwielbia je��, a to na pewno obni�a kortyzol w jej organizmie. Przynajmniej b�dzie tak pomi�dzy postojami. Nasza bohaterka rozbudowa�a opis postoj�w na siatce o dodatkow� warto�� v. Ta warto�� to liczba, kt�ra reprezentuje ilo�� jednostek stresu, jak� mo�e obni�y� dany post�j.

Usprawnij poprzedni program tak by bra� pod uwag� ewentualne przyjemno�ci kulinarne na postojach.

## Wej�cie

W pierwszej linii wej�cia znajduje si� liczba naturalna n, m�wi�ca o ilo�ci postoj�w. Nast�pnie program powinien wczyta� **n sekwencji danych: x y v**, kt�re s� wsp�rz�dnymi postoj�w na naniesionej przez Partycje siatce. Na koniec program powinien wczyta� dwie liczby naturalne **s** i **d**, kt�re s� odpowiednio postojem startowym i postojem docelowym, czyli siedzib� instytucji, do kt�rej zmierza nasza bohaterka. Ka�dy post�j ma inne wsp�rz�dne.

**0 <= n, v <= 32000**<br>
**0 <= x, y, s, d <= 2000000000**


## Wyj�cie
Na wyj�ciu algorytm powinien wypisa� jedn� liczb� ca�kowit�, kt�ra jest mo�liwie najmniejsz� liczb� jednostek stresu, kt�re prze�yje nasza bohaterka na trasie z punktu **s** do punktu **d**. Mo�e doj�� do sytuacji, gdy podr�owanie na pewnym odcinku b�dzie przynosi�o Partycji ci�g�e przyjemno�ci. W takiej sytuacji nale�y zmusi� nasz� bohaterk� by szybko wr�ci�a na tras� do Warszawy wy�wietlaj�c komunikat: NIE ZA DOBRZE?

### Przyk�adowe dane wej�ciowe
I
```
5
2 2 0
1 1 0
4 5 1
7 1 0
6 7 0
0 4
```

II
```
5
2 2 0
1 1 1
4 5 1
7 1 0
6 7 0
0 4
```

## Przyk�adowe dane wyj�ciowe
I
```
2
```

II
```
NIE ZA DOBRZE?
```