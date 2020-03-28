# Podró¿ do Warszawy i smako³yki

Partycja Logiczna przemyœla³a swoje plany i dosz³a do wniosku, ¿e mo¿e obni¿yæ swój stres na niektórych postojach. W koñcu uwielbia jeœæ, a to na pewno obni¿a kortyzol w jej organizmie. Przynajmniej bêdzie tak pomiêdzy postojami. Nasza bohaterka rozbudowa³a opis postojów na siatce o dodatkow¹ wartoœæ v. Ta wartoœæ to liczba, która reprezentuje iloœæ jednostek stresu, jak¹ mo¿e obni¿yæ dany postój.

Usprawnij poprzedni program tak by bra³ pod uwagê ewentualne przyjemnoœci kulinarne na postojach.

## Wejœcie

W pierwszej linii wejœcia znajduje siê liczba naturalna n, mówi¹ca o iloœci postojów. Nastêpnie program powinien wczytaæ **n sekwencji danych: x y v**, które s¹ wspó³rzêdnymi postojów na naniesionej przez Partycje siatce. Na koniec program powinien wczytaæ dwie liczby naturalne **s** i **d**, które s¹ odpowiednio postojem startowym i postojem docelowym, czyli siedzib¹ instytucji, do której zmierza nasza bohaterka. Ka¿dy postój ma inne wspó³rzêdne.

**0 <= n, v <= 32000**<br>
**0 <= x, y, s, d <= 2000000000**


## Wyjœcie
Na wyjœciu algorytm powinien wypisaæ jedn¹ liczbê ca³kowit¹, która jest mo¿liwie najmniejsz¹ liczb¹ jednostek stresu, które prze¿yje nasza bohaterka na trasie z punktu **s** do punktu **d**. Mo¿e dojœæ do sytuacji, gdy podró¿owanie na pewnym odcinku bêdzie przynosi³o Partycji ci¹g³e przyjemnoœci. W takiej sytuacji nale¿y zmusiæ nasz¹ bohaterkê by szybko wróci³a na trasê do Warszawy wyœwietlaj¹c komunikat: NIE ZA DOBRZE?

### Przyk³adowe dane wejœciowe
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

## Przyk³adowe dane wyjœciowe
I
```
2
```

II
```
NIE ZA DOBRZE?
```