

typedef double stack_el_t;

#ifndef STACK_CORE_STRUCT
#define STACK_CORE_STRUCT
struct stack_t
{
    unsigned int hash;
    size_t error;
    size_t warnings;
    ssize_t size;
    ssize_t len;
    stack_el_t* mem;
};

typedef struct stack_t* Stack;

#endif

enum STACK_ADR_STATUS
{
    NEW_NO_CTOR = 1,
    ADR_POISON = 13
};


void stack_no_ctor_f (Stack* stack);

void stack_dtor_f (Stack* stack);

void stack_push_f (Stack* stack, stack_el_t elem);

stack_el_t stack_pop_f (Stack* stack);
