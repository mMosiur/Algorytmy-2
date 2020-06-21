# Podróż do Warszawy i smakołyki

Partycja Logiczna przemyślała swoje plany i doszła do wniosku, że może obniżyć swój stres na niektórych postojach. W końcu uwielbia jeść, a to na pewno obniża kortyzol w jej organizmie. Przynajmniej będzie tak pomiędzy postojami. Nasza bohaterka rozbudowała opis postojów na siatce o dodatkową wartość v. Ta wartość to liczba, która reprezentuje ilość jednostek stresu, jaką może obniżyć dany postój.

Usprawnij poprzedni program tak by brał pod uwagę ewentualne przyjemności kulinarne na postojach.

## Wejście

W pierwszej linii wejścia znajduje się liczba naturalna n, mówiąca o ilości postojów. Następnie program powinien wczytać **n sekwencji danych: x y v**, które są współrzędnymi postojów na naniesionej przez Partycje siatce. Na koniec program powinien wczytać dwie liczby naturalne **s** i **d**, które są odpowiednio postojem startowym i postojem docelowym, czyli siedzibą instytucji, do której zmierza nasza bohaterka. Każdy postój ma inne współrzędne.

**0 <= n, v <= 32000**<br>
**0 <= x, y, s, d <= 2000000000**


## Wyjście
Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest możliwie najmniejszą liczbą jednostek stresu, które przeżyje nasza bohaterka na trasie z punktu **s** do punktu **d**. Może dojść do sytuacji, gdy podróżowanie na pewnym odcinku będzie przynosiło Partycji ciągłe przyjemności. W takiej sytuacji należy zmusić naszą bohaterkę by szybko wróciła na trasę do Warszawy wyświetlając komunikat: NIE ZA DOBRZE?

### Przykładowe dane wejściowe
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

## Przykładowe dane wyjściowe
I
```
2
```

II
```
NIE ZA DOBRZE?
```