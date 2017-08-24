#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

 int main(int argc, string argv[])
 {
    if (argc != 2)
    {
        printf("Nope\n");
        return 1;
    }
    int k = atoi(argv[1]);
    if (k < 0)
    {
        printf("Usage : caesar k\n");
        return 1;
    }
    else
    {
        
       printf("plaintext:  ");
        string code = GetString();
        printf("ciphertext: ");
        for (int i = 0, n = strlen(code); i < n; i++)
            {
                if islower(code[i])
                  code[i]=((((code[i] + k) - 97) % 26) + 97);
                else if isupper(code[i])
                    code[i]=((((code[i] + k) - 65) % 26) + 65);
                else
                    code[i]=(code[i]);
            }
           puts(code);
            
            return 0;
    }
 }