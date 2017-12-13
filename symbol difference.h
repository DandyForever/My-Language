#include "Tree_t.h"
#include "commands.h"
#include <assert.h>

Node* MakeNode (const int type, const double value, Node* Left, Node* Right);
Node* MakeNode (const int type, const double value);
int IsExisting (const char* name, Variables Var);

typedef Node* Exp_type;

double   GetN       ();
char*    GetV       ();
Exp_type GetE       (Variables var);
Exp_type GetP       (Variables var);
Exp_type GetT       (Variables var);
Exp_type GetEXP     (Variables var);
Exp_type GetASSN    (Variables var);
Exp_type GetIF      (Variables var);
Exp_type GetLOOP    (Variables var);
Exp_type GetINP     (Variables var);
Exp_type GetOUT     (Variables var);
Exp_type GetOPER    (Variables var);
Exp_type GetFUNC    ();
Exp_type GetCALL    (Variables var);
Exp_type GetG       (const char* expression);

Exp_type GetG (const char* expression)
{
    Expression = expression;
    Index = 0;

    SPACE

    /*if (Expression[Index] != 'v' && Expression[Index + 1] != 'r' && Expression[Index + 2] != 's' &&
        !isalpha(Expression[Index + 3]))
    {
        Index += 3;
        GetVRS ();
    }
    else
    {
        printf ("PROGRAM HAS NO VARIABLES\n");
        assert (0);
    }*/

    Exp_type value = 0;

    while (Expression[Index] == 'f' && Expression[Index + 1] == 'u' && Expression[Index + 2] == 'n' &&
            Expression[Index + 3] == 'c' && Expression[Index + 4] == 't' && Expression[Index + 5] == 'i' &&
            Expression[Index + 6] == 'o' && Expression[Index + 7] == 'n' && !isalpha (Expression[Index + 8]))
    {
        Index += 8;

        SPACE

        if (!value)
            value = GetFUNC ();

        else
            value = OPERAT(value, GetFUNC());

        SPACE
    }

    SPACE

    assert (Expression[Index] == '\0');

    return value;
}

/*void GetVRS ()
{
    SPACE

    while (Expression[Index] == ',' || Expression[Index] == ':')
    {
        char* name = GetV ();
        int isexisting = IsExisting (name, Var);

        if (isexisting != -1)
        {
            printf ("SAME VARIABLES NAMES %s\n", name);
            assert (0);
        }

        else
        {
            isexisting = Var.number;
            Var.name[Var.number++] = name;
        }

        SPACE
    }

    if (Expression[Index++] != ';')
    {
        printf ("NOT ENOUGH ';' IN VRS\n");
        assert (0);
    }

    SPACE
}*/

Exp_type GetFUNC ()
{
    Exp_type value = 0;

    SPACE

    char* name = GetV ();
    int isexisting = IsExisting (name, Func);

    if (isexisting != -1)
    {
        printf ("OVERLOADING OF FUNCTION %s IS IMPOSSIBLE\n", name);
        assert (0);
    }

    else
    {
        isexisting = Func.number;
        Func.name[Func.number++] = name;
    }

    SPACE

    Variables var = {};

    if (Expression[Index++] != '(')
    {
        printf ("EXPECTED '(' IN FUNCTION %s\n", name);
        assert (0);
    }

    SPACE

    while (Expression[Index] != ')')
    {
        char* namev = GetV ();
        int isexisting = IsExisting (namev, var);

        if (isexisting != -1)
        {
            printf ("SAME VARIABLES NAMES %s\n", namev);
            assert (0);
        }

        else
        {
            var.name[var.number++] = namev;
        }

        SPACE
    }

    SPACE

    if (Expression[Index++] != ')')
    {
        printf ("EXPECTED ')' IN FUNCTION %s\n", name);
        assert (0);
    }

    SPACE

    value = GetOPER (var);

    if (!strcmp ("main", name))
        return OPERAT(FUNCT(-var.number), value);

    return OPERAT(FUNCT(isexisting), value);
}

Exp_type GetOPER (Variables var)
{
    Exp_type value = 0;

    SPACE

    if (Expression[Index] == '[')
    {
        Index++;

        SPACE

        value = GetOPER (var);

        SPACE

        while (Expression[Index] != ']')
        {
            if (Expression[Index] == '\0')
            {
                printf ("NOT ENOUGH \']\'\n");
                assert (0);
            }

            Exp_type value_ = GetOPER (var);

            SPACE

            SPACE

            value = OPERAT(value, value_);

            SPACE
        }

        Index++;
    }
    else if (Expression[Index] == 'i' && Expression[Index + 1] == 'f' && !isalpha (Expression[Index + 2]))
    {
        value = GetIF (var);

        if (Expression[Index] == 'e' && Expression[Index + 1] == 'l' && Expression[Index + 2] == 's' &&
             Expression[Index + 3] == 'e' && !isalpha (Expression[Index + 4]))
        {
            Index += 4;

            SPACE

            int indcop = Index;

            Exp_type value_ = GetOPER (var);

            if (indcop == Index)
            {
                printf ("EMPTY OPERATOR 'else'\n");
                assert (0);
            }

            value = OTHER(value, value_);
        }
    }

    else if (Expression[Index] == 'e' && Expression[Index + 1] == 'l' && Expression[Index + 2] == 's' &&
             Expression[Index + 3] == 'e' && !isalpha (Expression[Index + 4]))
    {
        printf ("BAD OPERATOR 'if'\n");
        assert (0);
    }

    else if (Expression[Index] == 'w' && Expression[Index + 1] == 'h' && Expression[Index + 2] == 'i' &&
             Expression[Index + 3] == 'l' && Expression[Index + 4] == 'e' && !isalpha (Expression[Index + 5]))
    {
        value = GetLOOP (var);
    }

    else if (Expression[Index] == 'p' && Expression[Index + 1] == 'r' && Expression[Index + 2] == 'i' &&
              Expression[Index + 3] == 'n' && Expression[Index + 4] == 't' && !isalpha (Expression[Index + 5]))
    {
        value = GetOUT (var);
    }

    else if (Expression[Index] == 's' && Expression[Index + 1] == 'c' && Expression[Index + 2] == 'a' &&
              Expression[Index + 3] == 'n' && !isalpha (Expression[Index + 4]))
    {
        value = GetINP (var);
    }

    else if (Expression[Index] == 'c' && Expression[Index + 1] == 'a' && Expression[Index + 2] == 'l' &&
             Expression[Index + 3] == 'l' && !isalpha (Expression[Index + 4]))
    {
        value = GetCALL (var);
    }

    else if (isalpha (Expression[Index]))
    {
        value = GetASSN (var);
    }

    SPACE

    return value;
}

Exp_type GetCALL (Variables var)
{
    Index += 4;

    SPACE

    char* name = GetV ();
    int isexisting = IsExisting (name, Func);

    if (isexisting == -1)
    {
        printf ("NO SUCH FUNCTION %s\n", name);
        assert (0);
    }

    SPACE

    if (Expression[Index++] != '(')
    {
        printf ("EXPECTED '(' IN CALLING FUNCTION %s\n", name);
        assert (0);
    }

    SPACE

    Exp_type value = 0;
    while (Expression[Index] != ')')
    {
        char* namev = GetV ();
        int isexist = IsExisting (namev, var);

        if (isexist == -1)
        {
            printf ("NO SUCH VARIABLE %s\n", namev);
            assert (0);
        }

        else
        {
            if (value)
                value = PARAMET(value, VARIA(isexist));

            else
                value = VARIA(isexist);
        }

        SPACE
    }

    if (!value->left && !value->right)
        value = PARAMET(value, 0);

    SPACE

    if (Expression[Index++] != ')')
    {
        printf ("EXPRECTED ')' IN CALLING FUNCTION %s\n", name);
        assert (0);
    }

    SPACE

    if (Expression[Index++] != ';')
    {
        printf ("NOT ENOUGH ';' IN CALLING\n");
        assert (0);
    }

    SPACE

    return MakeNode (OPERATOR, CALL, value, FUNCT (isexisting));
}

Exp_type GetIF (Variables var)
{
    Index += 2;

    CONDITIONAL(if)

    return CONDIT(value, value_);
}

Exp_type GetLOOP (Variables var)
{
    Index += 5;

    CONDITIONAL(while)

    return LOOP(value, value_);
}

Exp_type GetINP (Variables var)
{
    Index += 4;

    INOUT(scan)

    return INPUT(VARIA(num));
}

Exp_type GetOUT (Variables var)
{
    Index += 5;

    INOUT(print);

    return OUTPUT(VARIA(num));
}

Exp_type GetASSN (Variables var)
{
    SPACE

    char* name = GetV ();
    int isexisting = IsExisting (name, var);

    if (isexisting == -1)
    {
        printf ("NO SUCH VARIABLE %s\n", name);
        assert (0);
    }

    Exp_type varr = VARIA(isexisting);

    SPACE

    assert (Expression[Index++] == '=');

    SPACE

    Exp_type expression = GetE (var);

    SPACE

    if (Expression[Index++] != ';')
    {
        printf ("NOT ENOUGH ';' IN ASSIGNMENT\n");
        assert (0);
    }

    return ASSN(expression, varr);
}

Exp_type GetEXP (Variables var)
{
    Exp_type value = GetE (var);

    SPACE

    if (Expression[Index] == '>' && Expression[Index + 1] == '=')
        COMPCMD(>=, EMORE, 2)
    else if (Expression[Index] == '<' && Expression[Index + 1] == '>')
        COMPCMD(<>, NEQUAL, 2)
    else if (Expression[Index] == '<' && Expression[Index + 1] == '=')
        COMPCMD(<=, ELESS, 2)
    else if (Expression[Index] == '=' && Expression[Index + 1] == '=')
        COMPCMD(==, EQUAL, 2)
    else if (Expression[Index] == '>')
        COMPCMD(>, MORE, 1)
    else if (Expression[Index] == '<')
        COMPCMD(<, LESS, 1)

    else
        return value;
}

Exp_type GetE (Variables var)
{
    Exp_type value = GetT (var);

    SPACE

    while (Expression[Index] == '+' || Expression[Index] == '-')
    {
        SPACE

        const char operation = Expression[Index];
        Index++;

        SPACE

        int ind_cop = Index;

        Exp_type next_value = GetT (var);

        SPACE

        assert (ind_cop != Index);

        if (operation == '+')
            value = PLUS(value, next_value);

        else
            value = MINUS(value, next_value);
    }

    return value;
}

Exp_type GetT (Variables var)
{
    Exp_type value = GetP (var);

    SPACE

    while (Expression[Index] == '*' || Expression[Index] == '/')
    {
        SPACE

        const char operation = Expression[Index++];

        SPACE

        int ind_cop = Index;

        Exp_type next_value = GetP (var);

        SPACE

        assert (ind_cop != Index);

        if (operation == '*')
            value = MULTIP(value, next_value);

        else
            value = DIVIS(value, next_value);
    }

    return value;
}

Exp_type GetP (Variables var)
{
    Exp_type value = 0;

    SPACE

    if (Expression[Index] == '(')
    {
        Index++;

        SPACE

        value = GetE (var);

        SPACE

        assert (Expression[Index++] == ')');

        SPACE

        return value;
    }

    else if (Expression[Index] == 's' && Expression[Index + 1] == 'i' && Expression[Index + 2] == 'n')
    {
        Index += 3;

        SPACE

        value = SINUS(GetP (var));

        SPACE
    }

    else if (Expression[Index] == 'c' && Expression[Index + 1] == 'o' && Expression[Index + 2] == 's')
    {
        Index += 3;

        SPACE

        value = COSINUS(GetP (var));

        SPACE
    }

    else if (Expression[Index] == 's' && Expression[Index + 1] == 'q' &&
              Expression[Index + 2] == 'r' && Expression[Index + 3] == 't')
    {
        Index += 4;

        SPACE

        value = RADICAL(GetP (var));

        SPACE
    }

    else if (isalpha (Expression[Index]))
    {
        SPACE

        char* name = GetV ();
        int isexisting = IsExisting (name, var);

        if (isexisting == -1)
        {
            printf ("UNCKNOWN VARIABLE %s\n", name);
            assert (0);
        }

        value = VARIA(isexisting);

        SPACE
    }

    else if (Expression[Index] >= '0' && Expression[Index] <= '9' || Expression[Index] == '+' || Expression[Index] == '-')
    {
        SPACE

        value = NUMERIC(GetN ());

        SPACE
    }

    else
    {
        printf ("UNCKNOWN COMMAND\n");
        assert (0);
    }

    return value;
}

double GetN ()
{
    double value = 0;

    while (Expression[Index] >= '0' && Expression[Index] <= '9')
    {
        value = value * 10 + Expression[Index] - '0';
        Index++;
    }

    if (Expression[Index] == '.')
    {
        Index++;

        int power = 10;

        while (Expression[Index] >= '0' && Expression[Index] <= '9')
        {
            value = value + (double) (Expression[Index] - '0') / power;
            power *= 10;

            Index++;
        }
    }

    return value;
}

char* GetV ()
{
    char* name = new char[varnamesize] {};
    assert (name);

    int length = 0;

    while (isalpha (Expression[Index]) || isdigit (Expression[Index]))
    {
        name[length++] = Expression[Index++];
    }

    name[length] = '\0';

    return name;
}

int IsExisting (const char* name, Variables Var)
{
    for (int i = 0; i < Var.number; i++)
    {
        if (!strcmp (name, Var.name[i]))
            return i;
    }

    return -1;
}

Node* MakeNode (const int type, const double value, Node* Left, Node* Right)
{
    Node* node = new Node;
    assert (node);

    node->key = type;
    node->value = value;

    node->left = Left;
    node->right = Right;

    return node;
}

Node* MakeNode (const int type, const double value)
{
    Node* node = new Node;
    assert (node);

    node->key = type;
    node->value = value;

    node->left = nullptr;
    node->right = nullptr;

    return node;
}
