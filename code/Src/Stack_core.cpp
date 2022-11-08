#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "Stack_settings.h"
#include "Stack_core.h"
#include "Stack.h"
#include "Stack_debug.h"
#include "Stack_debug_core.h"



static const ssize_t stack_start_size = 10;

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
    
    assert(stack != nullptr);
    assert((stack->mem != (stack_el_t*)NEW_NO_CTOR) && (stack->mem != (stack_el_t*)ADR_POISON));

    assert(stack->error == 0);
    assert(stack->len >= 0);
    assert(stack->size >= 0);

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
        *(stack->mem + itter) = FREE_MEM_SLOT;
    }
    
    *(stack->mem + stack->size) = BACK_CANARY;

    return;
}

static void stack_resize_down_f (Stack stack)
{
    
    assert(stack != nullptr);
    assert((stack->mem != (stack_el_t*)NEW_NO_CTOR) && (stack->mem != (stack_el_t*)ADR_POISON));

    assert(stack->error == 0);
    assert(stack->len >= 0);
    assert(stack->size >= 0);

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
        *(stack->mem + itter) = POISON_MEM_SLOT;
    }

    stack->mem = (stack_el_t*)realloc(stack->mem - 1 , (stack->size + 2) * sizeof(stack_el_t)) + 1;

    *(stack->mem + stack->size) = BACK_CANARY;

    return;
}

static void stack_mem_init_f (Stack stack)
{
    
    assert(stack != nullptr);
    assert(stack->mem != (stack_el_t*)ADR_POISON);

    assert(stack->error == 0);
    
    stack->size = stack_start_size;
    stack->len = 1;

    stack->mem = ((stack_el_t*)calloc(stack_start_size + 2, sizeof(stack_el_t))) + 1;

    *(stack->mem + stack->size) = BACK_CANARY;
    *(stack->mem - 1) = FIRST_CANARY;

    return;
}

static void stack_resize_f (Stack stack)
{
    
    assert(stack != nullptr);
    assert(stack->mem != (stack_el_t*)ADR_POISON);

    assert(stack->error == 0);
    
    if(stack->mem == (stack_el_t*)NEW_NO_CTOR)
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

void stack_ctor_f (Stack* stack, const char* name, STACK_EXTRA_ARGS)
{
    
    *stack = (Stack)(calloc(1, sizeof(struct stack_t)));

    (*stack)->mather_name = funk_name;
    (*stack)->mather_file = my_file;
    (*stack)->name = name;
    (*stack)->len = -1;
    (*stack)->size = -1;
    (*stack)->mem = (stack_el_t*)NEW_NO_CTOR;

    make_cach(*stack);

    FUNC_ASERT(*stack);

    return;
}

void stack_dtor_f (Stack* stack, STACK_EXTRA_ARGS)
{
    
    FUNC_ASERT(*stack);

    free((*stack)->mem - 1);
    
    (*stack)->mem = (stack_el_t*)ADR_POISON;
    (*stack)->len = -1;
    (*stack)->size = -1;

    free(*stack);

    *stack = (Stack)ADR_POISON;
    return;
}

//Stack_access_module=================================================================

void stack_push_f (Stack stack, stack_el_t elem, STACK_EXTRA_ARGS)
{
    
    FUNC_ASERT(stack);

    (stack)->len ++;
    stack_resize_f(stack);
    *((stack)->mem + (stack)->len - 1) = elem;
    
    make_cach(stack);
    
    FUNC_ASERT(stack);

    return;
}

stack_el_t stack_pop_f (Stack stack, STACK_EXTRA_ARGS)
{ 

    FUNC_ASERT(stack);

    if((stack)->len > 0)
    {
        (stack)->len --;
        stack_el_t elem = *((stack)->mem + (stack)->len);
        *((stack)->mem + (stack)->len) = FREE_MEM_SLOT;
        stack_resize_f(stack);

        make_cach(stack);
        
        FUNC_ASERT(stack);

        return elem;
    }
    else
    {

        FUNC_ASERT(stack);

        return 0;
    }
}


