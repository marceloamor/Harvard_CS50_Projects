#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Saving constant values relating to the alphabet
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int N = 26;


int main(int argc, string argv[])
{
    // Verify command line argument contains two arguments
    if (argc != 2)
    {
        printf("Please provide one command line argument only.\n");
        return 1;
    }

    // Verify key contains 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Varify key contains only letters
    int letters[N];
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Check only letters are used
        if (!((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z')))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }

        // Convert key to uppercase to facilitate
        if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] = toupper(argv[1][i]);
        }

        // Check for repeated letters
        for (int j = 0; j < N; j++)
        {
            if (argv[1][i] == letters[j])
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }

        letters[i] = argv[1][i];
    }

    // Prompt user for plaintext input
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    char ciphertext[length];

    // Convert to ciphertext
    // Loop through each char in plaintext
    for (int i = 0; i < length + 1; i++)
    {
        // If uppercase, use alphabet as stored
        if (isupper(plaintext[i]) != 0)
        {
            for (int j = 0; j < N; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    ciphertext[i] = argv[1][j];
                    break;
                }
            }
        }

        // If lowercase use alpabet converted to lowercase
        else if (islower(plaintext[i]) != 0)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                if (plaintext[i] == tolower(alphabet[j]))
                {
                    ciphertext[i] = tolower(argv[1][j]);
                    break;
                }
            }
        }
        // Pass non letters as is
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n", ciphertext);

}