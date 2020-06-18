# Włochaty

Partycja zainspirowana piosenką ,,Zmowa'' w której wokalista anarcho-punkowego zespołu Włochaty wykrzykuje m. in.

*Zmowa powszechna przeciwko rządowi<br>
To pragnienie ciągle żywe<br>
Choć przez lata zagłuszane troską<br>
O wodę, pożywienie, dach nad głową*

zrozumiała, że aby pokonać spisek światowych rządów nie może działać sama. Musi działać razem z innymi obywatelami, bo rządzący są bezradni wobec zgodnego działania większości obywateli. Dlatego Partycja postanowiła wystartować w wyborach prezydenckich. Co prawda jest niewiele czasu na zebranie wymaganej przez prawo liczby podpisów osób popierających jej kandydaturę, ale dzięki sieci współpracujących z nią wolontariuszy ma nadzieję, że uda jej się pokonać tą przeszkodę. Szczególnie, że jak pokazała przeprowadzona tydzień wcześniej analiza, teksty Partycji docierają do ogromnej rzeszy ludzi.

We współczesnej informatyce ogromną rolę odgrywają ciała skończone. Wystarczy wspomnieć, że to na nich w znacznej mierze opiera się kryptografia klucza publicznego. Partycja wykorzystuje równania nad skończonymi ciałami do budowania modeli rozprzestrzeniania się informacji w sieci. Chce je wykorzystać do tego, żeby jak najskuteczniej dotrzeć ze swoim przekazem do wyborców. Niestety prawdopodobnie nie istnieje wielomianowy algorytm rozwiązujący równania nad skończonymi ciałami. Partycja przeczytała jednak ostatnio, że wielomiany o ograniczonym stopniu można rozwiązać w czasie liniowym używając algorytmu losującego z jednostajnym prawdopodobieństwem wartości zmiennych i sprawdzającego czy wylosowane wartościowanie spełnia równanie. Okazuje się bowiem, że dla ciała **Z<sub>q</sub>** jeżeli wielomian stopnia **d** o **n** zmiennych przyjmuje jakąś wartość, to przyjmuje ją dla co najmniej **q<sup>n-d-glog(q)</sup>** wartościowań.

Ciało **Z<sub>q</sub>** dla liczby pierwszej **q** to struktura w której elementami są liczby 0,1,...,q-1 a działaniami są dodawanie i mnożenie modulo **q**. Wielomiany można przedstawić jako sumę stałych i jednomianów przemnożonych przez stałe t.j. iloczynów zmiennych podniesionych do różnych potęg. Stopień jednomianu to suma stopni przemnożonych zmiennych. Stopień wielomianu, to maksymalny stopień jednomianu występującego w sumie definiującej dany wielomian.

## Wejście

W pierwszej linii wejścia program otrzyma liczba **n** zmiennych oraz **m** jednomianów w rozważanym wielomianie a także liczbę pierwszą **q** oznaczającą rozmiar ciała nad którym prowadzone są obliczenia. W kolejnych **m** liniach podawane będą jednomiany których sumą jest wielomian w następującym formacie: najpierw liczba **z** zmiennych w jednomianie, potem stała przez którą należy przemnożyć jednomian a następnie **z** par liczb postaci **a** **b** gdzie **a** oznacza numer zmiennej a **b** potęgę w jakiej występuje (potęgi są większe od 0 i mniejsze niż **q**, zmienne są numerowane od 0).

Na koniec program otrzyma stałą **c**.

## Wyjście:

Na standardowym wyjściu program powinien wypisać TAK jeżeli istnieje wartościowanie dla którego wczytany wielomian ma wartość **c** i NIE w przeciwnym wypadku.

### Przykładowe wejście:
```
3 2 5
2 3 0 4 1 4
2 3 1 4 2 4
2
```

### Przykładowe wyjście:
```
NIE
```