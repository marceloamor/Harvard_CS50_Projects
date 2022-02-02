#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for pyramid correct height 
    int height;
    do
    {
        height = get_int("Pyramid Height: ");
    }
    while (height < 1 || height > 8);

    //to iterate over the same number of rows as height given
    for (int row = 0; row < height; row++) 
    {
        //to print a number of spaces complimentary to number of hashes
        for (int space = height - row - 1; space > 0; space--) 
        {
            printf(" ");
        }
        //to print increasing number of hashes per row 
        for (int hash = 0; hash < row + 1; hash++) 
        {
            printf("#");
        }
        
        //add spaces between left and right aligned hashes 
        printf("  ");
        
        //add hashes on the right side 
        for (int right_hashes = 0; right_hashes < row + 1; right_hashes++)
        {
            printf("#");
        }
        
        //ends each row
        printf("\n"); 
    }
    
}


   