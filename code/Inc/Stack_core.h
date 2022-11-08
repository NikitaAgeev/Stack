
#ifndef STACK_CORE_STRUCT
#define STACK_CORE_STRUCT
struct stack_t
{
    const char* name;
    const char* mather_name;
    const char* mather_file;
    unsigned int hash;
    u_int64_t error;
    u_int64_t warnings;
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


