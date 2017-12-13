const int varnamesize = 255, NUM_ofvar = 1000;

struct Variables
{
    char** name = new char*[NUM_ofvar];
    int number = 0;
};

const char* file_name = "program1.txt";

const char* Expression = nullptr;
int Index = 0;
Variables Func;

#define SPACE                  while (isspace(Expression[Index])) Index++;

#define  NUMERIC(number)        MakeNode (NUM     , number)
#define    VARIA(number)        MakeNode (VAR     , number)
#define    FUNCT(number)        MakeNode (FUNCTION, number)

#define ISNUM(node) node ->key == NUM
#define ISVAR(node) node ->key == VAR

#define      PLUS(left, right) MakeNode (OPERATOR, ADD,   left, right)
#define     MINUS(left, right) MakeNode (OPERATOR, SUB,   left, right)
#define    MULTIP(left, right) MakeNode (OPERATOR, MUL,   left, right)
#define     DIVIS(left, right) MakeNode (OPERATOR, DIV,   left, right)
#define      ASSN(left, right) MakeNode (OPERATOR, ASN,   left, right)
#define    OPERAT(left, right) MakeNode (OPERATOR, OPER,  left, right)
#define      MORE(left, right) MakeNode (OPERATOR, JA,    left, right)
#define      LESS(left, right) MakeNode (OPERATOR, JB,    left, right)
#define     EMORE(left, right) MakeNode (OPERATOR, JAE,   left, right)
#define     ELESS(left, right) MakeNode (OPERATOR, JBE,   left, right)
#define     EQUAL(left, right) MakeNode (OPERATOR, JE,    left, right)
#define    NEQUAL(left, right) MakeNode (OPERATOR, JNE,   left, right)
#define    CONDIT(left, right) MakeNode (OPERATOR, IF,    left, right)
#define     OTHER(left, right) MakeNode (OPERATOR, ELSE,  left, right)
#define      LOOP(left, right) MakeNode (OPERATOR, WHILE, left, right)
#define   PARAMET(left, right) MakeNode (OPERATOR, PARAM, left, right)
#define     SINUS(current)     MakeNode (OPERATOR, SIN,   current, nullptr)
#define   COSINUS(current)     MakeNode (OPERATOR, COS,   current, nullptr)
#define   RADICAL(current)     MakeNode (OPERATOR, SQRT,  current, nullptr)
#define     INPUT(current)     MakeNode (OPERATOR, SCAN,  current, nullptr)
#define    OUTPUT(current)     MakeNode (OPERATOR, PRINT, current, nullptr)

#define COMPCMD(name, command, size) {\
        Index += size;\
\
        SPACE\
\
        int indcop = Index;\
\
        Exp_type value_ = GetE (var);\
\
        SPACE\
\
        if (indcop == Index)\
        {\
            printf ("NO EXPRESSION IN ");\
            printf (#name);\
            printf ("'\n");\
            assert (0);\
        }\
\
        return command(value, value_);\
}

#define CONDITIONAL(name)\
    SPACE\
\
    if (Expression[Index++] != '(')\
    {\
        printf ("NOT ENOUGH '(' in '");\
        printf (#name);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    int indcop = Index;\
\
    Exp_type value = GetEXP (var);\
\
    if (indcop == Index)\
    {\
        printf ("NOT EXPRESSION IN '");\
        printf (#name);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    if (Expression[Index++] != ')')\
    {\
        printf ("NOT ENOUGH ')' in '");\
        printf (#name);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    indcop = Index;\
\
    Exp_type value_ = GetOPER (var);\
\
    if (indcop == Index)\
    {\
        printf ("NO OPERATORS AFTER '");\
        printf (#name);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE

#define INOUT(namecmd)\
    SPACE\
    \
    if (Expression[Index++] != '(')\
    {\
        printf ("NOT ENOUGH '(' IN '");\
        printf (#namecmd);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    if (!isalpha(Expression[Index]))\
    {\
        printf ("BAD ARGUMENT IN '");\
        printf (#namecmd);\
        printf ("'\n");\
        assert (0);\
    }\
\
    char* name = GetV ();\
    int num = IsExisting (name, var);\
\
    if (num == -1)\
    {\
        printf ("UNCKNOWN VARIABLE %s IN '", name);\
        printf (#namecmd);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    if (Expression[Index++] != ')')\
    {\
        printf ("NOT ENOUGH ')' in '");\
        printf (#namecmd);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE\
\
    if (Expression[Index++] != ';')\
    {\
        printf ("NOT ENOUGH ';' in '");\
        printf (#namecmd);\
        printf ("'\n");\
        assert (0);\
    }\
\
    SPACE

enum types
{
    NUM      = 1,
    VAR      = 2,
    OPERATOR = 3,
    FUNCTION = 4
};

enum operators
{
    ADD   = 1,
    SUB   = 2,
    MUL   = 3,
    DIV   = 4,
    SIN   = 5,
    COS   = 6,
    SQRT  = 7,
    OPER  = 8,
    JA    = 9,
    JB    = 10,
    JE    = 11,
    JNE   = 12,
    JAE   = 13,
    JBE   = 14,
    ASN   = 15,
    IF    = 16,
    ELSE  = 17,
    WHILE = 18,
    SCAN  = 19,
    PRINT = 20,
    CALL  = 21,
    PARAM = 22
};

