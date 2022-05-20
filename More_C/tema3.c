#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir{
	struct Dir* parent;
	struct Dir* head_children_dirs;
	struct Dir* next;
	char *name;
	struct File* head_children_files;
} Dir;

typedef struct File {
	struct File* next;
	char *name;
	struct Dir* parent;
} File;

//functia verifica daca in directorul "parent" exista directorul cu numele "name"
//returneaza un pointer la acest director daca este gasit
//sau NULL, daca nu gaseste acest director
Dir *search_for_dir(Dir *parent, char *name) {
	if (parent->head_children_dirs == NULL) {
		return NULL;
	}
	Dir *curr_dir = parent->head_children_dirs;
	while (curr_dir != NULL) {
		// cand gasim directorul il returnam
		if (strcmp(curr_dir->name, name) != 0) {
			curr_dir = curr_dir->next;
		} else {
			return curr_dir;
		}
	}
	return NULL;
}


//functia verifica daca in directorul "parent" exista fisierul cu numele "name"
//returneaza un pointer la acest fisier daca este gasit
//sau NULL, daca nu gaseste acest fisier
File *search_for_file(Dir *parent, char *name) {
	if (parent->head_children_files == NULL) {
		return NULL;
	}
	File * curr_file = parent->head_children_files;
	while (curr_file != NULL) {
		// cand gasim fisierul il returnam
		if (strcmp(curr_file->name, name) != 0) {
			curr_file = curr_file->next;
		} else {
			return curr_file;
		}
	}
	return NULL;
}

//eliberam memoria dintr-un fisier
void free_file(File *file) {
	if (file != NULL) {
		free(file->name);
		free_file(file->next);
		free(file);
	}
}

//elibereaza memoria ditr-un director
void free_dir(Dir *dir) {
	if (dir == NULL) {
		return;
	} else {
		free(dir->name);
		free_dir(dir->head_children_dirs);
		free_file(dir->head_children_files);
		free_dir(dir->next);
		free(dir);
	}
}

//functia verifica daca exista deja un fisier cu numele "name" in "parent"
//daca nu exista, il creeaza
//daca exista deja returneaza un mesaj de atentionare
void touch (Dir* parent, char* name) {
	File *curr_file = parent->head_children_files, *prev_file = NULL, *new_file = NULL;

	//verificam daca fisierul deja exista
	if (search_for_file(parent, name) == NULL) {
		//parcurgem lista de fisiere pana la ultimul
		while (curr_file != NULL) {
			prev_file = curr_file;
			curr_file = curr_file->next;
		}

		// alocam memorie pentru fisier
		new_file = malloc(sizeof(File));
		new_file->name = strdup(name);
		new_file->parent = parent;
		
		if (prev_file == NULL) {
			//daca lista de foldere era goala, new devine primul din lista
			parent->head_children_files = new_file;
		} else {
			//altfel ocupa ultima pozitie in lista
			prev_file->next = new_file;
		}
	} else {
		printf("File already exists\n");
	}
}

//functia verifica daca exista in "parent" un director cu numele "name"
//daca nu, il creaza
//daca da, returneaza un mesaj de atentionare
void mkdir (Dir* parent, char* name) {
	Dir *prev_dir = NULL, *new_dir = NULL, *curr_dir = parent->head_children_dirs;

	//verificam daca folderul deja exista
	if (search_for_dir(parent, name) == NULL) {
		//parcurgem lista de foldere pana la ultimul
		while (curr_dir != NULL) {
			prev_dir = curr_dir;
			curr_dir = curr_dir->next;
		}

		// alocam memorie pentru folder
		new_dir = malloc(sizeof(Dir));
		new_dir->name = strdup(name);
		new_dir->parent = parent;

		if (prev_dir == NULL) {
			//daca lista de foldere era goala, new devine primul din lista
			parent->head_children_dirs = new_dir;
		} else {
			//altfel ocupa ultima pozitie in lista
			prev_dir->next = new_dir;
		}
	} else {
		printf("Directory already exists\n");
	}
}

//functia afiseaza toate directoarele si fisierele din directorul curent
void ls (Dir* parent) {
	Dir *curr_dir = parent->head_children_dirs;
	File *curr_file = parent->head_children_files;

	// afisam directoarele primele, apoi fisierele
	while (curr_dir != NULL) {
		printf("%s\n", curr_dir->name);
		curr_dir = curr_dir->next;
	}
	while (curr_file != NULL) {
		printf("%s\n", curr_file->name);
		curr_file = curr_file->next;
	}
	return;
}

//functia cauta in "parent" fisierul cu numele "name"
//daca exista il sterge
//daca nu exista, afiseaza mesaj de atentionare
void rm (Dir* parent, char* name) {
	// verificam daca fisierul exista
	File *curr= parent->head_children_files, *prev = NULL;
	File *file = search_for_file(parent, name);
	if (file == NULL) {
		printf("Could not find the file\n");
	} else {
		//obtinem fisierul precedent celui cautat
		while (curr != file) {
			prev = curr;
			curr = curr->next;
		}
		
		//il scoatem pe fisier din lista de fisiere a lui parent
		if (prev == NULL) {
			parent->head_children_files = file->next;
		} else {
			prev->next = file->next;
		}

		//stergem fileul (eliberam memoria)
		file->next = NULL;
		free_file(file);
	}
}

//functia cauta in "parent" directorul cu numele "name"
//daca exista il sterge
//daca nu exista, afiseaza mesaj de atentionare
void rmdir (Dir* parent, char* name) {
	// verificam daca folderul exista
	Dir *current = parent->head_children_dirs, *prev_dir = NULL;
	Dir *dir = search_for_dir(parent, name);
	if (dir == NULL) {
		printf("Could not find the dir\n");
	} else {
		//obtinem directorul precedent celui cautat
		while (current != dir) {
			prev_dir = current;
			current = current->next;
		}
		
		//il scoatem din lista de directoare a lui parent
		if (prev_dir == NULL) {
			parent->head_children_dirs = dir->next;
		} else {
			prev_dir->next = dir->next;
		}
		
		//stergem directorul (eliberam memoria)
		dir->next = NULL;
		free_dir(dir);
	}
}

//functia schimba directorul curent in cel oferit prin "name"
//sau daca primeste name = "..", urca 1 nivel in ierarhie (la parinte)
void cd(Dir** target, char *name) {
	if (strcmp(name, "..") == 0 && (*target)->parent == NULL) {
		return;
		//cazul banal
	}

	if (strcmp(name, "..") == 0 && (*target)->parent != NULL) {
		//daca name este caz particular ".."
		*target = (*target)->parent;
	} else {
		//cautam directorul in care trebuie sa ne mutam
		if (search_for_dir(*target, name) == NULL){
			//daca nu exista, afisam mesaj de atentionare
			printf("No directories found!\n");
		} else {
			*target = search_for_dir(*target, name);
		}
	}
	return;
}

//functia returneaza calea directorului curent (pana la home)
char *pwd (Dir* target) {
	//daca primim parametru != NULL, trecem la treaba
	if (target == NULL) {
		//cazul in care este apelat pwd(home);
		return strdup("");
	} else {
		//prin apeluri recursive urcam in "tree" de la frunza (target) la parintele lui,
		//pana ajungem la home
		char *string = pwd(target->parent);
		//alocam spatiu pentru directorul curent si adaugam numele
		string = realloc(string,(strlen(target->name) + 1) +  (strlen(string) + 1) );
		//construim un sir de caractere string care se formeaza adaugand directoru cu director,
		//de la radacina pana la "frunza" ierarhiei
		//(frunza fiind "target", deoarece ce este mai "jos" de target nu ne intereseaza)
		sprintf(string, "%s/%s", string, target->name);
		//returnam calea obtinuta
		return string;
	}
}

//functia termina programul
void stop (Dir* target) {
	//eliberam memoria root-ului (home dir)
	free_dir(target);
	exit(0);
}

//functia afiseaza tree-ul cu radacina target si copiii sai
void tree (Dir* target, int level) {
	
}

//functia schimba numele fisierului sau folderului
void mv(Dir* parent, char *oldname, char *newname) {
	if (search_for_dir(parent, oldname) == NULL && search_for_file(parent, oldname) == NULL) {
		//verificam daca fisierul/folderul pe care vrem sa-l redenumim exista
		printf("File/Director not found\n");
		return;
	} else if (search_for_file(parent, newname) != NULL || search_for_dir(parent, newname) != NULL) {
		//verificam daca numele nou nu este deja folosit
		printf("File/Director already exists\n");
		return;
	}
	//cazurile in care nu facem nimic, deci returnam;
	
	File *file = search_for_file(parent, oldname);
	Dir *dir = search_for_dir(parent, oldname);
	
	if (dir != NULL) {
		//cream un folder cu numele nou, iar pe cel vechi il stergem cu totul
		mkdir(parent, newname);
		rmdir(parent, oldname);
	} else if (file != NULL) {
		//cream un fisier cu numele nou, iar pe cel vechi il stergem cu totul
		touch(parent, newname);
		rm(parent, oldname);
	}
}

int main () {
	Dir *home = malloc(sizeof(Dir));
	Dir *dir = home;
	home->name = strdup("home");
	//creeam directorul home (parent dir)
	//home este primul director

	char *line = malloc(MAX_INPUT_LINE_SIZE *  sizeof(char));
	//vom citi inputul fiecarei linii aici
	//(mai intai alocam memoria maxima pentru o linie de input)
	
	char *comanda = NULL, *cuv1 = NULL, *cuv2 = NULL;
	//o linie de comanda poate avea maxim 3 cuvinte
	//(pt mv 3 cuvinte,pentru celelalte comenzi 1 sau 2)

	//citim linie cu linie din standard input (stdin)
	while (fgets(line, MAX_INPUT_LINE_SIZE, stdin)) {
		comanda = strtok(line, " \n");
		cuv1 = strtok(NULL, " \n");
		cuv2 = strtok(NULL, " \n");
		//cu strtok impartim linia de input in cuvinte,
		//pentru a putea "citi" ce comanda a fost introdusa

		//primul cuvant reprezinta comanda,
		//iar apoi celelalte cuvinte (0,1 sau 2 in functie de comanda)
		//reprezinta ceilalti indici ai comenzii

		//(Concis: Unele comenzi au 1 cuvant, altele 2 sau 3)
		if (strcmp(comanda, "stop") == 0) {
			//eliberam toata memoria inainte de a apela functia stop,
			//care inchide programul
			free(line);
			stop(home); 
		} else if (strcmp(comanda, "touch") == 0) {
			touch(dir, cuv1);
		}  else if (strcmp(comanda, "cd") == 0) {
			cd(&dir, cuv1);
		} else if (strcmp(comanda, "rm") == 0) {
			rm(dir, cuv1);
		} else if (strcmp(comanda, "ls") == 0) {
			ls(dir);
		} else if (strcmp(comanda, "mkdir") == 0) {
			mkdir(dir, cuv1);
		} else if (strcmp(comanda, "mv") == 0) {
			//singura comanda cu 3 cuvinte in total
			//(comanda propriuzisa si current_name, new_name)
			mv(dir, cuv1, cuv2);
		} else if (strcmp(comanda, "tree") == 0) {
			tree(dir, 0);
		} else if (strcmp(comanda, "pwd") == 0) {
			char *string_aux = pwd(dir);
			printf("%s\n", string_aux);
			if (string_aux != NULL) {
				free(string_aux);
			}	
		} else if (strcmp(comanda, "rmdir") == 0) {
			rmdir(dir, cuv1);
		}
	}
	return 0;
}
