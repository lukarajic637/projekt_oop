 Trešeta (OOP konzolna igra) – C++

Ovaj projekt je konzolna implementacija kartaške igre Trešeta izrađena u C++ koristeći objektno programiranje.

Projekt podržava:
- 3 igrača (1 čovjek + 2 bota) sa špilom od 36 karata (bez četvorki)
- 4 igrača (1 čovjek + 3 bota) sa špilom od 40 karata
- akuže (3/4 asa, 3/4 duje, 3/4 trice, napolitana)
- bodovanje po pravilima Trešete

Kako pokrenuti projekt:

Opcija 1: Visual Studio (Windows)
1. Otvoriti datoteku treseta.sln
2. Odabrati konfiguraciju Release ili Debug
3. Pokrenuti projekt klikom na Local Windows Debugger

Opcija 2: Pokretanje preko .exe
1. Otvoriti mapu x64/Debug/
2. Pokrenuti treseta.exe

Kontrole u igri :

- Igrač na potezu unosi broj karte (index) iz prikazane ruke
- Igra će označiti koje su karte legalne za bacanje s oznakom "[OK]"
- Nakon svakog runde ili važnog ispisa potrebno je pritisnuti Enter za nastavak

Pravila igre:

Svaka runda je krug bacanja karata gdje svaki igrač baci po jednu kartu.
Rundu dobiva igrač s najjačom kartom u boji koja je prva bačena.

Praćenje boje:
Ako igrač ima kartu boje koja je prva bačena u rundi, mora baciti tu boju.

Jačina karata
Trica > Dvica > As > Kralj > Konj > Fanat > Sedmica > Šestica > Petica > Četvorka

Bodovanje:

- As vrijedi 1 bod
- Trica, Dvica, Kralj, Konj, Fanat vrijede po 1/3 boda
- Zadnja runda donosi +1 bod

Akuže:

- 3 asa / 3 duje / 3 trice = 3 boda
- 4 asa / 4 duje / 4 trice = 4 boda
- Napolitana (As + Dvica + Trica iste boje) = 3 boda

Mogući problemi i rješenja:

Program se ne kompajlira.
Provjeriti da je standard postavljen na C++11 ili C++14.
Project Properties → C/C++ → Language → C++ Language Standard → ISO C++14.


Luka Rajič , Lana Bule
