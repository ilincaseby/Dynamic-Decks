#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

char *
allocate_for_strings(char *s)
{
	s = malloc(command_size);

	if(!s) {
		fprintf(stderr, "Malloc failed\n");
		return NULL;
	}

	return s;
}

void
remove_basic_newline(char *s)
{
	int len = strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}