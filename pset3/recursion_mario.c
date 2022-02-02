#include <cs50.h>
#include <stdio.h>

void draw(int height);

int main(void)
{
    
    int height = get_int("Height: ");

    // Draw pyramid
    draw(height);

}

void draw(int height)
{
    if ((height -1) != 0)
    {
        draw(height-1);
    }
    
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");
}

