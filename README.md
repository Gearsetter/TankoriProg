# ***C Programozás 1 - Tanköri 26/27 - 3. hét***

## **Feladat leírás, motiváció, kontextus**

**Használandó nyelvi elemek:** main, printf, scanf, for, while, if-else, tömbök, függvények

Tegyük fel, hogy távolságot mérünk valamilyen külső szenzorral, egy adott mintavételi idővel. Ezen mérések közt lehetnek kiugró hibák is, ezért az irányító rendszerünk számára előfeldolgozást kell végeznünk, amely a példánkban annyit takar, hogy a legutolsó 4 mérés számtani közepét vesszük, hogy később azt adhassuk tovább.

Írjunk teszt programot az utolsó 4 mért érték folyamatos eltárolására, illetve az ezekből való átlagszámításra!

## **1. Tesztprogram keret megvalósítása**

**Használandó új nyelvi elemek:** .c file, main, \#include, printf, scanf, while
**.c file:** ilyen kiterjesztésű szöveges fileokba implementáljuk a programunkat elsősorban. A build folyamat során, a compiler program minden egyes programunkhoz tartozó .c filet egymástól függetlenül fordít. Több fileban való programíráshoz a header file módszereket is ismernünk kell később.
**main:** nevezetes függvény, ez lesz a program belépési pontja. (Több main függvény esetén, futtatáskor megfelelő target kiválasztása szükséges.) Amennyiben a main függvény, a programunk sikeres végrehajtásra kerül, a visszatérési értékünk 0, tehát a *return 0;* sort rendszeresen a függvény végére illesztjük.
**\#include:** máshol megírt függvényeket, programkomponenseket illeszthetünk vele a .c fileunkba, hogy azokat használni tudjuk benne. Tipikus első gyakorlati példa erre az *\#include <stdio.h>* sor, amellyel a printf-et és a scanf-et is tartalmazó .h header filet illesztjük be.
**print:** előre megírt, gyakran logolásra használatos függvény, a terminal ablakba képes kiírni üzeneteket. Az *stdio.h* fileba includeolásával használhatjuk.
**scanf:** a printf "párja", terminal ablakból tudunk vele általunk bevitt karaktert beolvasni egy változóba eltárolva. A *scanf* visszatérési értéke a beolvasott karakterek száma.
**while:** elöltesztelő ciklus, a *while(){}* blokk kerek zárójelébe a ciklus folytatási feltétele kerül, a kapcsos zárójelbe a ciklus törzse.

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

### 1.3. Extra: loopban várakozás a program végén, manuális kilépéssel

Gyakori igény, hogy a program ne lépjen ki a main függvényből automatikusan, hanem folyamatos futásban maradjon, amíg szándékosan le nem állítjuk. Ha nem a teljes működést szeretnénk ciklikusan ismételni, csak az automatikus befejezést megakadályozni, bevált trükk, ha egy végtelen ciklust illesztünk a main függvénytörzs végére, és valamilyen manuális triggerhez kötjük a kilépési feltételt.

1. Helyezzünk egy *while(1){}* végtelen ciklust a *return 0;* sor elé.
2. A ciklus törzsébe illesszünk egy *if* feltételhez kötött *break* kilépést, ahol a feltétel teljesülése, hogy a terminal ablakból bármilyen értelmezhető karakter érkezzen a felhasználó által.
3. Használjuk az *stdio.h* *scanf* függvényét a megfelelő szintaxis mellett, és használjuk ki, hogy a *scanf* visszatérési értéke a sikeresen beolvasott karakterek száma (tehát nem 0, vlaid beolvasás esetén). A scanf tárolójaként használjunk egy *char terminate* változót!
4. Buildeljünk!
5. Futtassuk a programunkat, hogy lássuk, tényleg csak a terminalba írt karakter triggerünk hatására fejezi be a futást!

## **2. Átlagszámítás megvalósítása és tesztelése**

**Használandó új nyelvi elemek:** tömb, for, ++, +=
**tömb:** egyforma típusú változók sorozata, amelynek fix méretet definiálhatunk előre, akár inicializálhatjuk az elemeit is. Fontos, hogy a tömb elemei fizikailag egymás után, sorrendben helyezkednek el a memóriában, ez teszi lehetővé, hogy indexeléssel hivatkozhassunk rá. Pl. **double a[4] = {0.0, 1.0, 2.0, 3.0};** egy 4 elemű tömb, amely elemeinek az értékét indexeléssel érhetjük el, sorban **a[0], a[1], a[2], a[3]** -> **0.0, 1.0, 2.0, 3.0** formában. Vigyázzunk, hogy a csak a tömb nevével való hivatkozás, **a**, a tömb legelejére mutató memóriacímet jelenti.
**for:** elöltesztelő ciklus, a *for(){}* blokk kerek zárójelébe három tag, a ciklusváltozó inicializálása, a ciklus folytatási feltétele és a ciklusváltozó léptetése kerül, pontosvesszővel elválasztva, a kapcsos zárójelbe pedig a ciklus törzse.
**++**: olyan operátor, ami a mellete lévő operandus értékét 1-gyel növeli.
**+=:** olyan operátor, ami a bal oldali operandust frissíti a jobb oldali operandust hozzáadva (-=, *=, /= esetén kivonva, szorozva, osztva). Pl. **a += b;** ugyanazt jelenti, mint **a = a + b;**.

## 2.1. Utolsó 4 mérési adatot reprezentáló tároló tömb létrehozása

A feladat megvalósításához, az átlagszámításhoz szükség van az utolsó 4 beérkező mérési adat eltárolására. Ezt tömbbel valósíthatjuk meg.

1. Definiáljunk egy double értékeket tároló tömböt *distances* néven, és inicializáljuk is tetszőlegesen. A tömb legyen 4 elemű, ahogyan azt a feladat specifikációja is igényli.
2. Definiáljunk egy integer változót *dist_size* néven, amely a tömb méretét reprezentálja, azaz értéke 4. Erre a ciklikus feldolgozáshoz szükségünk lesz később, és azért hozunk létre külön változót erre előre, mert magából a tömbből visszanyerni a valós méretet sokkal bonyolultabb, mint a tudott fix méretet eltárolni így.

## 2.2. Átlagszámítás ciklus segítségével

Számoljuk ki az átlagot, adjuk össze a *distances* tömb elemeit és osszuk el az összeget a tömb méretével, majd írjuk ki a terminálra a kapott eredményt.

1. Írjunk egy for ciklust, amely során egy *dist_sum* változóba összeadjuk a *distances* tömb elemeit.
2. Képezzünk átlagot a *dist_avg* változóba.
3. Írjuk ki az eredményt a terminalba *printf* függvény segítségével.
4. Buildeljünk!
5. Próbáljuk ki a programot, vajon jó eredményt kapunk-e?

## **3. Beérkező távolságmérések másolása, tárolása**

**Használandó új nyelvi elemek:** %
**%:** osztási maradékot visszaadó operátor. Amíg egész számok esetén a **/** operátor az eredmény egészrészét adja vissza, addig a **%** operátor annak törtrészét. Hasznos, ha pl. ciklikusan szeretnénk léptetni egy indexelő futó változót.

### 3.1. Beérkező távolságmérések szimulációja

Az egyszerűség kedvéért tegyünk csak annyit, hogy egy 4-nél nagyobb elemű tömböt kézzel létrehozunk, ez reprezentálja a külső méréseinket, majd ezt folymatosan átmásoljuk a 4 elem kapacitású *distances* tömbünkbe, úgy, hogy a legvégén a legutoljára érkezett 4 mérés legyen csak eltárolva.

1. Hozzunk létre egy 6 elemű tömböt *measurements* néven, és inicializáljuk tetszőleges értékekkel.
2. Definiáljunk egy *meas_size* változót a *measurements méretét reprezentálandó, a másolási ciklus számára.
3. Másoljuk át sorban a measurements összes elemét egy ciklus segítségével a *distances* tömbbe. A túlindexelést elkerülendő és a régi elemek felülírását elősegítendő, használjuk a **%** operátoros trükköt a *distances* indexeléséhez. ***Figyelem!*** Ha azt mondjuk csak egyszerűen, hogy *distances=measurements;* akkor vlójában fizikailag tettük egyenlővá a kettőt, hisz a *measurements* tömb kezdő címét adtuk a *distance* tömb kezdőértékének. Jelen esetben nem ezt akarjuk.

### 3.2 Folyamatos átlagszámítás minden másolás után

Végezzük el az átlagszámítást minden egyes elem másolása után (mint ahogyan ez egy valós alkalmazásnál történne), tehát ha ciklusban másolunk, akkor az átlagszámításhoz használt programrész, a ciklusával együtt a másoló cikluson belül fog elhelyezkedni.
Amí nem másoltunk át 4 elemet, az áltagszámításnak csak akkor van értelme, ha *distances* tömb elemeit kezdetben 0.0-kként inicializáltuk.

1. A másoló cikluson belül, a másolási lépést követően, helyezzük át a teljes átlagszámító programrészt, a *printf* kiírással együtt.
2. Adjunk új, csupa 0.0 kezdeti értéket a *distances* tömb összes elemének.
3. Buildeljünk!
4. Teszteljük a frissített programot, az átlagszámítás 6 eredményt kell hogy kiírjon sorban összesen a terminal ablakba.

## **4. Függvényekbe szervezés**

**Használandó új nyelvi elemek:** függvény
**függvény:** a neve révén kódmemória címmel rendelkező komplex nyelvi elem, amelynek törzsén belül deklarált nyelvi elemek alapvetően lokálisak, kívülről azok nem elérhetők, és a függvény visszatérésekor (függvény vége) megszűnnek létezni. A függvény a külvilágból a bemeneti listáján (akár több bemenet) keresztül jut információhoz, és a műveletei után új információt a visszatérési értékén keresztül közölhet a külvilággal (ami 1 vagy 0 darab (void típusú) lehet), esetleg legfeljebb globális változókat módosíthat, amelyekhez hozzáfér. A függvény segít átláthatóbbá, strukturáltabbá tenni a programot, redukálhatók vele az ismétlődő kódrészletek, bárhányszor újrafelhasználható, függvények egymásból is hívhatók. A függvény befejezését a törzsén belüli return kulcsszó jelöli, mely után a visszatérési értéket kell illesztenünk (pl. *main* esetén a *return 0;* ilyen volt).
Pl. **int myfunc(int x) { return 2*x; }** függvény visszatérési típusa int, neve myfunc, bemenetként egy x egész számot adunk be (x elnevezés csak egy sablon a függvény belsejének, amikor átadjuk x-ként az értéket, az csak átmásolódik egy, a függvényben lokális x változóba.)
Amikor ezt a függvényt meghívom, pl. **int result = myfunc(3);** módon, akkor a *result* változó értéke 6 lesz.

## 4.1. Átlagszámítás függvénybe szervezése

A main függvényt, az átláthatóság miatt, nem szokás ennyire zsúfoltan tartani, illik letisztultabbá alakítani. Ráadásul a példánk csak egy teszprogram, a lényeg, hogy a számítási feladatokat újra fel akarjuk majd használni később is. Ennek érdekében függvényként szeretnénk használni a műveleteinket.
Talán a legszembetűnőbb programrész, amely révén javíthatjuk a modularitást, az az átlagszámítás rész. Ezt fogjuk elsőként függvénnyé alakítani.

1. Hozzunk létre a *test.c* fileban (a main függvényen kívül, a min fölé) egy *get_dist_avg* függvényt, amelynek bemenetei a *distances* tömb és annak mérete, visszatérési értéke pedig a kiszámolt átlag, tehát típusa double.
2. A függvény törzsébe helyezzük át az átlagszámítás műveleteket, az eredmény printf kiírása nélkül.
3. Az áthelyezett műveletek helyén hívjuk meg az újonnan implementált függvényünket, és a *dist_avg* változónk legyen a függvény eredménye.
4. Buildeljünk, teszteljünk!
5. Figyeljük meg, hogy a tömb átadásakor csak a tömb nevét, tehát kezdőcímét tudjuk átadni, ezért is van szükségünk egyúttal a tömb előre ismert méretét is átadni a függvénynek, mint információ, hogy tudja, meddig kell iterálnia. A függvény definíciójában a **double d[]** jelöli, hogy itt double típusra mutató címet várunk. (Később tanuljuk, hogy ez ugyanaz, mintha **double\* d** jelölést használtunk volna.)
6. Futtassuk a programot debug módban is, és helyezzünk breakpointot a függvénytörzs belsejébe. Figyeljük meg, hogy a függvényen belüli lokális változók megszűnnek, amint a függvényből visszatérünk.

## 4.2 Távolságmérések feldolgozásának függvénybe helyezése

Helyezzük a távolságmérések másolását, feldolgozását is egy függvénybe! Észrevehetjük, hogy ekkor az átlagszámító függvényünk bekerülaz új függvény belsejébe, ami egyáltalán nem baj, nap mint nap fogunk még látni hasonlót, ettől lesz moduláris a programunk.

1. Hozzunk létre egy *process_measurements* függvényt a *test.c* fileban, melynek 4 bemenete lesz: a kívülről kapott *measurements* tömb és annak mérete, valamint a *distances* tömb, amit fel kell tölteni és annak mérete. Mivel az eredmények közlése a függvény belsejében az átlagok printf kiírásával történik, ezért nincs szükségünk visszatérési értékre, így annak típusa *void* (ilyenkor nem vagyunk kötelesek használni a return sort, de a függvénytörzs vége előtt vissza szeretnénk térni a **return;** szintaxis használatos).
2. Fontos, hogy a függvény implementációját az álagszámító függvény és a main közé helyezzük, mert a fordítás szekvenciális, és különben nem ismerné fel a *get_avg* függvényt, mert nem létezett sorban előtte. (Ugyanezért van a main függvény legalul.)
3. Másoljuk át az új függvénytörzsbe az összes műveletvégző részt.
4. Az eddigi műveletvégzés helyén hívjuk meg a *process_measurements* függvényt.
5. Buildeljünk, teszteljük az egymásba ágyazott függvényeinket breakpointokkal.