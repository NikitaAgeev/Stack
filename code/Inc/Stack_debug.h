
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


#define STACK_ASSERT_EXTRA_ARG const char* my_file, const char* my_func, size_t line, FILE* file, \
                               void (*const printer)(stack_el_t elem, FILE* log_file)

#define STACK_ASSERT_E_ARG_IN __FILE__, __FUNCTION__, __LINE__, STACK_LOG_FILE, STACK_ELEM_PRINTER

//predefinition_assertarion_functions----------------------------------------

int stack_assert_f (Stack stack, STACK_ASSERT_EXTRA_ARG);

int stack_verifi_f (Stack stack, STACK_ASSERT_EXTRA_ARG);

//define_assertarion_functions--------------------------------------

#define STACK_ASSERT(stack) stack_assert_f(stack, STACK_ASSERT_E_ARG_IN)

#define STACK_VERIFI(stack) stack_verifi_f(stack, STACK_ASSERT_E_ARG_IN)