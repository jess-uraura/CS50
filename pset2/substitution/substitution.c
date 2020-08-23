#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char unique[26];

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) && strchr(unique, argv[1][i]) == 0)
        {
            unique[i] = argv[1][i];
            continue;
        }
        else
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", toupper(unique[text[i] - 65]));
        }
        else if (islower(text[i]))
        {
            printf("%c", tolower(unique[text[i] - 97]));
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    printf("\n");
    return 0;
}