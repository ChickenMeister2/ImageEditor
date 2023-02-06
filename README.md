# ImageEditor
© 2022 Dima Cosmin Alexandru 314CA
Tema 3
    _____                                              _  _  _                
    \_   \ _ __ ___    __ _   __ _   ___      ___   __| |(_)| |_   ___   _ __ 
     / /\/| '_ ` _ \  / _` | / _` | / _ \    / _ \ / _` || || __| / _ \ | '__|
  /\/ /_  | | | | | || (_| || (_| ||  __/   |  __/| (_| || || |_ | (_) || | 
  \____/  |_| |_| |_| \__,_| \__, | \___|    \___| \__,_||_| \__| \___/ |_|   
                             |___/                                           

 Programul de fata permite incarcarea de fisiere in format PPM sau PGM,
atat ascii cat si binar si efectueaza diferite operatii, in functie de
keywordul introdus de la tastatura si de parametrii urmati de dupa keyword.
 In functia main se afla un while care se reitereaza cu fiecare comanda data.
La inceputul while-ului se citste comanda cu toti parametrii acesteia, iar
textul comenzii se imparte in cuvinte separate care vor fi verificate de
fiecare functie ce editeaza imaginea pentru a se asigura ca sunt valide.

----------------------------------LOAD PHOTO----------------------------------

 Aceasta functie este impartita in 5 functii. Pentru inceput se citeste
headerul pozei, iar in functie de magicwordul de la inceputul fisierului
citirea matricii de valori se continua in alta functie, diferita in functie
de color/alb-negru si ascii/binar.

-----------------------------------SELECT-------------------------------------

 Functia select permite selectarea unui interval 2D de pixeli in functie de
numerele introduse de la tastatura. Functia poate selecta si intreaga imagine
cu comanda "Select ALL". In cazul in care parametrii dati (x1,x2,y1,y2) sunt
incorecti, functia returneaza mesajul corespunzator iar selectia nu va fi
facuta pana nu se introduce din nou keywordul urmat de parametrii adecvati.
 
----------------------------------HISTOGRAM-----------------------------------
 
 Aceasta functie genereaza si afiseaza o historigrama a pozelor alb-negru si
o afiseaza in terminal. Functia primeste ca parametru numarul maxim de
stelute pe care le va afisa si numarul de binuri pe care se va face
histograma
  
-----------------------------------EQUALIZE-----------------------------------
 
 Functia equalize egalizeaza valorile pixelilor din imaginile alb-negru astfel
incat diferenta dintre cea mai intunecata parte a imaginii si cea mai
luminoasa se va micsora.

-------------------------------------CROP-------------------------------------

 Functia crop va efectua taierea imaginii, pastrand doar partea din imagine
care este selectata. Dupa truncherea imaginii toata imaginea va fi selectata
automat.

-------------------------------------APPLY------------------------------------

 Functia APPLY aplica pe intreaga imagine sau pe selectia actuala un filtru de
imagine pe baza unui kernel specific filtrului ales. Functia primeste APPLY
<NUME FILTRU> iar aceasta dispune de filtrele : blur, edge detection, sharpen
si gaussian blur. Pentru fiecare dintre cele 4 filtre se apeleaza o functie
separata ce va extrage din matricea originala de pixeli intr-o alta matrice,
valorile separate ale fiecarui pixel, adica o matrice pentru valorile de rosu,
de verde si albastru. Valorile modificate ale pixelilor sunt salvate intr-o
alta matrice initializata la inceput cu valorea "-1" deoarece kernelul se
aplica doar pe pixelii originali din imagine, nu se efectueaza calcule cu
pixelii modificati, deci nu se poate lucra fara o matrice auxiliara deoarece
pixelii rezultati vor avea valori incorecte. Fiecare valoare este extrasa si
inmultita pe rand cu valorea din kernel si apoi adaugata intr-o matrice de 3x3
careia ulterior i se va face suma elementelor, iar aceasta suma va deveni un
nou pixel in matricea originala.

-------------------------------------SAVE-------------------------------------

 Operatia SAVE va crea un nou fisier ce reprezinta imaginea din memorie ce are
aplicata filtrele pe care utilizatorul le-a introdus. Aceasta poate sa
primeasca si parametru "ascii" dupa numele fisierului iar in functie de acest
parametru se decide daca poza este salvata in format binar sau format ascii.

-------------------------------------EXIT-------------------------------------

 Functia EXIT va dezaloca (in cazul in care au fost alocate) toate resursele
folosite de program si va inchide while-ul, lucru care va inceta rularea
programului. Daca nu a fost incarcata nicio imagine programul va afisa un
mesaj specific
