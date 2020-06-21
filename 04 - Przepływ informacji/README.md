# Przepływ informacji

Partycja Logiczna po powrocie z Warszawy pochwaliła się swoim innowacyjnym pomysłem znajomym. Zauważyła, że w niektórych grupach społecznych, do których należy, przepływ informacji jest bardzo dobry. W innych zaś wiadomość, którą się podzieliła, wróciła do niej. Wszystko byłoby w porządku, gdyby jej rozmówca wiedział, że ten innowacyjny pomysł należy do jej osoby. Niestety... rozczarowujące okazało się, że jej interlokutor nie był tego świadomy. Nic w tym dziwnego komunikacja interpersonalna powoduje, że dane często stają się “zaszumione” - przykładem może być gra “głuchy telefon”.

Cała sytuacja bardzo zdenerwowała naszą bohaterkę i doszła do wniosku, że nie będzie chwaliła się swoimi osiągnięciami w środowiskach, gdzie informacje mogą zataczać koło. Chce zmniejszyć prawdopodobieństwo wystąpienia takiej sytuacji, dlatego skłonna jest wykluczyć wszystkie grupy społeczne, gdzie dowolna informacja może do kogoś wrócić.

Bohaterka wie, że rozmawiają ze sobą osoby o wspólnych zainteresowaniach. Dodatkowo osoby te mogą rozmawiać na różne tematy, nie tylko te dotyczące wspólnych zainteresowań. Innymi słowy przepływ informacji jest pomiędzy tymi dwiema osobami. Osoba, która otrzymała informacje od swojego rozmówcy może przekazać je innemu rozmówcy, z którym również ma wspólne zainteresowania.

Partycja zastanawia się, które grupy społeczne wykluczyć ze swojego przepływu informacji.

## WEJŚCIE

W pierwszej linii wejścia znajduje się liczba naturalna **n**, mówiąca o ilości osób w danej grupie społecznej. Następnie program powinien wczytać **n sekwencji danych: m**, czyli ilość zainteresowań danego członka grupy społecznej, a następnie **m liczb całkowitych** będących odpowiednikami dziedzin, którymi jest zainteresowana ta osoba.

**0 <= n, m, numery dziedzin <= 2000000000**

## WYJŚCIE

Na wyjściu algorytm powinien wypisać jedną z informacji: **TAK** - jeśli jakaś informacja może wrócić do tej samej osoby i tym samym Partycja powinna wykluczyć tą grupę, **NIE** - w przeciwnym wypadku.

## PRZYKŁADOWE DANE WEJŚCIOWE

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

## PRZYKŁADOWE DANE WYJŚCIOWE

I
```
NIE
```

II
```
TAK
```

## UWAGI

Rozwiązane zadania powinno być implementacją struktury zbiorów rozłącznych.