#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);


    // Prompt user for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // Create variable to store years
    int years = 0;
    
    // Calculate number of years needed to reach end size
    while (start_size < end_size)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        years++;
    }

    // Print finalnumber of years
    printf("Years: %i\n", years);

} 