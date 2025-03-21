#include <stdio.h>

int main() 
{
    int low = 1;
    int high = 100;
    int guess;
    char response;

    printf("Think of a number between 1 and 100\n");

    while (low <= high) 
    {
        guess = (low + high) / 2;

        printf("Is your number bigger than %d? (y/n): ", guess);
        scanf(" %c", &response);

        if (response == 'y') 
	{
            low = guess + 1;
        } 
	else if (response == 'n') 
	{
            high = guess - 1;
        } 
	else 
	{
            printf("Please, type 'y'(yes) or 'n'(no).\n");
        }
    }

    printf("Your number is: %d!\n", low);

    return 0;
}
