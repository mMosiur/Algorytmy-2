# Podróż do Warszawy

Partycja Logiczna podczas ferii wpadła na innowacyjne rozwiązanie dotyczące technologii elastycznych ekranów. Chciałaby sfinalizować swój pomysł, a więc wymaga to odwiedzenia naszej pięknej stolicy i siedziby Agencji Techniki i Technologii. Niestety to kawałek drogi, a Partycje jazda samochodem bardzo stresuje. W związku z tym wpadła na pomysł, że zabierze ze sobą swoją koleżankę Magistrale. Ona również nie cieszy się wizją prowadzenia samochodu, jednakże bardzo chciałaby zobaczyć Warszawę.

Partycja wymyśliła system, który pozwala zminimalizować czas prowadzenia samochodu, co narazi ją na mniejszy stres. Po drodze do Warszawy znajduje się n postojów, które numerujemy liczbami od **0** do **n - 1**. Numerem s jest oznaczone miejsce, z którego dziewczyny ruszają w trasę, zaś numerem **d** miejsce docelowe - Warszawa. Po naniesieniu odpowiedniej siatki na mapę, Partycja zauważyła pewną ciekawą zależność. Mianowicie doszła do wniosku, że mogą poruszać się tylko w jednym z czterech kierunków świata. Dodatkowo zgodnie z naniesioną siatką każdy z postojów był na przecięciu osi odciętych i rzędnych.

Nasza inteligentna bohaterka wpadła na pomysł, że za każdym razem, gdy zmienią swój kierunek o 90 stopni zamieniają się miejscami przy kierownicy. Dodatkowo po drodze mogą zatrzymać się na dowolnej ilości postojów, nie ma znaczenia, jak długo będzie trwała cała trasa. Dla Partycji liczy się tylko to, że powinna być za kierownicą możliwie najkrócej. Na koniec aby dać sobie więcej możliwości do zrezygnowania z prowadzenia automobila, Partycja zaproponowała jeszcze jedną zasadę. Dziewczyny ustaliły, że po każdym postoju Partycja może zdecydować, czy usiądzie za kierownicą. Innymi słowy na każdym fragmencie trasy prowadzącym z postoju do postoju jedna z kobiet usiądzie za kierownicą, gdy poruszają się północ, południe, zaś druga z nich prowadzi podczas jazdy na wschód lub zachód. W szczególności, jeśli pewien odcinek trasy prowadzi dokładnie w jednym z czterech kierunków świata, wtedy na tym odcinku prowadzi tylko jedna z kobiet.

Partycja zastanawia się, jak zaplanować trasę do siedziby Agencji Techniki i Technologii oraz podział pracy, by spędzić za kierownicą jak najmniej czasu. Przyjmujemy, że jedna jednostka na siatce jest równa jednej jednostce stresu Partycji, który należy zminimalizować.

## WEJŚCIE

W pierwszej linii wejścia znajduje się liczba naturalna **n**, mówiąca o ilości postojów. Następnie program powinien wczytać **n sekwencji danych: x y**, które są współrzędnymi postojów na naniesionej przez Partycje siatce. Na koniec program powinien wczytać dwie liczby naturalne **s** i **d**, które są odpowiednio postojem startowym i postojem docelowym, czyli siedzibą instytucji, do której zmierza nasza bohaterka. Każdy postój ma inne współrzędne.

**0 <= n <= 32000**
**0 <= x, y, s, d <= 2000000000**

## WYJŚCIE

Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest możliwie najmniejszą liczbą jednostek stresu, które przeżyje nasza bohaterka na trasie z punktu **s** do punktu **d**.

## PRZYKŁADOWE DANE WEJŚCIOWE
```
5
2 2
1 1
4 5
7 1
6 7
0 4
```

## PRZYKŁADOWE DANE WYJŚCIOWE
```
2
```