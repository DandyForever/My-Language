#include <iostream>
#include "symbol difference.h"

char* make_buffer ();

const char* ChooseOperator (const int number);
void SaveToFile (FILE* output_file, Node* current, const int depth);

int main()
{
    Tree_t data;
    char* buffer = make_buffer ();
    data.PushFirst (GetG (buffer));
    FILE* tree_file = fopen ("../tree.txt", "w");
    assert (tree_file);
    SaveToFile (tree_file, data.First (), 0);
    fclose (tree_file);
    //data.Dump ();
    return 0;
}

int sizeofFILE (FILE *filein)
{
    const int versize = ftell (filein);

    fseek (filein, 0, SEEK_END);
    const int file_length = ftell (filein) - versize;
    rewind (filein);

    fseek (filein, versize, SEEK_SET);

    return file_length;
}

char* make_buffer ()
{
    FILE* input_file = fopen (file_name, "rb");
    assert (input_file);

    int file_size = sizeofFILE(input_file);

    char* buffer = (char*) calloc (file_size + 1, sizeof (*buffer));
    assert (buffer);

    fread (buffer, file_size, sizeof(*buffer), input_file);

    return buffer;
}

void SaveToFile (FILE* output_file, Node* current, const int depth)
{
    for (int i = 0; i < depth; i++)
    {
        fprintf (output_file, "\t");
    }

    switch (current->key)
    {
    case NUM:
        fprintf (output_file, "(N'%g'\n", current->value);
        break;

    case VAR:
        fprintf (output_file, "(V'%g'\n", current->value);
        break;

    case FUNCTION:
        fprintf (output_file, "(F'%g'\n", current->value);
        break;

    case OPERATOR:
        fprintf (output_file, "(O'%s'\n", ChooseOperator (current->value));
        break;
    }

    if (current->left)
        SaveToFile (output_file, current->left, depth + 1);

    if (current->right)
        SaveToFile (output_file, current->right, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        fprintf (output_file, "\t");
    }

    fprintf (output_file, ")\n");
}

const char* ChooseOperator (const int number)
{
    switch (number)
    {
    case ADD:
        return "+";
        break;

    case SUB:
        return "-";
        break;

    case MUL:
        return "*";
        break;

    case DIV:
        return "/";
        break;

    case SIN:
        return "sin";
        break;

    case COS:
        return "cos";
        break;

    case SQRT:
        return "sqrt";
        break;

    case OPER:
        return "operator";
        break;

    case JA:
        return ">";
        break;

    case JB:
        return "<";
        break;

    case JAE:
        return ">=";
        break;

    case JBE:
        return "<=";
        break;

    case JE:
        return "==";
        break;

    case JNE:
        return "<>";
        break;

    case ASN:
        return "=";
        break;

    case IF:
        return "if";
        break;

    case ELSE:
        return "else";
        break;

    case WHILE:
        return "while";
        break;

    case SCAN:
        return "scan";
        break;

    case PRINT:
        return "print";
        break;

    case CALL:
        return "call";
        break;

    case PARAM:
        return "param";
        break;

    default:
        return 0;
    }
}
