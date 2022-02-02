#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long card; //declare a long variable to store card number
    int length = 0; //declare a variable to store card length

    do
    {
        card = get_long("Card number?: ");  //get card number as input from user
    }
    while (card < 0);    //do not accept negative numbers as input

    long card_check  = card; // copy of card to use for validation


    int card1 = (((card % 100) / 10) * 2);  //save every other digit starting from 2nd last
    int card2 = (((card % 10000) / 1000) * 2);
    int card3 = (((card % 1000000) / 100000) * 2);
    int card4 = (((card % 100000000) / 10000000) * 2);
    int card5 = (((card % 10000000000) / 1000000000) * 2);
    int card6 = (((card % 1000000000000) / 100000000000) * 2);
    int card7 = (((card % 100000000000000) / 10000000000000) * 2);
    int card8 = (((card % 10000000000000000) / 1000000000000000) * 2);

    card1 = (card1 / 10) + (card1 % 10);
    card2 = (card2 / 10) + (card2 % 10);
    card3 = (card3 / 10) + (card3 % 10);
    card4 = (card4 / 10) + (card4 % 10);
    card5 = (card5 / 10) + (card5 % 10);
    card6 = (card6 / 10) + (card6 % 10);
    card7 = (card7 / 10) + (card7 % 10);
    card8 = (card8 / 10) + (card8 % 10);

    //adds output of multipled digits with the unmultiplied digits and checks if divisible by 10
    int even_sums = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;
    int odd_sums = (card % 10) + ((card % 1000) / 100) + ((card % 100000) / 10000) + ((card % 10000000) / 1000000)\
                   + ((card % 1000000000) / 100000000) + ((card % 100000000000) / 10000000000)\
                   + ((card % 10000000000000) / 1000000000000) + ((card % 1000000000000000) / 100000000000000);

    if (((even_sums + odd_sums) % 10) != 0)
    {
        printf("INVALID\n");
        return 0;
    }


    //Checking specific card types for validity
    //by length
    while (card > 0)
    {
        card = card / 10;
        length++;
    }

    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }


    long Mastercard = card_check / 100000000000000;     //saves first two digits of a 16 digit card number for Mastercard
    long AMEX = card_check / 10000000000000;    //saves first two digits of a 15 digit card number for AMEX
    long Visa13 = card_check / 1000000000000;  //saves first digit of a 16 digit card number for 13 digit Visa
    long Visa16 = card_check / 1000000000000000;  //saves first digit of a 16 digit card number for 16 digit Visa



    if (length == 15) //validate AMEX cards
    {
        if (AMEX != 34 && AMEX != 37)
        {
            printf("INVALID\n");
            return 0;
        }
        else
        {
            printf("AMEX\n");
            return 0;
        }
    }

    if (length == 16) //validation for 16 digit cards, either Visa or Mastercard
    {
        if (Visa16 == 4)  //Visa validation
        {
            printf("VISA\n");
            return 0;
        }
        else if (Mastercard == 51 || Mastercard == 52 || Mastercard == 53 || Mastercard == 54\
                 || Mastercard == 55)  //Mastercard validation
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if (Visa16 != 4 && Mastercard != 51 && Mastercard != 52 && Mastercard != 53 && Mastercard != 54 && Mastercard != 55)
        {
            printf("INVALID\n");
            return 0;
        }
    }

    if (length == 13 && Visa13 == 4) //final validation of 13 digit Visa card
    {
        printf("VISA\n");
        return 0;
    }
    else if (length != 13 && Visa13 != 4)
    {
        printf("INVALID\n");
        return 0;
    }


}