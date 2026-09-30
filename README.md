# ***C Programozás 1 - Tanköri 26/27 - 3. hét***

## **Feladat leírás, motiváció, kontextus**

**Használandó nyelvi elemek:** main, printf, scanf, for, while, if-else, tömbök, függvények

Tegyük fel, hogy távolságot mérünk valamilyen külső szenzorral, egy adott mintavételi idővel. Ezen mérések közt lehetnek kiugró hibák is, ezért az irányító rendszerünk számára előfeldolgozást kell végeznünk, amely a példánkban annyit takar, hogy a legutolsó 4 mérés számtani közepét vesszük, hogy később azt adhassuk tovább.

Írjunk teszt programot az utolsó 4 mért érték folyamatos eltárolására, illetve az ezekből való átlagszámításra!

## **1. Tesztprogram keret megvalósítása**

**Használandó új nyelvi elemek:** .c file, main, \#include, printf, scanf
**.c file:** ilyen kiterjesztésű szöveges fileokba implementáljuk a programunkat elsősorban. A build folyamat során, a compiler program minden egyes programunkhoz tartozó .c filet egymástól függetlenül fordít. Több fileban való programíráshoz a header file módszereket is ismernünk kell később.
**main:** nevezetes függvény, ez lesz a program belépési pontja. (Több main függvény esetén, futtatáskor megfelelő target kiválasztása szükséges.) Amennyiben a main függvény, a programunk sikeres végrehajtásra kerül, a visszatérési értékünk 0, tehát a *return 0;* sort rendszeresen a függvény végére illesztjük.
**\#include:** máshol megírt függvényeket, programkomponenseket illeszthetünk vele a .c fileunkba, hogy azokat használni tudjuk benne. Tipikus első gyakorlati példa erre az *\#include <stdio.h>* sor, amellyel a printf-et és a scanf-et is tartalmazó .h header filet illesztjük be.
**print:** előre megírt, gyakran logolásra használatos függvény, a terminal ablakba képes kiírni üzeneteket. Az *stdio.h* fileba includeolásával használhatjuk.

### 1.1. main függvény létrehozása + Hello World!

1. Hozzunk létre egy *src* mappát, és benne a main függvényt tartalmazó *test.c* filet. Írjunk egy üres main függvényt, *return 0;* sorral.
2. Includeoljuk az *stdio.h*-t, hogy használhassuk a *printf* függvényt
3. Írjuk ki a terminal ablakba, *printf* segítségével, hogy "Hello World!"! Ehhez elég a *printf* első konstans sztringet váró paraméterét használnunk placeholderek nélkül.

### 1.2. build, run

Amennyiben VS Code a fejlesztőkörnyezet, és most kezdtük írni a programunkta, nem árt átnézni a build konfigurációkat. A jelen példában VS Code-ot és gcc fordítót használunk.

1. Ha még nem állítottuk be a build konfigurációt megvalósító .vscode/tasks.json filet, VS Code-ban nyomjunk F1-et, és keressük meg a *Configure Default Build Task* lehetőséget. Ez rögtön feldobja, hogy válasszunk sablont, mit generáljon nekünk, a péládban a gcc-sre esett a választás.
2. Keressük meg a root mappában a .vscode/tasks.json filet és ellenőrizzük, a gcc parancs argumentumait!
3. A biztos, zavartalan működéshez, a példa során minden egyes .c file kézzel hozzáadásra kerül argumentumként, az első feladat megoldásához a *"\$\{file\}",* sor lett kicserélve *"\${workspaceFolder}/src/test.c",*-re.
4. Menjünk vissza a filekezelő Explorer tabre, álljunk a *test.c* filera és nyomjunk Ctrl+Shift+B kombinációt, amely elindítja a build taskot, ha minden jól ment, a terminal ablakban megjelenik a *Build finished successfully* felirat, és létrejön a *test.exe* file.
5. Futtassuk a Hello World programunkat F5-tel debug módban vagy Ctrl+F5-tel anélkül. (Ha nem megy, ellenőrizzük, hogy a test.c fileon állunk-e, illetve hogy telepítve lett-e biztosan a debugger, pl. gdb)

### 1.3 Extra: loopban várakozás a program végén, manuális kilépéssel

Gyakori igény, hogy a program ne lépjen ki a main függvényből automatikusan, hanem folyamatos futásban maradjon, amíg szándékosan le nem állítjuk. Ha nem a teljes működést szeretnénk ciklikusan ismételni, csak az automatikus befejezést megakadályozni, bevált trükk, ha egy végtelen ciklust illesztünk a main függvénytörzs végére, és valamilyen manuális triggerhez kötjük a kilépési feltételt.

1. Helyezzünk egy *while(1){}* végtelen ciklust a *return 0;* sor elé.
2. A ciklus törzsébe illesszünk egy *if* feltételhez kötött *break* kilépést, ahol a feltétel teljesülése, hogy a terminal ablakból bármilyen értelmezhető karakter érkezzen a felhasználó által.
3. Használjuk az *stdio.h* *scanf* függvényét a megfelelő szintaxis mellett, és használjuk ki, hogy a *scanf* visszatérési értéke a sikeresen beolvasott karakterek száma (tehát nem 0, vlaid beolvasás esetén). A scanf tárolójaként használjunk egy *char terminate* változót!
4. Buildeljünk!
5. Futtassuk a programunkat, hogy lássuk, tényleg csak a terminalba írt karakter triggerünk hatására fejezi be a futást!