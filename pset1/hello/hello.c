#include <cs50.h>
#include <stdio.h>


int main(void)
{
    //Ask for a name, save it as a string, and print a greeting
    string name = get_string("What is your name? \n");

    printf("hello, %s\n", name);
}


