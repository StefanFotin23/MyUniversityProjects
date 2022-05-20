#include "communication.h"
#include "util_comm.h"

#include <stdio.h>
#include <string.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    send_squanch(18);

    send_squanch(9);

    send_squanch(3);

    send_squanch(11);
    //We use send_squanch to send the encoding of these charachters

    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */
}


void recv_byte_message(void)
{
    uint8_t i, character;
    
    for(i = 1; i <= 5; i++)
    {
        
        character = recv_squanch() + 64;
        //receive a charachter and translate it to ASCII code
        
        fprintf(stdout, "%c", character);
        //print them to standard output

    }

    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
}

void comm_byte(void)
{
    int x, i;
    
    for(i = 1; i <= 10; i++)
    {
        
        x = recv_squanch();
        
        send_squanch(x);

        send_squanch(x);

    }

    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    uint8_t length, shift_2 = 2;
    
    int i;

    char message[11] = "HELLOTHERE";

    length = strlen(message);

    length = length << shift_2;

    
    send_squanch(length);

    for(i = 0; i < 10; i++)
    {

        send_squanch(message[i] - 64);

    }

    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
}


void recv_message(void)
{
    uint8_t length = recv_squanch(), shift_2 = 2, shift_4 = 4, character;

    length = length << shift_2;

    length = length >> shift_4;

    int i;
    
    fprintf(stdout, "%u", length);

    for(i = 0; i < length; i++)
    {

        character = recv_squanch() + 64;

        fprintf(stdout, "%c", character);

    }

    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
}


void comm_message(void)
{
    uint8_t message[255], new_message1[11] = "PICKLERICK";
    
    uint8_t new_message2[11] = "VINDICATORS", n;
    
    uint8_t i, length, shift_2 = 2, shift_4 = 4, character;

    n = recv_squanch(); //n is the length of message we receive

    n = n << shift_2;

    n = n >> shift_4;

    length = strlen(new_message1); //length of the message we send

    length = length << shift_2;

    send_squanch(length);

    //we verify if the last character is 'P'
    if(strchr("PP", message[n-1]))
    {

        //if it is, we send the first message
        for(i = 0; i < 10; i++)
        {

            character = recv_squanch();

            send_squanch(new_message1[i] - 64);

        }

    }
    else
    {
        
        //else, we send the second message
        for(i = 0; i < 10; i++)
        {

            character = recv_squanch();

            send_squanch(new_message2[i] - 64);

        }

    }
    
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
    
    uint8_t k = 0, byte = 0, i, aux = 0, shift_0 = 0;


    for(i = 0; i <= 3; i++)
    {

        aux = aux | c2;//we copy c2 in aux

        aux = aux >> i;

        aux = aux << 7;

        aux = aux >> 7;//we get c2's "i"th bit

        aux = aux << k;

        byte = byte | aux;
        //we put the bit from c2 into the message in position "k"

        k++;

        aux = shift_0;//reset the aux

        aux = aux | c1;

        aux = aux >> i;

        aux = aux << 7;

        aux = aux >> 7;
        
        aux = aux << k;

        byte = byte | aux;

        k++;

    }
    
    
    send_squanch(byte);

}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1, i, aux, mask = 1, nr_1 = 0, nr_2 = 0, k = 0, message[9] = recv_squanch();

    //recv_squanch2 function doesn't exist in current program???

    for(i = 0; i <= 7; i++)
    {
        aux = aux | message[i];
        //we get message's "i"th bit

        if(i % 2 == 0)
        {

            k = i / 2;

            aux = aux << k;

            nr_1 = nr_1 | aux;
            //we put the bit in the first number

        }
        else
        {

            k = i / 2;

            aux = aux << k;

            nr_2 = nr_2 | aux;
            //we put the bit in the second number

        }

        aux = 0;

    }

    res = nr_2;

    res = res << 4;

    res = res | nr_1;

    /* TODO */

    return res;
}
