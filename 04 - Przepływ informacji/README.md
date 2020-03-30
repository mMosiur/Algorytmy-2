# Przep³yw informacji

Partycja Logiczna po powrocie z Warszawy pochwali³a siê swoim innowacyjnym pomys³em znajomym. Zauwa¿y³a, ¿e w niektórych grupach spo³ecznych, do których nale¿y, przep³yw informacji jest bardzo dobry. W innych zaœ wiadomoœæ, któr¹ siê podzieli³a, wróci³a do niej. Wszystko by³oby w porz¹dku, gdyby jej rozmówca wiedzia³, ¿e ten innowacyjny pomys³ nale¿y do jej osoby. Niestety... rozczarowuj¹ce okaza³o siê, ¿e jej interlokutor nie by³ tego œwiadomy. Nic w tym dziwnego komunikacja interpersonalna powoduje, ¿e dane czêsto staj¹ siê “zaszumione” - przyk³adem mo¿e byæ gra “g³uchy telefon”.

Ca³a sytuacja bardzo zdenerwowa³a nasz¹ bohaterkê i dosz³a do wniosku, ¿e nie bêdzie chwali³a siê swoimi osi¹gniêciami w œrodowiskach, gdzie informacje mog¹ zataczaæ ko³o. Chce zmniejszyæ prawdopodobieñstwo wyst¹pienia takiej sytuacji, dlatego sk³onna jest wykluczyæ wszystkie grupy spo³eczne, gdzie dowolna informacja mo¿e do kogoœ wróciæ.

Bohaterka wie, ¿e rozmawiaj¹ ze sob¹ osoby o wspólnych zainteresowaniach. Dodatkowo osoby te mog¹ rozmawiaæ na ró¿ne tematy, nie tylko te dotycz¹ce wspólnych zainteresowañ. Innymi s³owy przep³yw informacji jest pomiêdzy tymi dwiema osobami. Osoba, która otrzyma³a informacje od swojego rozmówcy mo¿e przekazaæ je innemu rozmówcy, z którym równie¿ ma wspólne zainteresowania.

Partycja zastanawia siê, które grupy spo³eczne wykluczyæ ze swojego przep³ywu informacji.

## WEJŒCIE

W pierwszej linii wejœcia znajduje siê liczba naturalna **n**, mówi¹ca o iloœci osób w danej grupie spo³ecznej. Nastêpnie program powinien wczytaæ **n sekwencji danych: m**, czyli iloœæ zainteresowañ danego cz³onka grupy spo³ecznej, a nastêpnie **m liczb ca³kowitych** bêd¹cych odpowiednikami dziedzin, którymi jest zainteresowana ta osoba.

**0 <= n, m, numery dziedzin <= 2000000000**

## WYJŒCIE

Na wyjœciu algorytm powinien wypisaæ jedn¹ z informacji: **TAK** - jeœli jakaœ informacja mo¿e wróciæ do tej samej osoby i tym samym Partycja powinna wykluczyæ t¹ grupê, **NIE** - w przeciwnym wypadku.

## PRZYK£ADOWE DANE WEJŒCIOWE

I
```
4
3 1 2 3
2 3 4
2 4 5
2 5 6
```

II
```
4
3 1 2 3
2 3 4
2 4 5
2 3 5
```

## PRZYK£ADOWE DANE WYJŒCIOWE

I
```
NIE
```

II
```
TAK
```

## UWAGI

Rozwi¹zane zadania powinno byæ implementacj¹ struktury zbiorów roz³¹cznych.