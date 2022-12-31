#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "Stack.h"

void printer (stack_el_t elem, FILE* log_file)
{
    fprintf(log_file, "%.3lf", elem);
}

STACK_LOG_OPEN(printer);

int main ()
{
    Stack st = nullptr;
    STACK_CTOR(st);

    STACK_ASSERT(st);

    STACK_VERIFI(st);
    
    
    for(int i = 0; i < 45; i ++)
    {
        PUSH(st, i);
    }

    STACK_DUMP(st);

    //STACK_STATUS_DUMP(st);

    for(int i = 0; i < 40; i ++)
    {
        POP(st);
    }
    
    STACK_DUMP(st);

    //STACK_STATUS_DUMP(st);

    STACK_DTOR(st);

    POP(st);

    STACK_LOG_CLOSE();
}