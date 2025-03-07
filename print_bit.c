#include <unistd.h>


void print_bits(unsigned char octet)
{
    int i;
    int shift;
    int bit;
    
    i = 7;
    while(i >= 0)
    {
        shift = 1 << i;
        bit = octet & shift;
        if(bit == 0)
            write(1, "0", 1);
        else
            write(1, "1", 1);
        i--;
    }
    write(1, "\n", 1);
}

#include <stdio.h>

int main()
{
    printf("-----print_bit-----\n");
    print_bits('l');
}