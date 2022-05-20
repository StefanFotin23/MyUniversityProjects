#include <stdio.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#include <stdlib.h>
#include <string.h>

int bonus_verify_1(char word[PRINT_BOARD_SIZE + 1], char auxiliary[3])
{   //verifing that the word is liable for bonus1
    //aux represents the "XX" from input
    if (strstr(word, auxiliary)) {
        return 1;
    } else {
        return 0;
    } 
}

int bonus_verify_2(char word[PRINT_BOARD_SIZE + 1], char auxiliary[3])
{   //verifing that the word is liable for bonus2
    //aux represents the "YY" from input
    int n = strlen(word);
    if (word[n - 2] == auxiliary[0] && word[n - 1] == auxiliary[1]) {
        return 1;
    } else {
        return 0;
    }
}

void set_board(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{
    //we initialize the matrix with '.' character
    int i,j;
    for (i = 0; i < PRINT_BOARD_SIZE; i++){
        for (j = 0; j < PRINT_BOARD_SIZE; j++){
            board[i][j] = '.';
        }
    }
} 

void do_task0(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{   
    set_board(board);
    print_board(board);//the matrix is already initialized so we just print it
}

void do_task1(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{
    set_board(board);
    char line_text[25], aux[4];
    int y, x, d, n, line_length, word_length, i, j, position;
    //y and x are the coordinates of the first letter of the word
    //d's value is 0 or 1 and represents the orientation of the word
    //position reffers to the position in the line_text where the word starts
    fgets(aux, 4, stdin);
    //we get "n" in a char format as variable "aux"
    
    if (aux[1] == '\n') {
        n = (int)(aux[0] - '0');
        //char to int
    } else {
        n = (int)(aux[0] - '0') * 10 + (int)(aux[1] - '0');
        //char to int
    }

    for (i = 0; i < n; i++) {
        fgets(line_text, 25, stdin);
        line_length = strlen(line_text);
        //getting the length of the line we just read
        position = 0;//we reset the position to 0
        
        if (line_text[1] == ' ') {
            //the case where y has 1 figure
            y = (int)(line_text[0] - '0');//char to int
            position = position + 2;
        } else {
            //the case where y has 2 figures
            y = (int)(line_text[0] - '0') * 10 + (int)(line_text[1] - '0');
            //char to int
            position = position + 3;
        }

        if (line_text[position + 1] == ' ') {
            //the case where x has 1 figure
            x = (int)(line_text[position] - '0');//char to int
            position = position + 2;
        } else {
            //the case where x has 2 figures
            x = (int)(line_text[position]- '0') * 10;
            x = x + (int)(line_text[position + 1] - '0');
            //char to int
            position = position + 3;
        }
        
        d = (int)(line_text[position] - '0');
        position = position + 2;
        word_length = line_length - position + 1;

        //now we "write" the word in the "board" horizontally or vertaically
        if (d == 0) {
            for (j = 0; j < word_length; j++) {
                if (line_text[position] != '\n') {
                    board[y][x] = line_text[position];
                    position++;
                    x++;//moving horizontally in the board
                }    
            }
        } else {
            for (j = 0; j < word_length; j++) {
                if (line_text[position] != '\n') {
                    board[y][x] = line_text[position];
                    position++;
                    y++;//mooving vertically in the board
                }
            }
        }
    }
    print_board(board);//printing the board
}

void do_task2()
{
    int v[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5,
     1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char line_text[25], aux[4];
    int n, line_length, word_length, i, j, position;
    int word_points, points1 = 0, points2 = 0;
    //y and x are the coordinates of the first letter of the word
    //d's value is 0 or 1 and represents the orientation of the word
    //position reffers to the position in the line_text where the word starts
    fgets(aux, 4, stdin);
    //we get "n" in a char format as variable "aux"
    
    if (aux[1] == '\n') {
        n = (int)(aux[0] - '0');
        //char to int
    } else {
        n = (int)(aux[0] - '0') * 10 + (int)(aux[1] - '0');
        //char to int
    }
    
    //we dont need to use y, x, d,
    //so we just count their figures, but don't save their values
    for (i = 0; i < n; i++) {
        fgets(line_text, 25, stdin);
        line_length = strlen(line_text);
        //getting the length of the line we just read
        position = 0;
        word_points = 0;
        //we reset the position and word_points to 0
        
        if (line_text[1] == ' ') {
            //the case where y has 1 figure
            position = position + 2;
        } else {
            //the case where y has 2 figures
            position = position + 3;
        }
        
        if (line_text[position + 1] == ' ') {
            //the case where x has 1 figure
            position = position + 2;
        } else {
            //the case where x has 2 figures
            position = position + 3;
        }
        
        position = position + 2;
        word_length = line_length - position + 1;

        //we sum up the points of each character from the word
        for (j = 0; j < word_length; j++) {
            if (line_text[position] != '\n') {
                word_points = word_points + 
                    v[(int)(line_text[position] - 'A')];
                position++;
            }
        }
        
        //we sum up the points from the word to the player that deserves them
        if (i % 2 == 0) {
            points1 = points1 + word_points;
        } else {
            points2 = points2 + word_points;
        }
    }
    printf("Player 1: %d Points\nPlayer 2: %d Points\n", points1, points2);
}

void do_task3()
{
    int v[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5,
     1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char line_text[25], aux[4], XX[4], YY[4], word[16];
    int n, y, x, d, line_length, word_length, i, j, position, pos;
    int word_points, points1 = 0, points2 = 0, total_bonus;
    //y and x are the coordinates of the first letter of the word
    //d's value is 0 or 1 and represents the orientation of the word
    //position reffers to the position in the line_text where the word starts
    //pos is a copy of "position" that we use in order to keep position's value
    fgets(XX, 4, stdin);
    XX[2] = '\0';//we get XX and take out '\n' from the string
    fgets(YY, 4, stdin);
    YY[2] = '\0';//we get YY and take out 'n' from the string
    fgets(aux, 4, stdin);
    //we get "n" in a char format as variable "aux"
    
    if (aux[1] == '\n') {
        n = (int)(aux[0] - '0');
        //char to int
    } else {
        n = (int)(aux[0] - '0') * 10 + (int)(aux[1] - '0');
        //char to int
    }

    for (i = 0; i < n; i++) {
        fgets(line_text, 25, stdin);
        line_length = strlen(line_text);
        //getting the length of the line we just read
        position = 0;
        word_points = 0;
        total_bonus = 1;
        //we reset the position, word_points and bonus to 0
        //we reset total_bonus to 1
        
        if (line_text[1] == ' ') {
            //the case where y has 1 figure
            y = (int)(line_text[0] - '0');//char to int
            position = position + 2;
        } else {
            //the case where y has 2 figures
            y = (int)(line_text[0] - '0') * 10 + (int)(line_text[1] - '0');
            //char to int
            position = position + 3;
        }

        if (line_text[position + 1] == ' ') {
            //the case where x has 1 figure
            x = (int)(line_text[position] - '0');//char to int
            position = position + 2;
        } else {
            //the case where x has 2 figures
            x = (int)(line_text[position]- '0') * 10;
            x = x + (int)(line_text[position + 1] - '0');
            //char to int
            position = position + 3;
        }
        
        d = (int)(line_text[position] - '0');
        position = position + 2;
        word_length = line_length - position;
        pos = position;
        
        for (j = 0; j < word_length; j++){
            //we put the word from the line in the "word" char variable
            word[j] = line_text[pos];
            pos++;
        }
        word[word_length - 1] = '\0';
        //we ensure that the string contains '\0' at its end
        
        //we sum up the points of each character from the word
        //and we count the final bonus that the word will receive
        if (d == 0) {
            for (j = 0; j < word_length; j++) {
                if (line_text[position] != '\n') {
                    word_points = word_points + 
                        v[(int)(line_text[position] - 'A')];
                    if ((bonus_board[y][x] == 1) && 
                        (bonus_verify_1(word, XX) == 1)) {
                            total_bonus = total_bonus * 2;
                    }
                    if ((bonus_board[y][x] == 2) && 
                        (bonus_verify_2(word, YY) == 1)) {
                            total_bonus = total_bonus * 3;
                    }
                    x++;
                    position++;
                }
            }
        } else {
            for (j = 0; j < word_length; j++) {
                if (line_text[position] != '\n') {
                    word_points = word_points + 
                        v[(int)(line_text[position] - 'A')];
                    if (bonus_board[y][x] == 1 && 
                        bonus_verify_1(word, XX) == 1) {
                            total_bonus = total_bonus * 2;
                    }
                    if (bonus_board[y][x] == 2 &&
                        bonus_verify_2(word, YY) == 1) {
                            total_bonus = total_bonus * 3;
                    }
                    y++;
                    position++;
                }
            }    
        }

        //we apply the bonus to the word
        word_points = word_points * total_bonus;

        //we sum up the points from the word to the player that deserves them
        if (i % 2 == 0) {
            points1 = points1 + word_points;
        } else {
            points2 = points2 + word_points;
        }
    }
    printf("Player 1: %d Points\nPlayer 2: %d Points\n", points1, points2);
}

void do_task4(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{
    set_board(board);
    char line_text[25], aux[4], XX[4], YY[4], word[16];
    char used_words[NUM_WORDS][16], first_letter[2];
    int n, y, x, d, line_length, word_length, i, j, position, pos, k = 0, h;
    int ok = 0, l = 0, unused_ok, length, ch_nr, empty_space;
    //"empty_space" is a 0/1 variable used to see if we have enough space
    //on the board where we want to insert a new word
    //"length" is the length of the word that we want to put in the matrix
    //"unused_ok" is a 0/1 variable used to determine if the word was used
    //if it is 1 the word is ready to use, else it was already used
    //"k" is the position in the used_words vector
    //"l" is the position in the words vector
    //"ok" is 0/1 depending if we put a word in the board or not
    //+use it to keep scrolling through words vector till we find the right one
    //"y" and "x" are the coordinates of the first letter of the word
    //"d"'s value is 0 or 1 and represents the orientation of the word
    //"position" reffers to the position in the line_text where the word starts
    //"pos" is a copy of "position" that we use in order to keep it's value
    fgets(XX, 4, stdin);
    XX[2] = '\0';//we get XX and take out '\n' from the string
    fgets(YY, 4, stdin);
    YY[2] = '\0';//we get YY and take out 'n' from the string
    fgets(aux, 4, stdin);
    //we get "n" in a char format as variable "aux"
    
    if (aux[1] == '\n') {
        n = (int)(aux[0] - '0');
        //char to int
    } else {
        n = (int)(aux[0] - '0') * 10 + (int)(aux[1] - '0');
        //char to int
    }

    for (i = 0; i < n; i++) {
        fgets(line_text, 25, stdin);
        line_length = strlen(line_text);
        //getting the length of the line we just read
        position = 0;
        
        if (line_text[1] == ' ') {
            //the case where y has 1 figure
            y = (int)(line_text[0] - '0');//char to int
            position = position + 2;
        } else {
            //the case where y has 2 figures
            y = (int)(line_text[0] - '0') * 10 + (int)(line_text[1] - '0');
            //char to int
            position = position + 3;
        }

        if (line_text[position + 1] == ' ') {
            //the case where x has 1 figure
            x = (int)(line_text[position] - '0');//char to int
            position = position + 2;
        } else {
            //the case where x has 2 figures
            x = (int)(line_text[position]- '0') * 10;
            x = x + (int)(line_text[position + 1] - '0');
            //char to int
            position = position + 3;
        }
        
        d = (int)(line_text[position] - '0');
        position = position + 2;
        word_length = line_length - position - 1;
        pos = position;
        
        for (j = 0; j < word_length; j++){
            //we put the word from the line in the "word" char variable
            word[j] = line_text[pos];
            pos++;
        }
        word[word_length] = '\0';
        //we ensure that the string contains '\0' at its end
        
        //now we "write" the word in the "board" horizontally or vertaically
        if (d == 0) {
            for (j = 0; j < word_length; j++) {
                board[y][x] = word[j];
                x++;//moving horizontally in the board   
            }
        } else {
            for (j = 0; j < word_length; j++) {
                board[y][x] = word[j];
                y++;//mooving vertically in the board
            }
        }

        //we put the word in used_words vector
        //we increment k (position in this vector)
        strcpy(used_words[k], word);
        k++;
    }

    //now we put in a word from the vector from "scrabble.h" in the table
    while (ok == 0 || l <= 100) {
        unused_ok = 1;
        for (i = 0; i < k; i++) {
            if (strcmp(used_words[i],words[l]) == 0) {
                unused_ok = 0;
            } 
        }
        //if the word is unused we continue to the next steps of verification
        if (unused_ok == 1) {
            first_letter[0] = words[l][0];
            length = strlen(words[l]);
            //"length" is length of the word that we want to insert in "board"
            for (i = 0; i < PRINT_BOARD_SIZE; i++) {
                for (j = 0; j < PRINT_BOARD_SIZE; j++) {
                    if (ok == 0) {
                        if (board[i][j] == first_letter[0]) {
                            //we follow the "horizontal" path, which means that
                            //the word can be put horizontal, so we check that
                            empty_space = 1;
                            for(h = j + 1; h <= j + length - 1; h++) {
                                if (board[i][h] != '.') {
                                    empty_space = 0;
                                }
                            }
                            if (PRINT_BOARD_SIZE - j >= length && 
                                empty_space == 1) {
                                //we insert the word horizontally
                                //we save the coordinates in y and x
                                y = i;
                                x = j;
                                ch_nr = 0;
                                //represents the position in the word from the
                                //words vector from "scrabble.h" header
                                for (ch_nr = 0; ch_nr < length; ch_nr++) {
                                    board[y][x] = words[l][ch_nr];
                                    x++;//moving horizontally in the board   
                                }
                                ok = 1;//so we finish the while
                            }
                            //if "ok" is still 0
                            //(the word hasn't been put in the board)
                            //we follow the "horizontal" path, which means that
                            //the word can be put horizontal, so we check that
                            if (ok == 0) {
                                empty_space = 1;
                                for(h = i + 1; h <= i + length - 1; h++) {
                                    if (board[h][j] != '.') {
                                        empty_space = 0;
                                    }
                                }
                                if (PRINT_BOARD_SIZE - i >= length &&
                                    empty_space == 1) {
                                    //we insert the word vertically
                                    //we save the coordinates in y and x
                                    y = i;
                                    x = j;
                                    ch_nr = 0;
                                    //represents the position in the word from the
                                    //words vector from "scrabble.h" header
                                    for (ch_nr = 0; ch_nr < length; ch_nr++) {
                                        board[y][x] = words[l][ch_nr];
                                        y++;//moving vertically in the board   
                                    }
                                    ok = 1;//so we finish the while
                                }
                            }
                        }   
                    }
                }
            }
        } 
        //we go to the next word from the vector from scrabble.h header
        l++;
    }
    print_board(board);
}

void do_task5(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{
    set_board(board);
    char line_text[25], aux[4], XX[4], YY[4], word[16];
    char used_words[NUM_WORDS][16], first_letter[2], word_max[16];
    int n, y, x, d, line_length, word_length, i, j, position, pos, k = 0, h;
    int l = 0, unused_ok, length, ch_nr, empty_space, y_max = -1, x_max = -1;
    int d_max = -1, points_max = 0, points_value, total_bonus;
    int v[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5,
     1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    //"empty_space" is a 0/1 variable used to see if we have enough space
    //on the board where we want to insert a new word
    //"length" is the length of the word that we want to put in the matrix
    //"unused_ok" is a 0/1 variable used to determine if the word was used
    //if it is 1 the word is ready to use, else it was already used
    //"k" is the position in the used_words vector
    //"l" is the position in the words vector
    //"ok" is 0/1 depending if we put a word in the board or not
    //+use it to keep scrolling through words vector till we find the right one
    //"y" and "x" are the coordinates of the first letter of the word
    //"d"'s value is 0 or 1 and represents the orientation of the word
    //"position" reffers to the position in the line_text where the word starts
    //"pos" is a copy of "position" that we use in order to keep it's value
    fgets(XX, 4, stdin);
    XX[2] = '\0';//we get XX and take out '\n' from the string
    fgets(YY, 4, stdin);
    YY[2] = '\0';//we get YY and take out 'n' from the string
    fgets(aux, 4, stdin);
    //we get "n" in a char format as variable "aux"
    
    if (aux[1] == '\n') {
        n = (int)(aux[0] - '0');
        //char to int
    } else {
        n = (int)(aux[0] - '0') * 10 + (int)(aux[1] - '0');
        //char to int
    }

    for (i = 0; i < n; i++) {
        fgets(line_text, 25, stdin);
        line_length = strlen(line_text);
        //getting the length of the line we just read
        position = 0;
        
        if (line_text[1] == ' ') {
            //the case where y has 1 figure
            y = (int)(line_text[0] - '0');//char to int
            position = position + 2;
        } else {
            //the case where y has 2 figures
            y = (int)(line_text[0] - '0') * 10 + (int)(line_text[1] - '0');
            //char to int
            position = position + 3;
        }

        if (line_text[position + 1] == ' ') {
            //the case where x has 1 figure
            x = (int)(line_text[position] - '0');//char to int
            position = position + 2;
        } else {
            //the case where x has 2 figures
            x = (int)(line_text[position]- '0') * 10;
            x = x + (int)(line_text[position + 1] - '0');
            //char to int
            position = position + 3;
        }
        
        d = (int)(line_text[position] - '0');
        position = position + 2;
        word_length = line_length - position - 1;
        pos = position;
        
        for (j = 0; j < word_length; j++){
            //we put the word from the line in the "word" char variable
            word[j] = line_text[pos];
            pos++;
        }
        word[word_length] = '\0';
        //we ensure that the string contains '\0' at its end
        
        //now we "write" the word in the "board" horizontally or vertaically
        if (d == 0) {
            for (j = 0; j < word_length; j++) {
                board[y][x] = word[j];
                x++;//moving horizontally in the board   
            }
        } else {
            for (j = 0; j < word_length; j++) {
                board[y][x] = word[j];
                y++;//mooving vertically in the board
            }
        }

        //we put the word in used_words vector
        //we increment k (position in this vector)
        strcpy(used_words[k], word);
        k++;
    }

    //now we put in a word from the vector from "scrabble.h" in the table
    while (l <= 100) {
        unused_ok = 1;
        for (i = 0; i < k; i++) {
            if (strcmp(used_words[i],words[l]) == 0) {
                unused_ok = 0;
            } 
        }
        //if the word is unused we continue to the next steps of verification
        if (unused_ok == 1) {
            first_letter[0] = words[l][0];
            length = strlen(words[l]);
            //"length" is length of the word that we want to insert in "board"
            for (i = 0; i < PRINT_BOARD_SIZE; i++) {
                for (j = 0; j < PRINT_BOARD_SIZE; j++) {
                    if (board[i][j] == first_letter[0]) {
                        //we follow the "horizontal" path, which means that
                        //the word can be put horizontal, so we check that
                        empty_space = 1;
                        for(h = j + 1; h <= j + length - 1; h++) {
                            if (board[i][h] != '.') {
                                empty_space = 0;
                            }
                        }
                        if (PRINT_BOARD_SIZE - j >= length && 
                            empty_space == 1) {
                            //we pretend to insert the word horizontally
                            //we save the coordinates in y and x
                            y = i;
                            x = j;
                            d = 0;
                            total_bonus = 1;
                            points_value = 0;
                            //represents the position in the word from the
                            //words vector from "scrabble.h" header
                            for (ch_nr = 0; ch_nr < length; ch_nr++) {
                                points_value = points_value +
                                    v[(int)(words[l][ch_nr]) - 'A'];
                                if ((bonus_board[y][x] == 1) && 
                                    (bonus_verify_1(words[l], XX) == 1)) {
                                        total_bonus = total_bonus * 2;
                                }
                                if ((bonus_board[y][x] == 2) && 
                                    (bonus_verify_2(words[l], YY) == 1)) {
                                        total_bonus = total_bonus * 3;
                                }
                                x++;//moving horizontally in the board   
                            }
                            points_value = points_value * total_bonus;
                            //printf("%s ==> %dpuncte\n", words[l], points_value);
                            //if we got a new high score of points, we remember the word
                            if (points_value > points_max) {
                                x_max = j;
                                y_max = i;
                                d_max = d;
                                points_max = points_value;
                                strcpy(word_max, words[l]);
                            }
                        }

                        //we follow the "horizontal" path, which means that
                        //the word can be put horizontal, so we check that
                        empty_space = 1;
                        for(h = i + 1; h <= i + length - 1; h++) {
                            if (board[h][j] != '.') {
                                empty_space = 0;
                            }
                        }
                        if (PRINT_BOARD_SIZE - i >= length &&
                        empty_space == 1) {
                            //we insert the word vertically
                            //we save the coordinates in y and x
                            y = i;
                            x = j;
                            ch_nr = 0;
                            d = 1;
                            total_bonus = 1;
                            points_value = 0;
                            //represents the position in the word from the
                            //words vector from "scrabble.h" header
                            for (ch_nr = 0; ch_nr < length; ch_nr++) {
                                points_value = points_value + v[(int)(words[l][ch_nr]) - 'A'];
                                if ((bonus_board[y][x] == 1) && 
                                    (bonus_verify_1(words[l], XX) == 1)) {
                                        total_bonus = total_bonus * 2;
                                }
                                if ((bonus_board[y][x] == 2) && 
                                    (bonus_verify_2(words[l], YY) == 1)) {
                                        total_bonus = total_bonus * 3;
                                }
                                y++;//moving vertically in the board   
                            }
                            points_value = points_value * total_bonus;
                            //if we got a new high score of points, we remember the word
                            if (points_value > points_max) {
                                x_max = j;
                                y_max = i;
                                d_max = d;
                                points_max = points_value;
                                strcpy(word_max, words[l]);
                            }
                        }
                    }   
                }
            }
        }
        //we go to the next word from the vector from scrabble.h header
        l++;
    }
    //printf("SOLUTIE: %d %d %d %d %s %d\n", y_max, x_max, d_max, points_max, word_max, length);
    //we put the word with most points in the board
    length = strlen (word_max);
    if (d_max == 0) {
        for (i = 0; i < length; i++) {
            board[y_max][x_max] = word_max[i];
            x_max++;
        }
    } else {
        for (i = 0; i < length; i++) {
            board[y_max][x_max] = word_max[i];
            y_max++;
        }
    }
    print_board(board);
}

int main()
{
    char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE], task_number[3]; 

    fgets(task_number, 3, stdin);//getting the task number
    if (task_number[0] == '0') {
        do_task0(board);//calling the task 0 function
    } else if (task_number[0] == '1') {
        do_task1(board);//calling the task 1 function
    } else if (task_number[0] == '2') {
        do_task2(board);//callingthe task 2 function
    } else if (task_number[0] == '3') {
        do_task3(board);//calling the task 3 function
    } else if (task_number[0] == '4') {
        do_task4(board);//calling the task 4 function
    } else if (task_number[0] == '5') {
        do_task5(board);//calling the task 5 function
    }
    return 0;
}