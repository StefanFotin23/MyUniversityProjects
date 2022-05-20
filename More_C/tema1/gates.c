#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    uint64_t aux = nr;

    aux = aux >> i;
    //we right shift aux "i" bits
    //then we use an if condition to see if the last bit of aux is 0 or 1
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


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1, mask = 1;

    //we use get_bi, then une a mask;
    if(get_bit(nr, i) == 1)
    {

        res = nr & (~(mask << i));
        //if "i" bit is 1 we make it 0 with the mask operation

    }
    else
    {
        
        res = nr | (mask << i);
        //if "i" bit is 0 we make it 1 with the mask operation

    }
    

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF, mask = 1;

    if(get_bit(nr, i) == 1)
    {

        res = nr;
        //if bit "i" is already 1, we just put nr into res variable

    }
    else
    {
        
        res = nr | (mask << i);
        ////if bit "i" is 0, we use the same method that we used at flip_bit
    }
    

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1, a = 1;

    if(get_bit(nr, i) == 0)
    {

        res = nr;
        //if bit "i" is already 0, we just put nr into res variable

    }
    else
    {
        
        res = nr & (~(a << i));
        //if bit "i" is already 1, we use the mask method

    }
    

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    return res;
} 


/* Task 2 - One Gate to Rule Them All */
//here we use the knowledge from "Proiectare Logica" course

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    //we implement the nand gate from the "Proiectare Logica" course
    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    //we use nand gate to implement and gate
    res = nand_gate( nand_gate(a, b), nand_gate(a, b));
    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    //we use nand gate to implement not gate
    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    //we use nand gate to implement or gate
    res = nand_gate(nand_gate(a, a), nand_gate(b, b));

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    //we use nand gate to implement xor gate
    res = nand_gate(nand_gate(a, nand_gate(a, b)), nand_gate(b, nand_gate(a, b)));

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1, sum, carry;

    sum = (or_gate(or_gate((!a && b && !c ), (a && !b && !c)), or_gate((!a && !b && c), (a && b && c))));

    carry = or_gate(or_gate((a && b), (b && c)), (a && c));
    //we use knowledge from "PL" course to implement these functions
    //we use truth table and minimize the functions

    res = 0;

    if(sum)
    {

        res = res | sum;

    }

    res = res << 1;

    if(carry)
    {

        res = res | carry;

    }
    //we put the sum value on bit1 and the carry value on bit0 of res variable

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1, c = 0, sum, shift_1 = 1, i;

    res = 0;

    //c has the carry role;

    for(i = 0; i <= 63; i++)
    {
        sum = full_adder(get_bit(a, i),get_bit(b, i), c);
        //we implement the full_adder function into ripple_carry_adder

        c = clear_bit(sum, 1);

        sum = sum >> shift_1;

        if(sum)
        {

            res = activate_bit(res, i);

        }
        //we use clear_bit and activate_bit functions

    }

    if(c)
    {

        return 0;
        //overflow condition

    }

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    return res;
}
