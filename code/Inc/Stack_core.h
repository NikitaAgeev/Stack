
#ifndef STACK_CORE_STRUCT
#define STACK_CORE_STRUCT
struct stack_t
{
    #ifndef NO_STACK_DUMP_EINFO
    const char* name;
    const char* mather_name;
    const char* mather_file;
    #endif

    #ifndef NO_STACK_ASSERT
    unsigned int hash;
    u_int64_t error;
    u_int64_t warnings;
    #endif

    ssize_t size;
    ssize_t len;
    stack_el_t* mem;
};

typedef struct stack_t* Stack;

#endif

enum STACK_ADR_STATUS
{
    OK = 0,
    NEW_NO_CTOR = 1,
    ADR_POISON = 13,
    ADR_NO_CONSTRUCT = 31,
    DATA_LOST = 404 
};
