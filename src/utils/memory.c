#include "../../../include/core/shell.h"

void free_and_null(void **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void free_array(void ***arr)
{
	int i = 0;
	if (arr)
	{
		while ((*arr)[i])
		{
			free_and_null((*arr)[i]);
		}
		free_and_null(*arr);
	}
}