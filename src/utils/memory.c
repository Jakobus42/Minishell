#include "../../include/utils/utils.h"

void free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void free_array(void ***arr)
{
	int i;

	i = 0;
	if (!arr || !*arr)
		return;
	while ((*arr)[i])
	{
		free_and_null((void **) &(*arr)[i]);
		i++;
	}
	free_and_null((void **) arr);
}
