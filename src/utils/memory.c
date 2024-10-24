#include "../../include/utils/utils.h"

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

void ft_free_double(char **smth)
{
	int x;

	if (!smth)
		return;
	x = ft_array_size(smth);
	while (smth[x])
	{
		free(smth[x]);
		smth[x] = NULL;
		x--;
	}
	if (smth)
		free(smth);
	smth = NULL;
}
