#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>

typedef int (*unlink_type)(const char *);

int unlink(char *fn)
{
	if(strstr(fn, "PROTECT") != NULL)
	{
		return 0;
	}
	else
	{
		return ((unlink_type)(dlsym(RTLD_NEXT, "unlink")))(fn);
	}
}
