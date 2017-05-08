

Adeptus Elektronicus
===
## Spotkanie 2 - Elektroniczny bigos, czyli ciąg dalszy nastąpił

 ![](../logo/deus_ex_silicium_256.png)

Mróz Krzysztof
hs3city.slack.com : @mroz
private@mrozo.pl
github.com/mrozo

---

Plan spotkania
===
1. ~~Definicja projektu~~
2. ~~Definicja wymagań funkcjonalnych projektu~~
3. ~~Uzasadnienie wyboru projektu~~
4. Pętla realizacji projektu:
4.1. Wybór wymagania funkcjonalnego.
4.2. Wybór części podstawowych do realizacji wymagania
4.3. Wybór układu realizującego wymagania
5. Analiza wyników

<!-- page_number: true -->

---
Wymagania funkcjonalne projektu
===
1. ~~Bazuje na arduino.~~
2. ~~Pomiar natężenia światła.~~
3. Pomiar mocy chałasu.
4. ~~Pomiar temperatury otoczenia.~~
5. ~~Pomiar wilgotności powietrza.~~
6. Dioda sygnalizująca pomiar dla każdego z czujników.
7. ~~Buzzer sygnalizujący pomiar.~~
8. Przycisk wymuszający natychmiastowy pomiar.


---

Wymagania funkcjonalne projektu cd.
===

9. ~~Silna dioda RGB sygnalizująca pomierzone wartości za pomocą jasności: czerwień - jasność, niebieski - temperatura, zielony - wilgotność powietrza. Im wyższa wartość pomiaru - tym większa jasność danego koloru.~~
10. ~~Przesyłanie wyników pomiarów do komputera.~~
11. ~~Wyświetlanie wyników pomiarów na komputerze.~~


---

Pomiar poziomu hałasu - mikrofon elektrytowy
===

 ![](img/Electret_condenser_microphone_capsules.jpg)

---
Mikrofon elektrytowy
===

Jest to bardzo tani i popularny typ mikrofonu stosowany właścniwie wszędzie - w telefonach, komputerach, PDA, RTFM itd.

Na wikipedii napisane jest jak działa, z naszego punktu widzenia ważne są tylko dwie rzeczy:

1. Sposób połączenia mikrofonu do zasilania
2. Czy mikrofon może być podłączony bezpośrednio do arduino? 

<!-- footer: @mikrofon @elektryt -->

---

Sposób podłączenia mikrofonu
===

Wykorzystany mikrofon to KPCM-15E (bo jest tani). 

Nota katalogowa: http://mrozo.pl/hs/pliki/noty_katalogowe/f_04668.pdf

Bezpośrednio z noty odczytujemy sposób podłączenia mikrofonu do zasilania.

<!-- footer: @mikrofon @elektryt @podłączenie @nota -->

---

Czy mikrofon można podłączyć bezpośrednio pod arduino?
===

Nie. Znaczy tak, ale nie ma to sensu. 

Mikrofony elektrytowe charakteryzują się małą amplitudą sygnału wyjściowego - oznacza to, że ciężko jest spróbkować i cokolwiek z nim zrobić.

Co to znaczy "mała amplituda"? Na podstawie pomiarów wyznaczono że wynisi ona maks $65 mV$ dla bardzo głośnych dźwięków. Wyniki pomiarów (jeden z szeregowo wpiętym kondensatorem wycinającym składową stałą, drugi bez):

 ![](img/mikrofon-pomiar-amplitudy.png)

<!-- footer: @mikrofon @elektryt @sygnal @parametry-->

---

Nota o przetwornikach analogowo cyfrowych (A/D)
===
Dlaczego sygnał wyjściowy z mikrofonu elektrytowego jest "mały"?
W najogólniejszym przypadku przetwarzanie sygnału o ciągłym czasie i ciągłym zbiorze wartości na wartość cyfrową odbywa się przez porównanie sygnału mierzonego z sygnałem wzorcowym.
![](img/atmega328-adc.png)
Schemat ADC z notu katalogowej atmega 328


<!-- footer: @arduino @adc @nota -->

---


Nota o przetwornikach analogowo cyfrowych (A/D) cd.
===
1. Jako że ADC porównuje sygnał mierzony do sygnału wzorcowego nie ma dla niego różnicy czy sygnał mierzony jest większy o $0.001 V$ czy $1000 V$ od sygnału wzorcowego. No chyba że coś się zjara.
2. Rozdzielczością przetwornika - precyzja z jaką porównujemy sygnały - czyli najmniejsza wartość zmiany wartości sygnału mierzonego powodująca zmianę sygnału wyjściowego. Rozdzielczość jest zależna od sygnału wzorcowego oraz od szerokości w bitach słowa wyjściowego przetwornika.

<!-- note:
1. Czym jest sygnał wzorcowy?
2. Z kąd pochodzi sygnał wzorcowy? - zintegrowany, zewnętrzny, źródło zasilania
-->

<!-- footer: @adc @omowienie -->

---

Czyli co to znaczy że sygnał jest "mały"?
===

Sygnał jest mały, gdy jego rozpiętość jest porównywalna do rodzielczości przetwornika. W idealnej sytuacji sygnał wejściowy ADC przyjmuje poziomy między $0 V$, a napięciem odniesienia (w przypadku arduino $5 V$).

Ponieważ długość słowa wyjściowego ADC w arduino wynosi $N=10 bit$, a napięcie odniesienia wynosi $V_{ref}=5 V$ to rozdzielczość wynosi:

$$
V_{LSB} = V_{ref}/2^{N} \approxeq 4.88 mV
$$
Czyli dla pomierzonego zakresu sygnału wyjściowego mikrofonu
można wykryć maks około 10 różnych poziomów. W praktyce mniej
<!-- note:
1. wspomnieć o zakłuceniach
2. aby wykorzystać pełną rozdzielczość pomiaru trzeba by było zaprojektować cały układ oraz oprogramowanie w taki sposób, 
-->

<!-- footer: @adc @rozdzielczosc @ -->

---

Odpowiedź
===

![](img/noise-detector.jpg)

<!--footer: @wzmacniacz @detektor-wartosci-szczytowej @mikrofon @elektryt -->

---


Wzmacniacz mikrofonowy - znowu to samo
===

Aby zwiększyć precyzję pomiaru hałasu należy sygnał napierw przeskalować co najmniej o rząd wielkości. Do tego zastosowano ten sam układ co w przypadku czujnika jasności.

![](img/schemat-detektora-halasu.png)
Powyższy schemat prezentuje układ wykorzystany do stworzenia detektora poziomu hałasu wraz z zaznaczonymi węzłami.

<!-- note:
1. zobaczcie środek - Między A i C jest ten sam.
2. zmieniono tylko R2 - dzięki temu zwiększono wzmocnienie do 22 razy
-->

<!-- footer: @wzmacniacz @opamp @mikrofon @detektor-wartosci-szczytowej-->

---
Omówienie schematu wzmacniacza mikrofonowego
===

![](img/schemat-detektora-halasu.png)

1. kondensator $C_1$ - usuwa składową stałą z sygnału: przed $C_1$ mamy $x+f(t)$, gdzie $x$ to jakaś wartość stała, a $f(x)$ to właściwy sygnał. W punkcie A mamy tylko $f(x)$
2. Między węzłem $A$ i $B$ jest wzmacniacz operacyjny kopiujący sygnał z węzła $A$ do $B$ celem izolowania mikrofonu od reszty układu. Mikrofon jest bardzo czuły na to, co do niego podłączymy (ma niską impedancję wyjściową).


<!-- note:
1. więcej na schemacie na następnej stronie!
-->

<!-- footer:  @detektor-wartosci-szczytowej @omowienie @opamp @skladowa-stala -->

---
Omówienie schematu wzmacniacza mikrofonowego cd.
===

![](img/schemat-detektora-halasu.png)
3. Wzmacniacz operacyjny między punktami $A$ i $B$ wraz z rezystorami $R_1$ i $R_2$ wzmacnia kopię sygnału $f'(x)$  $(1+R_2/R_1)\approxeq22$  krotnie


<!-- note:

-->

<!-- footer:  @wzmacniacz @detektor-wartosci-szczytowej @omowienie-->

---

Omówienie schematu wzmacniacza mikrofonowego cd.
===

![](img/schemat-detektora-halasu.png)

4. Kondensator $C_2$ gromadzi energię ze wzmocnionego sygnału, zaś $R_3$  powoli rozładowywuje go.
5. Dioda $D_1$ jest tutaj kluczowa dla tego układu. Uniemożliwia ona rozłwadowywanie $C_2$ przez wzmacniacz operacyjny.

<!-- note:
4. Im mniejszy R3, tym szybciej się rozładowywuje. Trzeba to wyważyć, można w symulatorze
5. wspomnieć o tranzystorze
-->

<!-- footer:   @wzmacniacz @detektor-wartosci-szczytowej @omowienie @dioda-->

---
Wynik symulacji
===

![](img/noise_simul.png)
<!-- note:
1. omówić wejście
2. omówić kondensator
3. omówić wzmacniacz powtarzający
4. omówić kondensator i rezystor
5. wspomnieć o diodzie
-->

<!-- footer: @symulacja @wynik @wzmacniacz @detektor-wartosci-szczytowej -->

---

Pomiary układu  $C \to D$
===

![](img/detektor-amplitudy-1kHz.png)

<!-- note:
1. to zrobiłem ja! 
2. niebieski to wyjście z układu - D
3. żółty to wyjście wzmacniacza - C
-->

<!--footer: @pomiar @detektor-wartosci-szczytowej -->

---

Pomiary układu  $C \to D$
===

![](img/detektor-amplitudy-1kHz.png)

<!-- note:
1. to zrobiłem ja! 
2. niebieski to wyjście z układu - D
3. żółty to wyjście wzmacniacza - C
-->

<!--footer: @pomiar @detektor-wartosci-szczytowej -->

---


Pomiary układu - wzmocnienie $A \to D$
===

![](img/detektor-amplitudy-pstrykniecie.png)

<!-- note:
1. sygnał wejściowy - pstryknięcie palcami
2. pstryknąć
3. patrzcie na skalę - różne dla obydwu sygnałów!
4. to jest od wejścia do wyjścia
-->

<!--footer: @pomiar @detektor-wartosci-szczytowej -->

---

Dioda
===

![](img/diode-photo.jpg)

Dioda to element półprzewodnikowy, który pozwala na przepływ prądu tylko w jednym kierunku. Oczywiście o ile nie zostanie przystawione zbyt wysokie napięcie, lub zbyt duży prąd - wtedy się zjara.

Dioda może być potraktowana jako odpowiednik mechanizmu zapadkowego w tylnim kole roweru - jedną stronę przepuszcza energię bez problemu, w drugą zaś - już nie.

<!-- note: 
Używaliśmy różnych rzeczy, ale co to jest??? czas to omówić!
-->

<!-- footer: @dioda @definicja, źródło zdjęcia: wikipedia.org -->

---

Kondensator
===

![](img/Photo-SMDcapacitors.jpg)

Kondensator - działa trochę jak bateria - po podłączeniu do napięcia ładuje się, po podłączeniu do obciążenia - rozładowywuje się. Im wyższe napięcie - tym szybciej się ładuje. Im większa pojemność kondensatora - tym wolniej się napełnia.

Używany jako baterie, części filtrów sygnału, piekielnie ważny, podstawowy element każdego układu elektronicznego.
<!-- note:

-->

<!-- footer: @kondensator @definicja , źródło zdjęcia: wikipedia.org -->

---

Kondensatory - nota o zasilaniu
===

__W każdym układzie elektronicznym__ spotyka się kondensatory wpięte bezpośrednio między szyny zasilania. Z założenia występują w układzie: jeden duży przy wejściu zasilającym i jeden mały przy każdym układzie scalonym. Ich zadaniem jest dostarczanie energii w momencie nagłych wzrostów poboru mocy. Typowo używa się elektrolitu $100 uF$ na wejściu zasilania oraz $1 uF$ przy każdym układzie scalonym.

<!-- note:

-->

<!-- footer:  @kondensator @zasilanie-->

---

Interfejs użytkownika
===

![](img/ui.jpg)


<!-- footer:  @przycisk @led @interfejs @ui-->

---
Interfejs użytkownika
===


Aby się nie rozwijać zbytnio, zastosujemy najprostrzy możliwy interfejs użytkownika - przyciski oraz diody LED podłączone bezpośrednio pod cyfrowe wejścia i wyjścia arduino.

![](img/ui-schemat.png)

Zapalenie diody polega na ustawieniu podłączoneo wyjścia w stan wysoki, a wyłączenie - w stan niski.

Przyciski wymuszają wykorzystanie wbudowanych w arduino rezystorów podciągających do $5 V$. Wciśnięcie przycisku powoduje przejście pinu w stan niski (zwarcie do masy).


<!-- footer: @przycisk @ui @led -->

---

Jak tego używać?
===

Przyciski: http://www.instructables.com/id/Arduino-Button-with-no-resistor/?ALLSTEPS
LED: https://www.arduino.cc/en/Tutorial/Fade



---

Wskaźniki LED
===

![](img/ui-schemat.png)


Należy zwrócić uwagę na inny sposób podłączenia diod niż w przypadku wcześniejszej diody RGB dużej mocy. Jako że zastosowane diody pobierają niewielką moc, mogą być zasilane bezpośrednio z mikrokontrolera. Rezystancja $3.3kOhm$ jest optymalna dla wykorzystanego napięcia zasilania wynoszącego $5V$ Przy takim ustawieniu przez diody przepływa około $1 mA$ przy napięciu około $1.7 V$ co daje około $1.7 mW$ mocy.



<!-- footer: @led @wskaznik @rezystor-->

---

Czy wiesz że... ? - przyciski drgają
===

![](img/glitch.png)

Podczas wciskania przycisk nie generjuje ładnego, idealnego przejścia od stanu wysokiego do niskiego ani na odwórt.Każde wciśnięcie generuje wiele przejść  (patrz zdjęcie).  Zagadnienie odszumiania takiego sygnału nazywa się debouncingiem.

<!-- footer: @przycisk @debouncing, źródło zdjęcia: http://www.emcu.it/STM32/STM32Discovery-Debounce/STM32Discovery-InputWithDebounce_Output_UART_SPI_SysTick.html -->



---

Interfejs użytkownika, a liczba pinów
===

Cztery przyciski i cztery diody - to aż 8 pinów. Arduino ma dostępnych 21 pinów. Czy teraz rozumieciedlaczego niektóre urządzenia mają irytujący sposób obsługi???

Istnieją alternatywne metody podłączania przycisków i led oszczędzające piny wejściowe/wyjściowe takie jak:
1. klawiatury matrycowe
2. klawiatury analogowe (dzielniki napięcia)
3. multipleksacja led (LED CUBE!)
4. klawiatury dotykowe
5. itd.
<!-- footer:  -->

---

Nota o testowaniu
===

1. Warto wyprowadzić wszystkie znaczące sygnały na łatwo dostępne złącze testowe.
2. Telefon jest bardzo przydatnym narzędziem testowym - może generować sygnały testowe - sygnały audio, świetlne itd. Jest doskonałym narzędziem do tworzenia dokumentacji. Może nawet nagrywać eksperymenty. Istnieją nawet aplikacje typu oscyloskop na telefon.
<!-- footer:  @testowanie @zlacze-testowe-->

---


Pułapki
===
* Nie każdy pin arduino ma PWM ;]
Szlifierka przybywa z odsieczą! (poszukajcie na płytce)
* wszystko zajmuje więcej miejsca niż to się wydaje!
* błędny wybór wzmacniacza dla fotorezystora - wykorzystany mcp358 nie jest typu rail to rail, przez co sygnał dochodzi do maks ~$3.7V$ (przed użyciem scalaka należy sprawdzić notę katalogową!) 

<!-- note:

-->

<!-- footer: @pulapki @wnioski -->

---



Przydatne linki
===
1. rezystory -> http://www.digikey.com/-/media/Images/Marketing/Resources/Calculators/resistor-color-chart.jpg?la=en-US&ts=72364a89-2139-476a-8a54-8d78dacd29ff
2. arduino micro pinout -> http://smartduinos.com/wp-content/uploads/2015/09/tumblr_mhwx21ePTX1s5t695o1_12801.png
3. mikrofon -> https://www.piekarz.pl/pl/pdf.php?id=4668
4. dht11 -> http://mikrokontroler.pl/2014/10/06/aplikacja-arduino-czujniki-wilgotnosci-i-temperatury-dht11-i-dht22/
5. dht11, biblioteka -> http://playground.arduino.cc//Main/DHTLib

---

Przydatne linki cd.
===

6. tranzystory -> http://www.onsemi.com/pub_link/Collateral/BC546-D.PDF
7. pnp - 557 - http://www.farnell.com/datasheets/296678.pdf
8. jebane kondensatory : http://www.marvac.com/fun/images/ceramic_cap.jpg

---

Prezentacja
===

<!-- footer: @prezentacja @elektroniczny-bigos -->

---