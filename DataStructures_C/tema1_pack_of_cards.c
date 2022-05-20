#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define number_of_cards 13
//as ranks (from 1 to 13); 13 * 4 = 52

typedef struct Card
{
    int rank;
    char name;
    int value;
    char symbol;
    struct Card *next;
} Card;
//we implement all the cards with their name and values (points)

typedef struct Pack_of_Cards
{
    int size;
    Card *head;
} Pack;
//we implement a normal pack of 52 cards

typedef struct Queue
{
    Card *front;
    Card *rear;
    long size;
} Queue;

Queue *createQueue(void)
{
    Queue *newQueue = malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    newQueue->size = 0;
    return newQueue;
}

void insert_in_Queue(Queue *q, Card *card)
{

    q->rear->next = card;
    q->rear = card;
    card->next = NULL;
    q->size++;
    if (q->size == 1)
    {
        q->front = card;
    }
}

Card *extract_from_Queue(Queue *q)
{
    Card *card = q->front;
    q->front = q->front->next;
    return card;
}

void freeQueue(Queue *q)
{
    Card *aux;
    while (q->front != NULL)
    {
        aux = q->front->next;
        free(q->front);
        q->front = aux;
        q->size--;
    }
    free(q);
}

//this function creates a card with a specified rank and symbol
Card *create_Card(int rank, char symbol)
{
    Card *card = calloc(1, sizeof(Card));
    card->rank = rank;
    card->symbol = symbol;
    char card_names[14] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5',
                           '4', '3', '2'};

    switch (card->rank)
    {
    case 1:
        card->name = card_names[0];
        card->value = 15;
        break;
    case 2:
        card->name = card_names[1];
        card->value = 14;
        break;
    case 3:
        card->name = card_names[2];
        card->value = 13;
        break;
    case 4:
        card->name = card_names[3];
        card->value = 12;
        break;
    case 5:
        card->name = card_names[4];
        card->value = 10;
        break;
    case 6:
        card->name = card_names[5];
        card->value = 9;
        break;
    case 7:
        card->name = card_names[6];
        card->value = 8;
        break;
    case 8:
        card->name = card_names[7];
        card->value = 7;
        break;
    case 9:
        card->name = card_names[8];
        card->value = 6;
        break;
    case 10:
        card->name = card_names[9];
        card->value = 5;
        break;
    case 11:
        card->name = card_names[10];
        card->value = 4;
        break;
    case 12:
        card->name = card_names[11];
        card->value = 3;
        break;
    case 13:
        card->name = card_names[12];
        card->value = 2;
        break;
    }
    return card;
}

//this function creates the pack from the start of the game
Pack *create_Pack()
{
    Pack *pack = calloc(1, sizeof(Pack));
    pack->size = 52;
    int i = 1, ok = 0;
    Card *card, *newcard;
    //creating first card, that is pack_head
    card = create_Card(i, 's');
    pack->head = card;

    //we create the deck of cards
    for (i = 1; i <= number_of_cards; i++)
    {
        if (ok == 0)
        {
            newcard = create_Card(i, 'h');
            card->next = newcard;
            card = newcard;
            newcard = create_Card(i, 'c');
            card->next = newcard;
            card = newcard;
            newcard = create_Card(i, 'd');
            card->next = newcard;
            card = newcard;
            ok++;
        }
        else
        {
            newcard = create_Card(i, 's');
            card->next = newcard;
            card = newcard;
            newcard = create_Card(i, 'h');
            card->next = newcard;
            card = newcard;
            newcard = create_Card(i, 'c');
            card->next = newcard;
            card = newcard;
            newcard = create_Card(i, 'd');
            card->next = newcard;
            card = newcard;

            if (i == 13)
            {
                card->next == NULL;
            }
        }
    }

    return pack;
}

//this function prints into "out" the current pack , from first card to last
void print_Pack(Pack *pack)
{
    Card *current = pack->head;
    FILE *fptr = fopen("out", "w");
    int i = 0;
    while (current != NULL)
    {
        fprintf(fptr, "%c%c", current->name, current->symbol);
        current = current->next;
        if (i < pack->size - 1)
        {
            fprintf(fptr, " ");
        }
        i++;
    }
    fflush(fptr);
    fclose(fptr);
}

//this functions frees the memory of the whole pack
void free_Pack(Pack *pack)
{
    Card *current = pack->head, *next_card;
    while (current != NULL)
    {
        next_card = current->next;
        free(current);
        current = next_card;
    }
    free(pack);
}

//to shuffle we just use:
//pack->head = amestecare_[and the type of shuffle we want](pack);
Card *amestecare_inversare(Pack *pack)
{
    Card *curr = pack->head, *prev = NULL, *next = NULL;
    //we get pointers to current, previous and next card
    while (curr != NULL)
    {
        next = curr->next; //save next
        curr->next = prev; //reverse the "pointing direction"
        //advance prev and curr
        prev = curr;
        curr = next;
    }
    pack->head = prev;

    return pack->head; //this is the new head
}

//for this specific shuffle we need an "index" array of n integers that holds
//the order for the shuffles
//we get that n and that "index" by reading from "int" and formating the input
Card *amestecare_N_Piles(Pack *pack, int n, int *index)
{
    //index represents an array that stores the order of the sub_sizes
    int i, j, l, k = 0, sub_size = 52 / n;
    //size este nr natural, nu cu virgula sau rest
    Card *first_aux = pack->head, *last_aux = pack->head;
    Card **sub_first = (Card **)calloc(n, sizeof(Card *));
    Card **sub_last = (Card **)calloc(n, sizeof(Card *));
    //we use a 2 dynamic allocated arrays to hold the addresses
    //of the first and last card from every sub_pack that we get
    //one array for the first card address of every sub_pack
    //and one array for the last card address of every sub_pack

    for (j = 0; j < sub_size - 1; j++)
    {
        last_aux = last_aux->next;
    }

    for (i = 0; i < n - 1; i++)
    {
        sub_first[i] = first_aux;
        sub_last[i] = last_aux;
        //here we form that 2 arrays with addreses

        l = 0;
        while (l < sub_size)
        {
            first_aux = first_aux->next;
            last_aux = last_aux->next;
            l++;
        }
    }
    sub_first[n - 1] = first_aux;
    sub_last[n - 1] = last_aux;
    //here we finished to fill that 2 arrays

    pack->head = sub_first[index[0] - 1];
    //we modify the pack->head to start with the first sub_size
    sub_last[index[0] - 1]->next = sub_first[index[1] - 1];
    for (j = 1; j < n; j++)
    {
        sub_last[index[j] - 1]->next = sub_first[index[j + 1] - 1];
    }
    sub_last[index[n - 1] - 1]->next = NULL;
    //in this block of code we build the new pack, with that pointers
    //that we stored in the 2 arrays, by manipulating the card->next's

    //free(sub_first);
    //free(sub_last);

    return pack->head;
}

Card *amestecare_intercalare(Pack *pack)
{
    Card *current1 = pack->head, *current2, *aux1, *aux2;
    current2 = pack->head;
    int i = 0;
    while (i < (pack->size / 2))
    {
        current2 = current2->next;
        i++;
    }
    //now current1 will point to pack->head
    //and current2 will point to the 26th card in the pack
    //if we think that the cards are from 0 to 51

    //here we manipulate some pointers and
    //next's to make the order that we want
    i = 0;
    while (i < ((pack->size / 2) - 1))
    {
        aux1 = current1->next;
        aux2 = current2->next;
        current1->next = current2;
        current2->next = aux1;
        current1 = aux1;
        current2 = aux2;
        i++;
    }
    current1->next = current2;
    //and current1 is last card that will point through "next" to current2
    //and by now current2 is already NULL, so that s the end of the pack

    return pack->head;
}

Card *amestecare_mongean(Pack *pack)
{
    Card *curr1 = pack->head, *aux1, *aux2, *curr2 = pack->head->next;
    int i = 0;

    //this is the first step of the shuffle and requires different rules of
    //manipulatting the pointers and "next"s
    curr1->next = curr2->next;
    aux1 = curr2->next->next;
    curr2->next = curr1;
    curr1 = curr1->next;
    aux2 = aux1->next;
    aux1->next = curr2;
    curr2 = aux1;

    //this part is standard for the rest of the pack
    while (i < 24)
    {
        curr1->next = aux2;
        curr1 = curr1->next;
        aux1 = aux2->next;
        aux2 = aux1->next;
        aux1->next = curr2;
        curr2 = curr1->next;
        i++;
    }
    //and here we got the exception for the last step of the shuffle
    curr1->next = aux2;
    pack->head = aux1;
    //here we made sure that the last card of the pack points to NULL
    //and that we got the right pack->head for the new pack (after shuffle)

    return pack->head;
}

//in this function we simulate
void razboi(Pack *pack)
{
    Pack *deck1 = calloc(1, sizeof(Pack)), *deck2 = calloc(1, sizeof(Pack));
    //deck1 and deck2 represent the 2 packs for the 2 players
    Card *curr = pack->head;
    int i = 0;

    while (curr != NULL)
    {
        if (i < pack->size / 2)
        {
            if (i == 0)
            {
                deck1->head = curr;
            }
            else if (i == (pack->size / 2) - 1)
            {
                deck1->head->next = deck1->head;
                deck1->head = NULL;
            }
            else
            {
                deck1->head->next = deck1->head;
                deck1->head = curr;
            }
        }
        else
        {
            if (i == pack->size / 2)
            {
                deck2->head = curr;
            }
            else if (i == pack->size - 1)
            {
                deck2->head->next = deck2->head;
                deck2->head = NULL;
            }
            else
            {
                deck2->head->next = deck2->head;
                deck2->head = curr;
            }
        }
        i++;
        curr = curr->next;
    }
    deck1->head = amestecare_inversare(deck1);
    deck2->head = amestecare_inversare(deck2);
    //now the 2 decks of cards are build

    print_Pack(deck1);

    //now we free the memory of the 2 decks arrays
    //free(deck1);
    //free(deck2);
}

int main()
{
    Pack *pack = create_Pack();
    FILE *fptr = fopen("in", "r");
    int string_size = 100, i, n = 0;
    char *string = calloc(string_size, sizeof(char));
    char *game_name = calloc(string_size, sizeof(char));
    //we read with fgets line by line and format every line
    fgets(game_name, string_size, fptr);
    game_name[strlen(game_name) - 2] = '\0';

    //now we shuffle the pack
    fgets(string, string_size, fptr);
    string[strlen(string) - 2] = '\0';
    if (strlen(string) == 2)
    {
        n = 10 * (string[0] - '0') + (string[1] - '0');
    }
    else
    {
        n = string[0] - '0';
    }
    //n is the number of shuffles that need to be done

    for (i = 0; i < n; i++)
    {
        fgets(string, string_size, fptr);
        if (string[strlen(string) - 2] == '\n' ||
            string[strlen(string) - 2] == '\r')
        {
            string[strlen(string) - 2] = '\0';
        }
        //we get 4 types of shuffles
        if (strcmp(string, "inversare") == 0)
        {
            pack->head = amestecare_inversare(pack);
        }
        else if (strcmp(string, "intercalare") == 0)
        {
            pack->head = amestecare_intercalare(pack);
        }
        else if (strcmp(string, "mongean") == 0)
        {
            pack->head = amestecare_mongean(pack);
        }
        else
        {
            //CASE WHERE WE GOT npiles
            if (strstr(string, "npiles") != NULL)
            {
                int nr, *index, j;
                string = string + 7;
                if (string[1] == ' ')
                {
                    nr = string[0] - '0';
                    index = calloc(nr, sizeof(int));
                    string = string + 2;
                    for (j = 0; j < nr; j++)
                    {
                        index[j] = string[0] - '0';
                        string = string + 2;
                    }
                }
                else
                {
                    nr = 10 * (string[0] - '0') + (string[1] - '0');
                    index = calloc(nr, sizeof(int));
                    string = string + 3;
                    for (j = 0; j < nr - 1; j++)
                    {
                        if (string[1] == ' ')
                        {
                            index[j] = string[0] - '0';
                            string = string + 2;
                        }
                        else
                        {
                            index[j] = 10 * (string[0] - '0') +
                                (string[1] - '0');
                            string = string + 3;
                        }
                    }
                    if (strlen(string) == 2)
                    {
                        index[nr - 1] = 10 * (string[0] - '0') +
                            (string[1] - '0');
                    }
                    else if (strlen(string) == 1)
                    {
                        index[nr - 1] = string[0] - '0';
                    }
                }
                pack->head = amestecare_N_Piles(pack, nr, index);
            }
        }
    }

    if (strcmp(game_name, "amestecare") == 0)
    {
        //we're done so we put the output into "out"
        print_Pack(pack);
    }
    else if (strcmp(game_name, "razboi") == 0)
    {
        //now we start to simulate "razboi"
    }
    else if (strcmp(game_name, "rollingstone") == 0)
    {
        //now we start to simulate "rollingstone"
    }
    else if (strcmp(game_name, "scarabei") == 0)
    {
        //now we start to simulate "scarabei"
    }

    //we free the Heap memory that we used
    //free(game_name);
    //free(string);
    //free(pack);
    return 0;
}