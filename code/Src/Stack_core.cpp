#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "Stack_core.h"
#include "Stack_debug.h"


static const ssize_t stack_start_size = 2;

static const ssize_t stack_geometri_coef = 2;

static const ssize_t stack_linear_coef = 10;

static const ssize_t stack_change_resize = stack_start_size * pow(stack_geometri_coef, 2);


static void  stack_resize_up_f (Stack stack);

static void stack_resize_down_f (Stack stack);

static void stack_mem_init_f (Stack stack);

static void stack_resize_f (Stack stack);

//Resizing_module=====================================================================

//Functions---------------------------------------------------------------------------

static void stack_resize_up_f (Stack stack)
{   
    
    if( stack->size >= stack_change_resize )
    {
        stack->size += stack_linear_coef;
    }
    else
    {
        stack->size *= stack_geometri_coef;
    }

    stack->mem = ( (stack_el_t*)realloc(stack->mem - 1, ((stack->size + 2) * sizeof(stack_el_t))) ) + 1;    

    ssize_t itter = 0;

    for(itter = stack->len; itter < stack->size; itter++)
    {
        *(stack->mem + itter) = free_stack_mem_gen();
    }
    
    *(stack->mem + stack->size) = back_canary_stack_mem_gen();

    return;
}

static void stack_resize_down_f (Stack stack)
{
    
    ssize_t stack_old_size = stack->size;
    
    if( stack->size > stack_change_resize )
    {
        stack->size -= stack_linear_coef;
    }
    else
    {
        stack->size /= stack_geometri_coef;
    }

    ssize_t itter = 0;

    for(itter = stack->size; itter < stack_old_size; itter++)
    {
        *(stack->mem + itter) = poison_stack_mem_gen();
    }

    stack->mem = (stack_el_t*)realloc(stack->mem - 1 , (stack->size + 2) * sizeof(stack_el_t)) + 1;

    *(stack->mem + stack->size) = back_canary_stack_mem_gen();

    return;
}

static void stack_mem_init_f (Stack stack)
{
    stack->size = stack_start_size;
    stack->len = 0;

    stack->mem = ((stack_el_t*)calloc(stack_start_size + 2, sizeof(stack_el_t))) + 1;

    *(stack->mem + stack->size) = back_canary_stack_mem_gen();
    *(stack->mem - 1) = first_canary_stack_mem_gen();

    return;
}

static void stack_resize_f (Stack stack)
{
    
    if(stack->size == -1)
    {
        stack_mem_init_f(stack);
        return;
    }
    
    if( ( (stack->len * stack_geometri_coef) < stack->size) && (stack->size != stack_start_size) && (stack->size <= stack_change_resize) )
    {
        stack_resize_down_f(stack);
    }
    else if( (stack->len > stack->size) && (stack->size < stack_change_resize) )
    {   
        stack_resize_up_f(stack);
    }
    else if( ( (stack->len + stack_linear_coef) < stack->size) && (stack->size != stack_start_size) && (stack->size > stack_change_resize) )
    {
        stack_resize_down_f(stack);
    }
    else if( (stack->len > stack->size) && (stack->size >= stack_change_resize) )
    {
        stack_resize_up_f(stack);
    }

    return;
}

//Define------------------------------------------------------------------------------

//Constructor_module==================================================================

void stack_no_ctor_f (Stack* stack)
{
    
    *stack = (Stack)NEW_NO_CTOR;
    
    return;
}

void stack_ctor_f (Stack* stack)
{
    
    *stack = (Stack)(calloc(1, sizeof(struct stack_t)));
    
    (*stack)->len = -1;
    (*stack)->size = -1;
    (*stack)->mem = (stack_el_t*)FREE_MEM_SLOT;
    
    stack_resize_f(*stack);

    make_cach(*stack);

    return;
}

void stack_dtor_f (Stack* stack)
{
    
    free((*stack)->mem - 1);
    
    (*stack)->mem = (stack_el_t*)ADR_POISON;
    (*stack)->len = -1;
    (*stack)->size = -1;

    free(*stack);

    *stack = (Stack)ADR_POISON;
    return;
}

//Stack_access_module=================================================================

void stack_push_f (Stack* stack, stack_el_t elem)
{
    

    if((*stack) == (Stack)NEW_NO_CTOR) stack_ctor_f(stack);
    
    (*stack)->len ++;
    stack_resize_f(*stack);
    *((*stack)->mem + (*stack)->len - 1) = elem;
    
    make_cach(*stack);
    
    return;
}

stack_el_t stack_pop_f (Stack* stack)
{ 

    (*stack)->len --;
    stack_el_t elem = *((*stack)->mem + (*stack)->len);
    *((*stack)->mem + (*stack)->len) = FREE_MEM_SLOT;
    stack_resize_f(*stack);

    make_cach(*stack);
    
    return elem;
}

void printer (stack_el_t elem)
{
    printf("%lf", elem);
}

int main ()
{
    Stack st = nullptr;
    stack_no_ctor_f(&st);
    
    
    for(int i = 0; i < 13; i ++)
    {
        stack_push_f(&st, i);
    }

    stack_dump_status(st, printer);

    for(int i = 0; i < 13; i ++)
    {
        stack_pop_f(&st);
    }
    

    stack_dtor_f(&st);
}