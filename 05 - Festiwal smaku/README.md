# Festiwal smaku

Jak wiadomo w Lublinie cz�sto odbywaj� si� spotkania kulinarne, degustacyjne i r�ne festiwale smaku. Jedna z kole�anek Partycji (z grupy spo�ecznej, kt�rej nie wykluczy�a:) ) zajmuje si� organizacj� festiwalu degustacji tradycyjnych polskich potraw. Chcia�aby, aby to wydarzenie by�o jednym z najlepszych. Zale�y jej na tym, aby ka�dy zjad� to, na co ma ochot�.

W zwi�zku z tym Jagoda, bo tak ma na imi� kole�anka naszej bohaterki, poprosi�a wszystkich zaproszonych na festiwal o wype�nienie ankiety. Ankieta polega na tym, �e ka�dy uczestnik wydarzenia musi wybra� potrawy, kt�re chcia�by skosztowa�. Oczywi�cie taka osoba mo�e zaznaczy� dowoln� ilo�� potraw z listy, kt�re ch�tnie by zjad�a. Uczestnik mo�e zaznaczy� wszystkie potrawy, ale r�wnie dobrze mo�e nie zaznaczy� �adnej - wtedy wiemy, �e nie b�dzie on zadowolony. Poniewa� s� to bardzo ekskluzywne potrawy i kunsztowne, ekskluzywne wydarzenie na ka�dego uczestnika przypada tylko jedna degustacja. Niestety dobranie odpowiednich posi�k�w dla ka�dego z go�ci, jest ogromnym wyzwaniem organizacyjnym. Wynika to przede wszystkim z tego, �e ka�dej potrawy zostanie przygotowana taka sama, ograniczona ilo��. Dodatkowo Jagoda chce aby, jak najwi�cej os�b wysz�o z wydarzenia zadowolonych. To zadowolenie gwarantuje jedynie to, �e przybysze zjedz� potraw�, kt�ra by�a na ich li�cie �ycze�.


## WEJ�CIE
W pierwszej linii wej�cia znajduj� si� liczby naturalne **n** **m** **l**, **n** - to liczba uczestnik�w wydarzenia, **m** - to ilo�� dost�pnych potraw, za� **l** - to ilo�� zestaw�w degustacyjnych ka�dej z potraw. Nast�pnie program powinien wczyta� wyniki ankiety, kt�re s� podane w macierzy o wymiarach **n x m**. Gdy uczestnik chce spr�bowa� potrawy wprowadzi� �**x**�, a w przeciwnym wypadku �**o**�.

**0 <= n, m, l <= 2000000000**


## WYJ�CIE
Na wyj�ciu algorytm powinien wypisa� jedn� liczb� ca�kowit�, kt�ra jest najwi�ksz� mo�liw� liczb� os�b zadowolonych z uczestnictwa w wydarzeniu.


## PRZYK�ADOWE DANE WEJ�CIOWE
```
6 3 2
o o x
x x x
o o x
x o o
x o x
x o o
```

## PRZYK�ADOWE DANE WYJ�CIOWE
```
5
```

## UWAGI
Rozwi�zane zadania powinno by� implementacj� metody wyszukiwania maksymalnego skojarzenia w grafie dwudzielnym