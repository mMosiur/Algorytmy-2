# Zadanie 12 - Hańba

Ile można siedzieć w domu? Czego tu się bać jak planuje się żyć do jesieni? Partycja postanowiła kontestować otaczającą rzeczywistość i zaczęła chodzić na długie spacery (oczywiście w maseczce, bo co za dużo kontestowania to nie zdrowo). Odkryła też, że Julian Tuwim wielkim poetą był. A w tym odkryciu pomógł jej zespół Hańba, który fragmenty wiersza ,,Mój dzionek'' wyśpiewuje w piosence ,,Hoży i świeży''. O ironio! Broni ludzi inteligentnych. Zakrzyknęła Partycja i zaczęła śpiewać:

*Le­d­wo sło­necz­ko ude­rzy<br>
W okno zło­ci­stym pro­my­kiem,<br>
Bu­dzę się hoży i świe­ży<br>
Z an­ty­pań­stwo­wym okrzy­kiem.*

W trakcie swych długich spacerów Partycja pokonuje wiele kilometrów. Nie wie niestety jak wiele bo ze względów bezpieczeństwa nie zabiera ze sobą telefonu (Wielki Brat patrzy!) i nie ma jak zapisywać swojej trasy. Wymyśliła więc sposób, jak w przybliżeniu oszacować pokonywany dystans. Raz na jakiś czas Partycja pyta przypadkowych przechodniów o współrzędne punktu w którym się znajdują. W ten sposób powstała baza punktów przez które przechodziła Partycja. Ponieważ Partycja nie zawsze chodzi tą samą trasą punkty nie układają się w jedną ścieżkę. Partycja chodzi dookoła swojego domu, który oznacza jako punkt (0,0). Chce od góry oszacować długość pokonywanej trasy i dlatego w przypadku wczytania wielu punktów znajdujących się na jednej półprostej o początku w punkcie (0,0) usuwa ze zbioru punktów wszystkie punkty leżące na tej półprostej poza punktem najbardziej odległym od początku układu współrzędnych (punktu (0,0)).

## Wejście:

W pierwszej linii wejścia program otrzyma liczbę **n** punktów w zbiorze a następnie, **n** par liczb całkowitych opisujących współrzędne punktu w zbiorze.
```
1<=n<=100000
```

## Wyjście:

Na standardowym wyjściu program powinien wypisać wczytane punkty uporządkowane względem amplitudy w ich reprezentacji w biegunowym układzie współrzędnych o biegunie w punkcie (0,0) i osi OX jako osi biegunowej. Spośród punktów o takiej samej amplitudzie powinien zostać wypisany tylko jeden, ten o największym promieniu wodzącym.

### Przykładowe wejście:
```
6
0 0
1 2
2 1
5 0
-1 -2
4 2
```

### Przykładowe wyjście:
```
5 0
4 2
1 2
-1 -2
```