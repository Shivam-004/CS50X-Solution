#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
 
int getK(int lettersCiphered, string k);
 
int main(int argc, string argv[])
{	
    if (argc != 2)
    {
        printf("Invalid\n");
        return 1;
    }
    string k = argv[1];
    for (int i = 0, length = strlen(k); i < length; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Invalid\n");
            return 1;
        }
    }
    printf("plaintext: ");
    string s = GetString();
    printf("ciphertext: ");
    int lettersCiphered = 0;
 
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
 
        if (isupper(c))
        {
            char ch = (((c - 65) + getK(lettersCiphered,k)) % 26) + 65;
            printf("%c", ch);
            lettersCiphered++;
        }
        else if(islower(c))
        {
            char ch = (((c - 97) + getK(lettersCiphered,k)) % 26) + 97;
            printf("%c", ch);
            lettersCiphered++;
        }
        else
        {
            printf("%c", c);
        }
    }
 
    printf("\n");
 
    return 0;
}
int getK(int lettersCiphered, string k)
{
    int length = strlen(k);
    return tolower(k[lettersCiphered % length]) - 97;
}