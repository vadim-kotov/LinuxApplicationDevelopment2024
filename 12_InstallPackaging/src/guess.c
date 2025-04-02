#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <errno.h>
#include "config.h"
#include "libroman.h"

/** @mainpage
 * # Interactive number guessing game
 * Choose number between 1 and 100 and answer questions with only 'yes' or 'no'
 *
 * `Usage: guess [OPTION]`
 *
 * ## Options:
 * - `-r` - switch to Roman numerals
 * - `-h`, `--help` - show this help
 * - `--version` - show version
 */

/** @file guess.c
 * Implementation
 */ 

#define _(STRING) gettext(STRING)

/** Show version of application */
void version()
{
	printf("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
}

/** Show help */
void help()
{
	printf(_("Usage: %s [OPTION]\n"), PACKAGE_TARNAME);
	printf(_("Interactive number guessing game.\n"));
	printf(_("Choose number between 1 and 100 and answer questions with only 'yes' or 'no'\n\n"));
	printf(_("Options:\n"));
	printf(_("  -r             switch to Roman numerals\n"));
	printf(_("  -h, --help     show this help\n"));
	printf(_("      --version  show version\n"));
}

/** Use numerals in Roman mode.
 *
 * Run application with -r key to enable.
 */
bool roman_mode = false;

/** Print number in Arabic or Roman mode depending on global variable
 * @p roman_mode.
 *
 * @param num number to print
 */
void print_number(int num)
{
	if(roman_mode)
	{
		printf("%s", get_roman_numeral(num));
	}
	else
	{
		printf("%d", num);
	}
}

int main(int argc, char **argv) 
{
	int low = 1;
	int high = 99;
	int guess;
	char *in = NULL;
	size_t n = 0;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
		{
			help();
			return 0;
		}
		if(!strcmp(argv[i], "--version"))
		{
			version();
			return 0;
		}
		if(!strcmp(argv[i], "-r"))
		{
			roman_mode = true;
		}

	}

	printf(_("Think of a number between 1 and 100\n"));

	while (low <= high) 
	{
		guess = (low + high) / 2;

		printf(_("Is your number bigger than "));
		print_number(guess);
		printf(_("? (y/n): "));

		errno = 0;
		if(getline(&in, &n, stdin) == -1)
		{
			if(errno)
			{
				printf("\n");
				fprintf(stderr, _("Input read error\n"));
				return 1;
			}
			else 
			{
				printf("\n");
				fprintf(stderr, _("Input stopped by user\n"));
				return 0;
			}
		}

		in[strlen(in) - 1] = '\0';
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

		free(in);
		in = NULL;
		n = 0;
	}

	printf(_("Your number is: "));
	print_number(low);
	printf("!\n");
	
	return 0;
}
