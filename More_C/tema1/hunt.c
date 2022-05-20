#include "hunt.h"
#include <stdio.h>
#include<assert.h>

uint64_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    uint64_t aux = nr;

    aux = aux >> i;

    if(aux % 2 == 1)
    {

        res = 1;

    }
    else
    {

        res = 0;

    }
    
    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    return res;
}

uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF, a = 1;

    if(get_bit(nr, i) == 1)
    {

        res = nr;

    }
    else
    {
        
        res = nr | (a << i);

    }
    

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    return res;
}

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    uint64_t aux1, aux2;

    int k = 0, index, i;

    for(i = 0; i < 63; i++)
    {

        //we use get_bit for map's bits
        if(get_bit(memory, i))
        {

            k++; //if the bit is 1 we increment the k counter

        }
        else
        {
            
            k = 0; //if the bit is 0, we reset the counter k to 0

        }

        if(k == 5)
        {

            index = i; //if we found 5 consecutive 1 bits,
            // we save the last bit position to index variable

            break; //we use "break" for aoptimization purposes

        }
        
    }

    aux1 = 47 - index;

    aux2 = 48;

    //we shift memory 2 times in order to remain just the 16 bits we want
    memory = memory << aux1;

    memory = memory >> aux2;

    //here we put in res variable the value from memory
    //memory now has the 16 bits that we wanted
    res = res & memory;

    /* TODO */

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    uint64_t aux1, aux2;

    int k = 0, i, index;

    for(i = 63; i >= 0; i--)
    {

        //we use get_bit on memory variable
        if(get_bit(memory, i))
        {

            k++; //we count the consecutive bits of 1

        }
        else
        {
            
            k = 0; //if we find a 0 bit, we reset the counter to 0

        }

        if(k == 3)
        {

            index = i; //we save the 3rd consecutive 1 bit position in index
            
            break; //optimization purpose

        }
        

    }

    aux1 = 64 - index;

    aux2 = 48;

    memory = memory << aux1;

    memory = memory >> aux2;

    res = res & memory;
    //we use the same method as in the find_spell function

    /* TODO */

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    res = spell ^ key; //we implement the spell_encrypted formula

    /* TODO */

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1, type = 0, shift_28 = 28;

    uint64_t mask_64bit = 0;

    uint8_t i = 0, k = 0;

    uint16_t value = 0, shift_1 = 1;

    mask_64bit = mask_64bit | enemy;

    for(i = 0; i <= 15; i++)
    {

        if(get_bit(mask_64bit, i) == 1)
        {

            k++;

        }

    }

    if(k % 2 == 1)
    {

        type = 6;

    }
    else
    {
        
        type = 9;

    }
    
    res = res & type;

    res = res << shift_28;

    if(type == 6)
    {

        value = -enemy;

        res = res | value;

    }
    
    if(type == 9)
    {
        
        value = enemy & ( shift_1 - enemy);

        res = res | value;

    }

    /* TODO */

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1, antibodies_high = 0, antibodies_low = 0, shift_16 = 16;

    antibodies_high = cocktail;

    res = res & antibodies_high;

    res = res << shift_16;

    res = res | antibodies_low;

    /* TODO */

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;
    
    uint8_t ok_0 = 1, ok_1 = 1, ok_2 = 1, k = 0, i, index, aux_0 = 0;
    
    uint8_t aux_1 = 1, aux_2 = 2, aux_3 = 3, aux_4 = 4;
    
    uint8_t aux_31 = 31, aux_32 = 32;

    uint64_t aux = 0, mask = 1, shift_1 = 1;

    for(i = 0; i <= 63; i++)
    {
        
        mask = mask << i;

        aux = aux | mask;

        mask = shift_1;

        aux = aux >> i;
        //we save in aux variable the value of the "i"th bit

        if(aux)
        {

            k++; //we count the consecutive bits of 1

            if(i != aux_31 || i != aux_32)
            {

                ok_1 = aux_0;
                //if the 31st or 32nd bit isn't 1, it can't be index 1

            }

        }
        else
        {
            
            ok_2 = aux_0; //if we got a bit of 0, it can't be index 2

            if(i == aux_31 || i == aux_32)
            {

                ok_1 = aux_0; //if the 32st or 32nd bit is 0, it can't be index 1

            }

            if(k > aux_4)
            {

                ok_0 = aux_0; 
                //if we got more than 4 consecutive bits of 1,
                // it can't be index 0

            } 
                
            k = aux_0; //we reset k to 0
            //it counts the number of consecutive bits of 1

        }
        
    }

    if(ok_0)
    {

        index = aux_0;

    }

    if(ok_1)
    {

        index = aux_1;

    }

    if(ok_2)
    {

        index = aux_2;

    }

    if((ok_0 == aux_0) && (ok_1 == aux_0) && (ok_2 == aux_0))
    {

        index = aux_3;

    }
    //here we set the index from the information taken from the ok's variables

    res = res & index;

    /* TODO */ 
    
    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1, k = 0, aux, i, index = 0;

    for(i = 0; i <= 31; i++)
    {

        //we use get_bit
        if(get_bit(map, i) && k == 0)
        {

            aux = i; //save the position of the first bit of 1

            k++;

        }

        if(get_bit(map, i) && k == 1)
        {

            index = i - aux; //the position of the second bit of 1 is "i"
            //index = the distance that we wanted the first place

        }

    }

    res = res & index;

    /* TODO */

    return res;
}
