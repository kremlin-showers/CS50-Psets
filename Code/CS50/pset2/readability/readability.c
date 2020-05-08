#include <stdio.h>
#include <cs50.h>
#include <math.h>

int word_count(string);
int sentence_count(string);
int letter_count(string);

int main(void)
{
    string x = get_string("Text: ");
    float p = (float)letter_count(x) / word_count(x);
    float q = (float)sentence_count(x) / word_count(x);
    float L = 100 * p;
    float S = 100 * q;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if(index < 1)
    {
        printf("Befor Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


int word_count(string y)
{
   int x = 0;
   for(int i = 0; y[i] != '\0'; i++)
   {
       if (y[i] == ' ')
       {
           x++;
       }
   }
   return x+1;
}


int sentence_count(string y)
{
   int x = 0;
   for(int i = 0; y[i] != '\0'; i++)
   {
       if (y[i] == '.' || y[i] == '?' || y[i] == '!')
       {
           x++;
       }
   }
   return x;
}


int letter_count(string y)
{
   int x = 0;
   for(int i = 0; y[i] != '\0'; i++)
   {
       if(96 < (int)y[i] && (int)y[i] < 123)
       {
           x++;
       }
       else if(64 < (int)y[i] && (int)y[i] < 91 )
       {
           x++;
       }       
   }
   return x;
}
