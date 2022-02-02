#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Declaring functions to count letters, words, and sentences
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    //Gets input text from user
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text) + 1; //Adds one to number of words to account for 1st word
    int sentences = count_sentences(text);

    float L = ((float)letters / words) * 100; //letters per 100 words
    float S = ((float)sentences / words) * 100; //sentences per 100 words

    int score = round((0.0588 * L) - (0.296 * S) - 15.8); //Coleman-Liau Formula

    if (score < 1) //Prints appropriate grade levels
    {
        printf("Before Grade 1\n");
    }
    else if (score >= 1 && score <= 16)
    {
        printf("Grade %i\n", score);
    }
    else
    {
        printf("Grade 16+\n");
    }

}

int count_letters(string text) //Counts lower and uppercase characters for letters
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        //if any character is of int 65-90 or 97-122 then i++
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text) //Counts spaces to count word number
{
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        //if any character is of int 65-90 or 97-122 then i++

        if (text[i] == 32)
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text) //Counts valid punctuation to count sentence number
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        //if any character is of int 65-90 or 97-122 then i++
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}