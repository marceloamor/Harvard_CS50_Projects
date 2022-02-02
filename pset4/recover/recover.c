#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
#define BUFFER_SIZE 512
#define FILE_NAME_SIZE 8

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    //open input file and create pointer to its beginning
    char *input = argv[1];

    FILE *input_ptr = fopen(input, "r");
    if (input_ptr == NULL)
    {
        printf("Error: file cannot be opened\n");
        return 1;
    }

    //create and initialise variables
    BYTE buffer[BUFFER_SIZE];
    int counter = 0;
    FILE *jpeg = NULL;
    char file_name[FILE_NAME_SIZE];

    //open while loop to iterate through available file size
    while (fread(&buffer, BUFFER_SIZE, 1, input_ptr) == 1)
    {
        //validate start of JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if current JPEG not the first found, then close the current JPEG and save it
            if (!(counter == 0))
            {
                fclose(jpeg);
            }
            sprintf(file_name, "%03d.jpg", counter);
            jpeg = fopen(file_name, "w");
            counter ++;
        }
        //if not the first JPEG, simply write to new one
        if (counter > 0)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, jpeg);
        }
    }

    //close open files
    fclose(input_ptr);
    fclose(jpeg);

}