#include<stdio.h>
#include<cs50.h>
#include<math.h>

int digit_sum(int n);

int main(void)
{
    // getting the number
    long x = get_long("What's the number");
    long z = x;
    int dig = 0;
    string returnstring = "INVALID\n";
  
// finding the number digits in the number
    for (int i = 0 ; floor(x / pow(10, i)) != 0 ; i++)
    {
        dig++;
    }
// finding a valid card type
    int aye = floor(z / pow(10, dig - 1));
    int axe = aye * 10 + floor((z - aye * pow(10, dig - 1)) / pow(10, dig - 2));
    
// criteria for a VISA card   
    
    if ((dig == 13 || dig == 16) && floor(x / pow(10, dig - 1)) == 4)
    {
        returnstring = "VISA\n";
    }
// criteria for a MASTERCARD
    
    else if (50 < axe && axe < 56 && dig == 16)
    {
        returnstring = "MASTERCARD\n";
    }
// criteria for an AMERICAN EXPRESS card
    
    else if ((axe == 34 || axe == 37) && dig == 15)
    {         
        returnstring = "AMEX\n";
    }
// invalidating the card if it does not fit any criteria
    else
    {
        returnstring = "INVALID\n";
    }
           
// Luhn's Algorithm
    
    if (dig % 2 == 0)
    {
        int seq1 = 0;
        int seq2 = 0;
        for (int p = dig ; p != 0 ; p = p - 2)
        {
// finds the sum required in Luhn's algorithm
            
            int y = x / pow(10, p - 1);
            seq1 += digit_sum(2 * y);
            x = x - pow(10, p - 1) * y;
            seq2 += x / pow(10, p - 2);
            int ab = x / pow(10, p - 2);
            
            x = x - pow(10,  p - 2) * ab;                
        }
// checks weather the sum is a multiple of 10
        
        if ((seq1 + seq2) % 10 == 0)
        {
            printf("%s", returnstring);
        }
// if it is not then invalidates the number
        
        else
        {
            printf("INVALID\n");
        }        
    }
// The same but for the case of odd number of digits
    else
    {
        int seq1 = 0;
        int seq2 = 0;
        for (int p = dig ; p != -1 ; p = p - 2)
        {
            int y = x / pow(10, p - 1);
            seq1 += y;
            x = x - pow(10, p - 1) * y;
                
            int ab = x / pow(10, p - 2);
            seq2 += digit_sum(2 * ab);
            x = x -  pow(10, p - 2) * ab;
                
        }
        if ((seq1 + seq2) % 10 == 0)
        {
            printf("%s", returnstring);
        }
        else
        {
            printf("INVALID\n");
        }    
    }  
}


// function for sum of digits of a number
int digit_sum(int n)
{  
    int x = 0;
    int z = 0;
    for (int i = 0 ; n / pow(10, i) != 0 ; i++)
    {
        x++;
       
    }
    while (n != 0)
    {
        int y = n / pow(10, x - 1);
        z += y; 
        n = n - pow(10, x - 1) * y;
        x = x - 1;       
    }
    return z;    
}
