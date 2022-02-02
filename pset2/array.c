 #include <cs50.h>
#include <stdio.h>

int main(void)
{
    int scores[3];
    scores[0] = 5;
    scores[1] = get_int("Score: ");
    scores[0] = 5;

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0); 

}

