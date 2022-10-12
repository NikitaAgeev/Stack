enum STACK_ELEM_STATUS
{
    FREE_MEM_SLOT = 0xFA,
    POISON_MEM_SLOT = 0xDE,
    FIRST_CANARY = 0xFC,
    BACK_CANARY = 0xBC
};

stack_el_t free_stack_mem_gen();
stack_el_t poison_stack_mem_gen();
stack_el_t first_canary_stack_mem_gen();
stack_el_t back_canary_stack_mem_gen();

typedef size_t canary_t;

void st_assert_f (Stack stack);

void make_cach (Stack stack);

unsigned int find_cach (Stack stack);

void stack_mem_dump_f (Stack stack, void (*printer)(stack_el_t elem));

void stack_dump_status (Stack stack, void (*printer)(stack_el_t elem) = NULL);

