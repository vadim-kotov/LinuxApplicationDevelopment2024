#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main() 
{
	int low = 1;
	int high = 99;
	int guess;
	char resp[2], in;

	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALE_PATH);
	textdomain("guess");

	printf(_("Think of a number between 1 and 100\n"));

	while (low <= high) 
	{
		guess = (low + high) / 2;

		printf(_("Is your number bigger than %d? (y/n): "), guess);
		scanf(" %c", &in);
		resp[0] = in;
		resp[1] = '\0';

		if (!strcmp(resp, _("y")))
		{
			low = guess + 1;
		} 
		else if (!strcmp(resp, _("n")))
		{
			high = guess - 1;
		} 
		else
		{
			printf(_("Please, type 'y'(yes) or 'n'(no).\n"));
		}
	}

	printf(_("Your number is: %d!\n"), low);
	
	return 0;
}
