#include "strings.h"

char* get_number_str(FILE*text, int number)
{
    rewind(text);
    char* str = (char*)calloc(KB, sizeof(char));
    int i = 0;
    while (!feof(text) && i < number)
    {
        fgets(str, KB - 1, text);
        i++;
        if (feof(text))
            break;
    }
    int length = (int)strlen(str);
    if (str[length-1] != '\n')
    {
        str[length] = '\n';
        str[length + 1] = '\0';
    }
    return str;
}




char* decrease_str(char* orig)
{
    char* buf = (char*)calloc(KB, sizeof(char));
    if (buf == NULL)
        exit(1);
    strcpy_s(buf, KB, orig);
    int length = (int)strlen(buf);
    buf[length - 1] = '\0';
    return buf;
}
