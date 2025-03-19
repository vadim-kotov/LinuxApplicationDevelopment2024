#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include "rhash.h"

#include "config.h"
//#define READLINE

#ifdef READLINE

#include <readline/readline.h>
#include <readline/history.h>

#endif

int main()
{
	unsigned char digest[64];
	char output[130];
	char *input, *algin, *arg;
	unsigned long long alg, flags;
	int res;

#ifndef READLINE

	size_t len;

#endif

	rhash_library_init();

	input = NULL;
	while(1)
	{
		free(input);

#ifdef READLINE

		input = readline("> ");
		if(input && *input)
		{
			add_history(input);
		}
		if(input == NULL)
		{
			break;
		}

#else

		printf("> ");

		input = NULL;
		len = 0;
		errno = 0;
		if((getline(&input, &len, stdin)) == -1)
		{
			if(errno)
			{
				perror("Reading input error: ");
				free(input);
				return 1;
			}

			break;
		}

#endif

		algin = strtok(input, " \n");
		if(algin == NULL)
		{
			continue;
		}

		if(!strcasecmp(algin, "md5"))
		{
			alg = RHASH_MD5;
		}
		else if(!strcasecmp(algin, "sha1"))
		{
			alg = RHASH_SHA1;
		}
		else if(!strcasecmp(algin, "tth"))
		{
			alg = RHASH_TTH;
		}
		else
		{
			fprintf(stderr, "Unknown command: %s\n", algin);
			continue;
		}

		if(isupper(algin[0]))
		{
			flags = RHPR_BASE64;
		}
		else
		{
			flags = RHPR_HEX;
		}

		arg = strtok(NULL, " \n");
		if(arg == NULL)
		{
			fprintf(stderr, "Missing second argument in command: %s\n", algin);
			continue;
		}
		
		if(arg[0] == '\"')
		{
			res = rhash_msg(alg, arg, strlen(arg), digest);
			if(res < 0)
			{
				fprintf(stderr, "String digest calculation error\n");
				continue;
			}

			rhash_print_bytes(output, digest, rhash_get_digest_size(alg), flags);
			printf("%s\n", output);
		}
		else
		{
			errno = 0;
			res = rhash_file(alg, arg, digest);
			if(res < 0)
			{
				fprintf(stderr, "File digest calculation error: %s: %s\n", arg, strerror(errno));
				continue;
			}

			rhash_print_bytes(output, digest, rhash_get_digest_size(alg), flags);
			printf("%s\n", output);
		}

	}

	free(input);

#ifdef READLINE

	clear_history();
	rl_deprep_terminal();

#endif

	printf("\n");
	return 0;

}
