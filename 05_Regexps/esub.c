#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

#define MAXGR 10
#define ERRBUF_SIZE 100
#define MAX_BACKREF 100

void usage(char *prog)
{
	fprintf(stderr, "%s: Usage: ./esub <regexp> <pattern> <test>\n", prog);
}

int main(int argc, char **argv)
{
	char *string, *subs, *subs_br, *out;
	regex_t regex;
	regmatch_t bags[MAXGR];
	int errcode, b, e, i, sb, se, bag_num;
	char errbuf[ERRBUF_SIZE];

	if(argc < 4)
	{
		usage(argv[0]);
		return 1;
	}

	string = argv[3];
	subs = argv[2];

	if((errcode = regcomp(&regex, argv[1], REG_EXTENDED)))
	{
		regerror(errcode, &regex, errbuf, ERRBUF_SIZE);
		fprintf(stderr, "Regular expression compilation error: %s\n", errbuf);
		regfree(&regex);
		return 1;
	}

	if((errcode = regexec(&regex, string, MAXGR, bags, 0)))
	{
		regerror(errcode, &regex, errbuf, ERRBUF_SIZE);
		fprintf(stderr, "Regular expression execution error: %s\n", errbuf);
		regfree(&regex);
		return 1;
	}
	
	subs_br = calloc(strlen(subs) + strlen(string) * MAX_BACKREF, sizeof(char));
	if(subs_br == NULL)
	{
		perror("Memory allocation error: ");
		regfree(&regex);
		return 1;
	}
	i = 0;
	sb = 0;
	se = 0;
	while(subs[i] != '\0')
	{
		if(subs[i] == '\\')
		{
			if(subs[i+1] == '\\')
			{
				se = i + 1;
				strncat(subs_br, subs + sb, se - sb);
				sb = i + 2;
				i += 2;
				continue;
			}
			else if(isdigit(subs[i+1]))
			{
				se = i;
				strncat(subs_br, subs + sb, se - sb);
				bag_num = subs[i+1] - '0';
				b = bags[bag_num].rm_so; 
				e = bags[bag_num].rm_eo;
				if(b < 0)
				{
					fprintf(stderr, "Error in pattern string: no back reference with number %d\n", bag_num);
					regfree(&regex);
					free(subs_br);
					return 1;
				}
				strncat(subs_br, string + b, e - b);
				sb = i + 2;
				i += 2;
				continue;
			}
		}
		i++;
	}
	se = i;
	strncat(subs_br, subs + sb, se - sb);

	out = calloc(strlen(string) + strlen(subs_br), sizeof(char));
	if(out == NULL)
	{
		perror("Memory allocation error ");
		regfree(&regex);
		free(subs_br);
		return 1;
	}
	b = bags[0].rm_so; e = bags[0].rm_eo;
	strncat(out, string, b);
	strcat(out, subs_br);
	strcat(out, string + e);

	printf("%s\n", out);

	regfree(&regex);
	free(subs_br);
	free(out);
	return 0;
}
