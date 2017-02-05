

Adeptus Elektronicus
===
## Spotkanie 1 - Laboratorium szalonego elektronika


Mróz Krzysztof
hs3city.slack.com : @mroz
private@mrozo.pl

---

Filozofia
===

1. Jest to spis rzeczy wybitnie przydatnych do pierwszego laboratorium.
2. Zakłada się, że pierwsze laboratorium jest laboratorium z góry spisanym na straty.
3. Spis i porady zostały przygotowany z myślą o niskiej cenie, no ale bez przesady.
4. Szczególnie premiowane są platformy darmowe.
5. Szczególnie szczególnie premiowane są platformy otwarto-źródłowe.

<!-- footer: 6. nec temere, nec timide -->
<!-- page_number: true -->

---

Narzędzia
===

1. Multimetr - generyczny, czarny no-name, do 15 zł, 2 szt. - 30 zł.
2. Lutownica - YiHUA 936, chińska podróba Hakko, 75 zł.
3. Odsysacz do cyny - 5 zł, 2 szt - 10 zł.
4. Trzecia ręka - 10 zł.
5. Szczypce boczne - 20zł

**Suma 145 zł.**

<!-- footer: -->

---


Materiały i części
===

1. przewody - np. przewód domofonowy 8p. 1,80 zł/m, 5 m - 9 zł.
2. przewody krokodyl - 10 szt. - 10 zł.
3. taśma izolacyjna - 10 kolorów - 20 zł.
4. koszulki termokurczliwe - zestaw - 10 zł.
5. Rezystory THT - zestaw 24 wartości po 20 szt. - 25 zł.
6. Led 3 mm, THT - 50 szt. - 5 zł.
7. Płytka stykowa - ~600-800 pól - 10 zł.

---

Materiały i części cd.
===

7. Uniwersalne płytki pcb - 5 x 7 cm, dwustronne zielone, 5 szt - 15 zł.
8. Przyciski THT - 20 szt. - 7 zł.
9. Przełączniki DIP SWITCH - 8-smio pozycyjny, THT, 5 szt. - 5 zł.
10. Potencjometry THT - 10 kOhm x 5, 100 kOhm x 5, 1 MOhm x 5szt - 6 zł.
11. Cyna ~0,56 mm - najlepiej z ołowiem - 15 zł.

**Suma 137 zł.**

---
Przydatne, opcjonalne odatki
===

1. źródło zasilania laboratoryjne
1.a. zasilacz PC, ładowarka USB, LUB
1.b. zasilacz laptopowy + konwerter BUCK-BOOST (15 zł.)
2. zasilanie układów
2.a. Stabilizatory LM7805 3 szt. - 3 zł.
2.b. Stabilizatory LM3117 3 szt. - 3 zł.
2.c. Kondensatory 100 nF ceramik + 100 uF elektrolit x 5 - 5 zł.

---
Przydatne, opcjonalne dodatki, cd.
===

3. Zasilanie bateryjne
3.a. koszyczek 2 x AA, 2 szt. - 2 zł.
3.b. koszyczek 4 x AA, 2 szt. - 5 zł.
3.c. złącza na baterie 9 V, 2 szt. - 2 zł.
4. Pudełko na projekty - 2-10 zł.
5. Termoklej + zapalniczka - 20 zł.
6. Półeczki warsztatowe - ~100 zł.

---


Rdzeń
===

Arduino. Koniec.
Koszt - od 23 zł.

Jeśli możesz - kup oryginał.

---

Sklepy - czyli gdzie to kupić
===

1. tme.eu - sprzedaż hurtowa - duży asortyment, szybka obsługa, stosunkowo drogi
2. maritex.com.pl - hurtownia w Gdyni, średni asortyment, stosunkowo tani
3. digikey.com - największa hurtownia części elektronicznych, droga przesyłka
4. gotronik.pl - narzędzia, moduły - działa

---

Sklepy - czyli gdzie kupić, cd.
===

5. Jacktronic - spory asortyment elektroniczny, ul. Wita Stwosza 32a, Gdańsk, jacktronic.pl
6. Cezar S.C - asortyment raczej elektryczny, ul. Jesionowa 1, Gdańsk
7. Bowi - asortyment elektryczny, audio-wideo, CCTV, Grunwaldzka 345, Gdańsk, bowi.com.pl
8. Części elektroniczne - asortyment elektroniczny, Aleja Generała Józefa Hallera 169, Gdańsk

---

Koszt w sumie
===

** Suma: 305 zł + koszta przesyłek, czyli jakieś 315 - 350 zł. **

---

Oprogramowanie
===

1. OS - linux
2. Projektowanie układów elektronicznych i PCB - KiCad
3. Programowanie - Arduino IDE/Eclipse + Arduino plugin
4. Symulacja układów - LtSpice

<!-- footer: ad.1. "linux is like a tipi - no windows, no gates and apache inside" - unknown author -->

---

Oprogramowanie, cd.
===

5. Szybka symulacja układów "na brudno": Circuit Simulator Applet
6. Przeglądarka internetowa
7. przeglądarka PDF

<!-- footer: -->

---

Notka o chmurze
===

Odradza się korzystanie z oprogramowania CAD hostowanego w chmurze. Jest to wysoce ryzykowne ze względu na niestabilność firm opiekujących się takimi produktami, a dodatkowo projekty elektroniczne nie są portowalne między programami CAD.

---

Notka o Arduino i prawnikach
===

Jakiś czas temu doszło do rozłamu między twórcami platformy/bibliotek arduino. W wyniku tego doszło do powstania dwóch stron: arduino.org oraz arduino.cc, a także do pojawienia się produktów sygnowacych nazwą Genuino. Wynika to z problemów licencyjnych, a w praktyce nie ma różnicy między tymi produktami.

---

Notka o multimetrach
===

1. Nie podłączaj ich do 230 V. To są tanie Chińczyki.
2. Zawsze uważaj, aby sądy podczas pomiaru były podłączone do odpowiednich gniazd.
3. Nie dokonuj pomiarów rezystancji na włączonym układzie.
4. Kontrola ciągłości jest bardzo przydatnym trybem pracy multimetru.

<!-- footer: ad.3. No chyba że wiesz co robisz, ale wtedy co Ty tutaj robisz?! -->

---

Notka o diodkach LED
===

1. **zawsze** wpinaj LED na zasilaniu - oszczędzi Ci to wiele czasu i przekleństw.
2. LED podłączaj **zawsze** przez rezystor.
2. Można bezpiecznie założyć, że małe, sygnalizacyjne diody LED (np. 3 mm) pracują przy prądzie równym 1 mA i napięciu 1,5 V.Czyli przy zasilaniu 5 V rezystor powinien mieć wartość od 3 do 4 kOhm, zas dla 3,3 V od 1,5 do 2 kOhm.

<!-- footer: -->

---


Koniec
===

> Temat drążony tysiące razy, kasuje wątek.
>
> <small>-- *[Gaia (mythology) - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Gaia_%28mythology%29)*</small>


