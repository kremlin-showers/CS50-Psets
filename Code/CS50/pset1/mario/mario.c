#include<stdio.h>
#include<cs50.h>


void make_brick(int n);
int main(void)
{
    //getting a valid height
    int h = 0;
    while (h < 1 || h > 8)
    {
        h = get_int("Height:");
    }
    //our main loop
    for (int i = 1; i < h + 1 ; i++)
    {
        //printing the required spacebars before the hashtags
        for (int x = 0; x < h - i ; x++)
        {
            printf(" ");



        }
        //use of a function defined later
        make_brick(i);



    }





}
//function to print the hashtags in the pyramid formation
void make_brick(int n)
{

    for (int i = 0; i < n ; i++)
    {

        printf("#");
    }
    printf("  ");
    for (int x = 0; x < n; x++)
    {


        printf("#");

    }
    printf("\n");


}