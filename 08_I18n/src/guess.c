#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main() 
{
	int low = 1;
	int high = 99;
	int guess;
	char in[3]; // 2 for UTF-8 char & 1 for '\0'

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	printf(_("Think of a number between 1 and 100\n"));

	while (low <= high) 
	{
		guess = (low + high) / 2;

		printf(_("Is your number bigger than %d? (y/n): "), guess);
		scanf(" %3s", in);

		if (!strcmp(in, _("y")))
		{
			low = guess + 1;
		} 
		else if (!strcmp(in, _("n")))
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
