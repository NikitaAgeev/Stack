
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "Stack_core.h"
#include "Stack_debug.h"

const size_t l_canary = 1002;

const size_t r_canary = 2001;

static unsigned int MurmurHash2 (char* data, size_t n, size_t size);

static unsigned int MurmurHash2 (char* data, size_t n, size_t size)
{
  size_t len = n * size;
  const unsigned int m = 0x5bd1e995;
  const unsigned int seed = 0;
  const int r = 24;

  unsigned int h = seed^len;

  const unsigned char* dt = (const unsigned char *)data;
  unsigned int k = 0;

  while (len >= 4)
  {
      k  = dt[0];
      k |= dt[1] << 8;
      k |= dt[2] << 16;
      k |= dt[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      dt += 4;
      len -= 4;
  }

  switch (len)
  {
    case 3:
      h ^= dt[2] << 16;
    case 2:
      h ^= dt[1] << 8;
    case 1:
      h ^= dt[0];
      h *= m;
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

void make_cach (Stack stack)
{
    stack->hash = MurmurHash2((char*)stack->mem, stack->size, sizeof(stack_el_t));
}

unsigned int find_cach (Stack stack)
{
    return MurmurHash2((char*)stack->mem, stack->size, sizeof(stack_el_t));
}


void stack_mem_dump_f (Stack stack, void (*printer)(stack_el_t elem) = NULL)
{
    
    ssize_t itter = 0;
    ssize_t mem_itter = 0;

    for(itter = -1; itter < stack->size + 1; itter++)
    {
        printf("%04ld | ", itter);

        for(mem_itter = 0; mem_itter < sizeof(stack_el_t); mem_itter++)
        {
            printf("%02hhX ", *(((char*)(stack->mem + itter)) + mem_itter) );
            if((mem_itter + 1) % 4 == 0)
            {
                printf("| ");
            }
        }
        
        if(*(stack->mem + itter) == free_stack_mem_gen()) printf("< FREE_SLOT");
        else if(*(stack->mem + itter) == poison_stack_mem_gen()) printf("< POISON_SLOT");
        else if(*(stack->mem + itter) == first_canary_stack_mem_gen()) printf("< FIRST_CANARY");
        else if(*(stack->mem + itter) == back_canary_stack_mem_gen()) printf("< BACK_CANARY");
        else if(  printer != NULL)
        {
            printf("< ");
            (*printer)(*(stack->mem + itter));
        }

        printf("\n");
    }
}

void stack_dump_status (Stack stack,void (*printer)(stack_el_t elem))
{
    printf("hash:     %08X\n", stack->hash);
    printf("errors:   %08lX\n", stack->error);
    printf("warnings: %08lX\n", stack->warnings);
    printf("size:     %ld\n", stack->size);
    printf("len:      %ld\n", stack->len);
    
    printf("memory dump:\n");
    stack_mem_dump_f(stack, printer);

}

stack_el_t free_stack_mem_gen()
{
    size_t itter = 0;
    stack_el_t ans = 0;

    for(itter = 0; itter < sizeof(stack_el_t); itter++)
    {
        *(((char*)&ans ) + itter) = (char)FREE_MEM_SLOT;
    }
    return  ans;
}

stack_el_t poison_stack_mem_gen()
{
    size_t itter = 0;
    stack_el_t ans = 0;

    for(itter = 0; itter < sizeof(stack_el_t); itter++)
    {
        *(((char*)&ans ) + itter) = (char)POISON_MEM_SLOT;
    }
    return  ans;

}

stack_el_t first_canary_stack_mem_gen()
{
    size_t itter = 0;
    stack_el_t ans = 0;

    for(itter = 0; itter < sizeof(stack_el_t); itter++)
    {
        *(((char*)&ans ) + itter) = (char)FIRST_CANARY;
    }
    return  ans;

}

stack_el_t back_canary_stack_mem_gen()
{
    size_t itter = 0;
    stack_el_t ans = 0;

    for(itter = 0; itter < sizeof(stack_el_t); itter++)
    {
        *(((char*)&ans ) + itter) = (char)BACK_CANARY;
    }
    return  ans;

}