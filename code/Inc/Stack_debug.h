
//predefinition_dump_function=================================

void stack_dump_f (Stack stack, void (*printer)(stack_el_t elem, FILE* log_fixle), FILE* log_file);

void stack_status_dump_f (Stack stack, FILE* log_file);

u_int64_t stack_error_code (Stack stack);

u_int64_t stack_warning_code (Stack stack);

int stack_errno_f (Stack stack, FILE* log_file);

int stack_warno_f (Stack stack, FILE* log_file);

//define_dump_function----------------------------------------

#define STACK_LOG_OPEN(stack_el_printer)                                                \
static FILE* const STACK_LOG_FILE = fopen("logs", "w");                                  \
static void (*const STACK_ELEM_PRINTER)(stack_el_t elem, FILE* log_file) = stack_el_printer 

#define STACK_LOG_CLOSE() fclose((FILE*)STACK_LOG_FILE)

#define STACK_DUMP(stack) stack_dump_f(stack, STACK_ELEM_PRINTER, (FILE*) STACK_LOG_FILE);\
                          fprintf((FILE*) STACK_LOG_FILE, "\n\n")

#define STACK_STATUS_DUMP(stack) stack_status_dump_f(stack, (FILE*)STACK_LOG_FILE);\
                                 fprintf((FILE*) STACK_LOG_FILE, "\n\n")

#define STACK_ERRNO(satck) stack_errno_f(stack, (FILE*) STACK_LOG_FILE)

#define STACK_WARNO(stack) stack_warno_f(stack, (FILE*) STACK_LOG_FILE)


//assert_ARG_defines========================================================

//debug
#if !defined NO_STACK_ASSERT && !defined NO_STACK_FUNCK_ASSERT
#define STACK_ASSERT_DEBUG_EARG FILE* file, void (*const printer)(stack_el_t elem, FILE* log_file)

#define STACK_ASSERT_DEBUG_EARG_IN STACK_LOG_FILE, STACK_ELEM_PRINTER
#else
#define STACK_ASSERT_DEBUG_EARG    ...

#define STACK_ASSERT_DEBUG_EARG_IN "NO_ARG"
#endif

//dump_info
#ifndef NO_STACK_DUMP_EINFO
#define STACK_ASSERT_DINFO_EARG const char* my_file, const char* my_func, size_t line

#define STACK_ASSERT_DINFO_EARG_IN __FILE__, __FUNCTION__, __LINE__
#else
#define STACK_ASSERT_DINFO_EARG 

#define STACK_ASSERT_DINFO_EARG_IN 
#endif

//extra_args_define

#ifndef NO_STACK_DUMP_EINFO
#define STACK_ASSERT_EARG    STACK_ASSERT_DINFO_EARG, \
                             STACK_ASSERT_DEBUG_EARG

#define STACK_ASSERT_EARG_IN STACK_ASSERT_DINFO_EARG_IN, \
                             STACK_ASSERT_DEBUG_EARG_IN
#else
#define STACK_ASSERT_EARG    STACK_ASSERT_DEBUG_EARG

#define STACK_ASSERT_EARG_IN STACK_ASSERT_DEBUG_EARG_IN
#endif


//asserts====================================================================

//predefinition_assertarion_functions----------------------------------------

int stack_assert_f (Stack stack, STACK_ASSERT_EARG);

int stack_verifi_f (Stack stack, STACK_ASSERT_EARG);

//define_assertarion_functions--------------------------------------

#define STACK_ASSERT(stack) stack_assert_f(stack, STACK_ASSERT_EARG_IN)

#define STACK_VERIFI(stack) stack_verifi_f(stack, STACK_ASSERT_EARG_IN)