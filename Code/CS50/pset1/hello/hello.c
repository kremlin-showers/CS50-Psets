#include<stdio.h>
#include<cs50.h>

int main(void)
{
    //getting the name
    string i = get_string("what's your name?\n");
    //printing the name
    printf("Hello, %s\n ", i);
}

