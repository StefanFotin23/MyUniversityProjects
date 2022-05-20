Tema 2 SD - Fotin Andrei Stefan

	Implementarea temei a fost realizata exclusiv prin functii,
dupa cum a fost conceputa initial.
	Am mai adaugat cateva functii ajutatoare, pentru a usura
lizibilitatea codului, a functiilor, pentru a rezolva mai
simplu taskurile si pentru a avea cod cat mai modular.
	-GET_NODE primeste pointer la tipul TreeNode si pointer la un string (nume)
si returneaza pointer la nodul pe care il cautam
	-CREATE_EMPLOYEE creaza un nod, alocand memorie si atribuind parametrii din
antet (name si manager)
	-REARRANGE_TEAM primeste un vector cu pointer la tipul TreeNode si numarul
de elemente al acestuia si il ordoneaza lexicografic
	-HIRE introduce in tree angajatul nou si il atribuie managerului sau
	-FIRE elimina un angajat din tree si elibereaza memoria sa la final
	-PROMOTE muta echipa angajatului catre managerul sau si apoi, angajatul
urca un nivel si devine "coleg" in echipa cu fostul manager
	-MOVE_EMPLOYEE muta un angajat, fara echipa sa (care ramane atribuita
managerului fostului sau sef), iar acest angajat este mutat sub comanda
noului manager precizat in antetul functiei
	-MOVE_TEAM muta un angajat cu tot cu echipa sa catre noul sau manager
	-FIRE_TEAM elimina din tree si din memorie un angajat, impreuna cu toti
subalternii sai
	-PRINT_TREE preia rolul functiei PREORDER_TRAVERSAL si este apelata in
interiorul functiei PREORDER_TRAVERSAL + PREODER_TRAVERSAL apeleaza PRINT_TREE
si dupa asta, scrie in fisier "\n" la finalul textului pentru a indeplini 
conditiile pentru a lua punctele pe checker
	-DESTROY_TREE este o functie recursiva si este utilizata pentru a elibera
memoria arborelui. (functioneaza perfect, dezaloca toate blocurile de memorie
alocate, erorile nu provin de la aceasta functie;
Se poate verifica daca in main, comentam apelul tuturor functiilor inafara de
test_hire si observam ca DESTROY_TREE elibereaza eficient si corect toata
memoria arborelui construit de functia HIRE)

	
