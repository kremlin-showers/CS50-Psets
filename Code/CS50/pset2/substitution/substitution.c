#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

int keycheck(string);



// main function
int main(int argc, string argv[])
{
    string z = argv[1];



// checking the number of arguements
    if (argc != 2)
    {
        printf("Use: ./substitution key\n");
        return 1;
    }
// using the keycheck function
    else if (keycheck(argv[1]) != 0)
    {
        printf("Need valid string\n");
        return 1;
    }

    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            z[i] = toupper(argv[1][i]);
        }
// getting the input string
        string input = get_string("plaintext: ");
        for (int i = 0; i < strlen(input); i++)
        {
// checking weather input[i] is a letter
            if (96 < tolower(input[i]) && tolower(input[i]) < 123)
            {
// checking weather it is uppercase or lowercase
                if (isupper(input[i]) != 0)
                {
// making the substitution
                    char chara = input[i];
                    input[i] = z[chara - 65];
                }
                else
                {
                    char chara = input[i];
                    input[i] = tolower(z[chara - 97]);
                }








            }
            else
            {

            }







        }
// printing the substitution
        printf("ciphertext: %s\n", input);

    }


}
// function for checking valid strings
int keycheck(string y)
{
    string z = y;

    for (int i = 0; i < 26; i++)
    {
        z[i] = toupper(y[i]);
    }
// Checking that the length is 26
    if (strlen(y) != 26)
    {
        return 1;
    }
// checking that all elements of the string are letters
    for (int i = 0; i < 26; i++)
    {
        if (z[i] < 91 && z[i] > 64)
        {

        }
        else
        {
// returning 1 if any of the elements is not a letter
            return 1;
        }

    }
// checking for repeated letters
    for (int j = 65; j < 91; j++)
    {
        int x = 0;
        for (int i = 0; i < 26; i++)
        {
            if (j == z[i])
            {
                x++;
            }
            else
            {

            }




        }
// returning 1 if a character appears more than one or zero times
        if (x != 1)
        {
            return 1;
        }
        else
        {

        }
    }
// returning 0 if all is correct
    return 0;
}
