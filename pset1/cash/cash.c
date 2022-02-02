#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coins = 0;   //set number of coins to 0
    float change; //declare a float variable to store remaining change throughout

    do
    {
        change = get_float("How much change is owed?: ");  //get change from user
    }
    while (change < 0);    //make sure change is not less than 0
    int cent = round(change * 100); //convert and round to dollar values to cents

    while (cent >= 25)
    {
        cent = cent - 25; // subtract quarter value until change is less than quarter value
        coins++;  //add number of quarters to coin count
    }
    while (cent >= 10)
    {
        cent = cent - 10; // subtract dime value until change is less than dime value
        coins++;       //add number of dimes to coin count
    }
    while (cent >= 5)
    {
        cent = cent - 5;    // subtract nickel value until change is less than nickel value
        coins++;  //add number of nickels to coin count
    }
    while (cent >= 1)
    {
        cent = cent - 1;  // subtract penny value until no change remaining
        coins++;     //add number of pennies to coin count
    }
    printf("%i\n", coins);
}