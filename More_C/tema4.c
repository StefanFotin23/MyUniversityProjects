#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	//we initialize the variables that we need
	int i, j, n = *(int*)input;
	//k is the position of the caracther in the "output" char
	char *out, aux[21];
	if (n < 10) {
		out = (char*)malloc(n * (3 * n + 1));
		//we initialize the variables that we need and
		//we initialize the matrix that we must build
		//we build the matrix
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				sprintf(aux, "%d%d ", n + 1 - j, i);
				//matrix[i][j] = ((n + 1) - j) * 10 + i
				//(rule calculated by me on paper)
				strcat(out, aux);
			}
			if (i < n) {
				sprintf(aux, "\n");
				strcat(out, aux);
			}
		}
	} else if (n >= 10 && n < 100) {
		out = (char*)malloc(n * (5 * n + 1));
		//we initialize the variables that we need and
		//we initialize the matrix that we must build
		//we build the matrix
		for (j = 1; j <= n; j++) {
			for (i = n; i >= 1; i--) {
				sprintf(aux, "%d%d ", i, j);
				//matrix[i][j] = ((n + 10) - j) * 10 + i
				//(rule calculated by me on paper)
				strcat(out, aux);
			}
			if (i < n) {
				sprintf(aux, "\n");
				strcat(out, aux);
			}
		}
	}
	return (void*)out;
}

// Task 2
void *DecodeString(void *input)
{
	int sum = 0;
	char *p, *out = (char*)malloc(21);
	//we assume that the output has maximum of 20 digits
	//we take out the value for (a1, a2, ..., an) from the string
	p = strtok(input, "_");
	while (p) {
		sum = sum + atoi (p);
		//adding the ai value to sump = strtok (NULL, '_');
		p = strtok(NULL, "_");
	}

	sprintf(out, "%d", sum);
	//we write the sum into the output
	
	return (void*)out;
}

//Task 3
void *InvertArray(void *input)
{
	int n = *(int*)input, i;
	//we put the value of the number of vector elements into n
	char *output = (char*)malloc(10 * n), *aux_string = (char*)malloc(10);
	//we assume that the numbers have maximum 9 digits
	//so the output string is big enough too
	if (n % 2 == 0) {
		//the rule is to swap the elements on the positions:
		//"2k+1" and "2k+2", but we just build "output" in that way
		for (i = 1; i <= n - 3; i = i + 2) {
			sprintf(aux_string, "%d ", *((int*)input + i + 1));
			strcat(output, aux_string);
			sprintf(aux_string, "%d ", *((int*)input + i));
			strcat(output, aux_string);
		}
		sprintf(aux_string, "%d ", *((int*)input + n));
		strcat(output, aux_string);
		sprintf(aux_string, "%d", *((int*)input + n - 1));
		strcat(output, aux_string);
	} else {
		//we swap the elements with rule:
		//first with last, 2nd with penultimate and so on
		//but we just build the "right" vector in the "output" char
		for (i = n; i >= 2; i--) {
			sprintf(aux_string, "%d ", *((int*)input + i));
			strcat(output, aux_string);			
		}
		sprintf(aux_string, "%d", *((int*)input + 1));
		strcat(output, aux_string);
	}

	return (void*)output;
}

//Task 4
Player *allocPlayer()
{
	Player *player = malloc(sizeof(Player));
	//we declare a "player" pointer of type "PLayer" structure
	player->name = malloc(sizeof(char) * MAX_LEN_STR_ATR);
	player->color = malloc(sizeof(char) * MAX_LEN_STR_ATR);
	player->hat = malloc(sizeof(char) * MAX_LEN_STR_ATR);
	player->alive = 1;
	//we return the pointer to the structure
	return player;
}

//Task 4
Game *allocGame()
{
	Game *game = malloc(sizeof(Game));
	//we declare a "game" pointer of type "Game" (the structure from "utils.h")
	game->name = malloc(sizeof(char) * MAX_LEN_STR_ATR);
	//we return the pointer to the structure
	return game;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	//we alloc the Player struct
	Player *player = allocPlayer();
	int n, i;
	char *input = malloc(MAX_LEN_STR_ATR), *pointer;
	//we get the text line by line
	
	//we read player name
	fgets(player->name, MAX_LEN_STR_ATR, inputFile);
	n = strlen(player->name);
	player->name[n - 1] = '\0';

	//we read player color
	fgets(player->color, MAX_LEN_STR_ATR, inputFile);
	n = strlen(player->color);
	player->color[n - 1] = '\0';

	//we read player hat
	fgets(player->hat, MAX_LEN_STR_ATR, inputFile);
	n = strlen(player->hat);
	player->hat[n - 1] = '\0';

	fgets(input, MAX_LEN_STR_ATR, inputFile);
	player->numberOfLocations = atoi(input);
	
	//we read the locations
	fgets(input, MAX_LEN_STR_ATR, inputFile);
	player->locations = malloc(player->numberOfLocations * sizeof(Location));
	pointer = strtok(input, " ,()");
	for (i = 0; i < player->numberOfLocations; i++) {
		player->locations[i].x = atoi(pointer);
		pointer = strtok(NULL, " ,()");
		player->locations[i].y = atoi(pointer);
		pointer = strtok(NULL, " ,()");
	}

	//we read the role for everyone
	fgets(input,MAX_LEN_STR_ATR, inputFile);
	input = strtok(input, " \n\r");
	//we use strtok to keep just the word from the input because,
	//I noticed that this string has other characters after the word itself
	//and we want to use strcmp on it
	if (strcmp(input, fromEnumtoString(Rotator)) == 0) {
		player->playerRole = Rotator;
		player->ability = Abilities[Rotator];
	} else if (strcmp(input, fromEnumtoString(Decoder)) == 0) {
		player->playerRole = Decoder;
		player->ability = Abilities[Decoder];
	} else if (strcmp(input, fromEnumtoString(Invertor)) == 0) {
		player->playerRole = Invertor;
		player->ability = Abilities[Invertor]; 
	} else if (strcmp(input, fromEnumtoString(Impostor)) == 0) {
		player->playerRole = Impostor;
		player->ability = Abilities[Impostor];
	}

	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	//we alloc the Game struct
	Game *game = allocGame();
	Player *player = NULL;
	//we get the text line my line
	//total 5 lines, because we consider the "player" lines as one
	char *input = malloc(MAX_LEN_STR_ATR);
	//input is an auxiliary used to get the input from a line and work with it

	//we read game name
	fgets(game->name, MAX_LEN_STR_ATR, inputFile);
	int n = strlen(game->name), i;
	game->name[n - 1] = '\0';

	//we read game killRange
	fgets(input, MAX_LEN_STR_ATR, inputFile);
	game->killRange = atoi(input);

	//we read game numberofCrewmates
	fgets(input, MAX_LEN_STR_ATR, inputFile);
	game->numberOfCrewmates = atoi(input);
	
	//we read "numberofCrewmates" crewmates
	game->crewmates = malloc (game->numberOfCrewmates * sizeof(Player));
	for (i = 0; i < game->numberOfCrewmates; i++) {
		player = ReadPlayer(inputFile);
		game->crewmates[i] = player;
	}

	//we read the impostor
	player = ReadPlayer(inputFile);
	game->impostor = player;

	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	int i;
	//we start writing in outputFile
	player->name[strlen(player->name)] = '\0';
	player->hat[strlen(player->hat)] = '\0';
	player->color[strlen(player->color)] = '\0';
	if (strchr("\n\r\t ", player->name[strlen(player->name) - 1])) {
		player->name[strlen(player->name) - 1] = '\0';
	}
	if (strchr("\n\r\t ", player->color[strlen(player->color) - 1])) {
		player->color[strlen(player->color) - 1] = '\0';
	}
	if (strchr("\n\r\t ", player->hat[strlen(player->hat) - 1])) {
		player->hat[strlen(player->hat) - 1] = '\0';
	}
	fprintf(outputFile, "Player %s with color %s, ", player->name, player->color);
	fprintf(outputFile, "hat %s", player->hat);
	fprintf(outputFile, " and role %s has entered the game", fromEnumtoString(player->playerRole));
	fprintf(outputFile, ".\nPlayer's locations: ");
	for (i = 0; i < player->numberOfLocations; i++) {
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x, player->locations[i].y);
	}
	fprintf(outputFile, "\n");
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	int i;
	
	//we start writing in the outputFile
	if (strchr("\n\r\t ", game->name[strlen(game->name) - 1])) {
		game->name[strlen(game->name) - 1] = '\0';
	}
	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "\tGame options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n\n", game->numberOfCrewmates);
	fprintf(outputFile, "\tCrewmates:\n");
	//we call WritePlayer functiion to write in outputFile every crewmate
	for (i = 0; i < game->numberOfCrewmates; i++) {
		WritePlayer(game->crewmates[i], outputFile);
	}
	//now we write the impostor into the outputFile
	fprintf(outputFile, "\n\tImpostor:\n");
	WritePlayer((game->impostor), outputFile);
	return;
}

//Task 7
void *KillPlayer(void *input)
{
	Game *game = (Game*)input;
	int range[game->numberOfCrewmates], impostor_x, impostor_y, i, min = MAX_LEN_STR_ATR;
	int player_x[game->numberOfCrewmates], player_y[game->numberOfCrewmates];
	int player_index;
	char *output = malloc(MAX_LEN_STR_ATR), *aux = malloc(MAX_LEN_STR_ATR);

	impostor_x = game->impostor->locations
		[game->impostor->indexOfLocation].x; 
	impostor_y = game->impostor->locations
		[game->impostor->indexOfLocation].y;
	//we get the impostors last coordinates

	for (i = 0; i < game->numberOfCrewmates; i++) {
		player_x[i] = game->crewmates[i]->locations
			[game->crewmates[i]->indexOfLocation].x;
		player_y[i] = game->crewmates[i]->locations
			[game->crewmates[i]->indexOfLocation].y;
		//we got the crewmate "i" last coordinates

		//we set the range to 0
		range[i] = 0;

		//we get the abs of (x1 - x2)
		if (impostor_x < player_x[i]) {
			range[i] = range[i] + player_x[i] - impostor_x; 
		} else {
			range[i] = range[i] + impostor_x - player_x[i];
		}
	 
	 	//we get the abs of (y1 - y2)
		if (impostor_y < player_y[i]) {
			range[i] = range[i] + player_y[i] - impostor_y;
		} else {
			range[i] = range[i] + impostor_y - player_y[i];
		}

		//we get the player (alive) that is the closest to impostor
		if (range[i] <= min && game->crewmates[i]->alive == 1) {
			min = range[i];
			player_index = i;
		}
	}

	while (strchr("\n\r\t ", game->impostor->name[strlen(game->impostor->name) - 1])) {
		game->impostor->name[strlen(game->impostor->name) - 1] = '\0';
	}
	while (strchr("\n\r\t ", game->crewmates[player_index]->name[strlen(game->crewmates[player_index]->name) - 1])) {
		game->crewmates[player_index]->name[strlen(game->crewmates[player_index]->name) - 1] = '\0';
	}

	//the case where a player is killed
	if (min < 5 && game->crewmates[player_index]->alive == 1) {
		game->crewmates[player_index]->alive = 0;
		//equivalent to: player died
		
		//creating the output, by concatenating aux to it 2 times
		sprintf(aux, "Impostor %s has just killed crewmate %s",
			game->impostor->name, game->crewmates[player_index]->name);
		strcat(output, aux);
		sprintf(aux, " from distance %d.", min);
		strcat(output, aux);
	}

	//the case where a player haven't got killed
	if (min >= 5) {
		sprintf(output, "Impostor %s couldn't kill anybody.",
			game->impostor->name);
	}
	
	return (void*)output;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	int i, player_index, impostor_index;

	//calculating impostor's next location
	impostor_index = (game->impostor->indexOfLocation + 1) %
		game->impostor->numberOfLocations;
	game->impostor->indexOfLocation = impostor_index;

	for (i = 0; i < game->numberOfCrewmates; i++) {
		//we are editing the name in order to eliminate improper chars from it
		if (strchr(" \n\t\r", game->crewmates[i]->
			name[strlen(game->crewmates[i]->name) - 1]) != NULL) {
				game->crewmates[i]->name
				[strlen(game->crewmates[i]->name) - 1] = '\0';
		}

		//we are doing the same wthing to impostor's name
		if (strchr(" \n\t\r", game->impostor->
			name[strlen(game->impostor->name) - 1]) != NULL) {
				game->impostor->name
				[strlen(game->impostor->name) - 1] = '\0';
		}

		//we are calculating the next location of the crewmate 'i'
		player_index = (game->crewmates[i]->indexOfLocation + 1) %
			game->crewmates[i]->numberOfLocations;
		game->crewmates[i]->indexOfLocation = player_index;

		//now we are printing the output
		if (game->crewmates[i]->alive == 0) {
			//printing output in case crewmate 'i' is dead
			fprintf(outputFile, "Crewmate %s is dead.\n",
				game->crewmates[i]->name);
		} else {
			//printing in the outputFile in case crewmate 'i' is alive
			fprintf(outputFile, "Crewmate %s went to location (%d,%d).",
				game->crewmates[i]->name, game->crewmates[i]->locations
				[game->crewmates[i]->indexOfLocation].x,game->crewmates[i]
				->locations[game->crewmates[i]->indexOfLocation].y);
			fprintf(outputFile, "\nCrewmate %s's output:\n",
				game->crewmates[i]->name);
			fprintf(outputFile, "%s\n",(char*)
				game->crewmates[i]->ability(inputMatrix[i]));
		}
	}
	//printing the output for the impostor 
	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n",
		game->impostor->name, game->impostor->locations
		[game->impostor->indexOfLocation].x, game->impostor->locations
		[game->impostor->indexOfLocation].y);
	fprintf(outputFile, "Impostor %s's output:\n", game->impostor->name);
	fprintf(outputFile, "%s\n",(char*)
		game->impostor->ability(inputMatrix[i]));
		i++;//some problem here inside the ability(parameters)
	return;
}

// Task 9
void FreePlayer(Player *player)
{
	int i;
	free(player->name);
	free(player->hat);
	free(player->color);
	free(player->ability);
	//for (i = 0; i < player->numberOfLocations; i++) {
	//	free(player->locations[i].x);
	//	free(player->locations[i].y);
	//}
	free(player);
	return;
}

// Task 9
void FreeGame(Game *game)
{
	int i;
	free(game->name);
	for (i = 0; i < game->numberOfCrewmates; i++) {
		free(game->crewmates[i]);
	}
	free(game->impostor);
	free(game);
	return;
}