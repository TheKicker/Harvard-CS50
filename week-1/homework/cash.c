#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // TODO: prompt the user for cents > 0
    int c;
    do
    {
        c = get_int("Enter number of cents: ");
    }
    while (c < 1); // Make sure its in range
    return c; // Return their input
}

int calculate_quarters(int cents)
{
    // Greedy Algo 25
    int num = cents / 25;
    return num;
}

int calculate_dimes(int cents)
{
    // Greedy Algo 10
    int num = cents / 10;
    return num;
}

int calculate_nickels(int cents)
{
    // Greedy Algo 5
    int num = cents / 5;
    return num;
}

int calculate_pennies(int cents)
{
    // Greedy Algo 1
    int num = cents / 1;
    return num;
}
