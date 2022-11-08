struct stack_t;

typedef double stack_el_t;

typedef struct stack_t* Stack;

void printer (stack_el_t elem, FILE* log_file);

#define STACK_EXTRA_ARGS const char* my_file, const char* funk_name, size_t line, \
                         FILE* file, void (*const printer)(stack_el_t elem, FILE* log_file)

#define STACK_E_ARGS_IN  __FILE__, __FUNCTION__, __LINE__, (FILE*)STACK_LOG_FILE, STACK_ELEM_PRINTER

//FUNCTION_ACCESS============================================================

void stack_ctor_f (Stack* stack, const char* name, STACK_EXTRA_ARGS);

void stack_dtor_f (Stack* stack, STACK_EXTRA_ARGS);

void stack_push_f (Stack stack, stack_el_t elem, STACK_EXTRA_ARGS);

stack_el_t stack_pop_f (Stack stack, STACK_EXTRA_ARGS);

//DEFINE_ACCESS--------------------------------------------------------------

#define POP(stack) stack_pop_f(stack, STACK_E_ARGS_IN)

#define PUSH(stack, elem) stack_push_f(stack, elem, STACK_E_ARGS_IN)

#define STACK_CTOR(stack) stack_ctor_f(&stack, #stack, STACK_E_ARGS_IN)

#define STACK_DTOR(stack) stack_dtor_f(&stack, STACK_E_ARGS_IN)

//===========================================================================
