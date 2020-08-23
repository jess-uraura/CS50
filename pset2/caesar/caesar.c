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

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]) % 26;
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        int shifted = (int) text[i] + key;

        if (isupper(text[i]))
        {
            if (shifted > 90) // ASCII code for "Z"
            {
                printf("%c", shifted - 26);
            }
            else
            {
                printf("%c", shifted);
            }
        }
        else if (islower(text[i]))
        {
            if (shifted > 122) // ASCII code for "z"
            {
                printf("%c", shifted - 26);
            }
            else
            {
                printf("%c", shifted);
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    printf("\n");
    return 0;
}