Tema1 - 311CD - Fotin Andrei-Stefan

1) Implementarea pachetului de carti in memorie
	Am folosit 2 structuri de tip: Pack si Card. Card reprezinta o carte de joc
si are campurile: name, symbol, value, rank si *next. Folosind pointerul next,
acesta pointeaza la urmatoarea carte din pachet.
	Am folosit o functie create_Pack care returneaza pointer la "head"-ul
pachetului nou creat, dupa regula data initial.
	Am adaugat si o functie de afisare a pachetului, mai exact scrierea sa
in "out", cat si o functie de eliberare a memoriei acestuia, apelata inainte de
finalizarea programului, in main.

2) Cele 4 functii de shuffle
	Toate functiile primesc pachetul si returneaza "head"-ul pachetului
dupa amestecare
	Singura exceptie este "npiles" unde oferim in antet 2 variabile,
una de tip int: n si una de tip integer array: index, unde stocam ordinea
in care trebuie amestecate cele n sub-pachete specifice cerintei acestui tip
de amestecare.

3)Formatarea inputului se face folsing fgets pentru a citi linie cu linie
din fisierul int si apoi prelucram datele obtinute si le memoram pe cele
utile in diferite variabile. *Folosim memoria de pe Heap, nu din stiva, pe
care apoi o eliberam cu apeluri are functiei: free();
	*Toate datele de iesire vor fi scrise in fisierul "out".
	*Utilizam lucrul cu siruri de caractere si pointeri pentru a
formata inputul si datele importante citite si apoi eventual memorate.

4)Avem cate o functie (care returneaza void) pentru fiecare joc, pe care
le apelam daca ne aflam in cazul in care inputul ne indica sa rulam
respectivul joc.
	*Consideram si "amestecare" un caz special, in care nu avem joc,
ci doar efectuam amestecarea pachetului si la final afisam pachetul rezultat.

