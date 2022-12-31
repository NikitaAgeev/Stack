enum STACK_ELEM_STATUS
{
    FREE_MEM_SLOT_E = 0xF5,
    POISON_MEM_SLOT_E = 0xDE,
    FIRST_CANARY_E = 0xFC,
    BACK_CANARY_E = 0xBC
};

enum STACK_ERROR
{
    BAD_FIRST_CANARY        = 1 << 0,
    BAD_BACK_CANARY         = 1 << 1,
    DAMAGE_FREE_SLOT        = 1 << 2,
    DAMAGE_SLOT_TO_POISON   = 1 << 3, 
    BAD_HASH                = 1 << 4,
    BAD_LEN                 = 1 << 5,
    STACK_MEM_IS_POISON     = 1 << 6,
};

enum STACK_WARNINGS
{
    FIRST_CANARY_INSIDE = 1 << 0,
    BACK_CANARY_INSIDE  = 1 << 1,
    FREE_SLOT_INSIDE    = 1 << 2,
    POISON_SLOT_INSIDE  = 1 << 3,
    
};


extern const stack_el_t FREE_MEM_SLOT;
extern const stack_el_t POISON_MEM_SLOT;
extern const stack_el_t FIRST_CANARY;
extern const stack_el_t BACK_CANARY;

void make_cach (Stack stack);

unsigned int find_cach (Stack stack);

int stack_funk_assert_f(Stack stack, const char* parant_func, STACK_ASSERT_EARG);


#define STACK_A_E_A_I_CORE my_file, __FUNCTION__, line, file, printer

#define FUNC_ASERT(STACK) stack_funk_assert_f(STACK, my_func, STACK_A_E_A_I_CORE)
