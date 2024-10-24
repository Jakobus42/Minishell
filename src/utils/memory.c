#include "../../include/utils/utils.h"

#include <stdlib.h>
#include <string.h>

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	if (new_size == 0)
		return (free(ptr), NULL);
	void *new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (ptr)
	{
		size_t copy_size = old_size < new_size ? old_size : new_size;
		memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return new_ptr;
}

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
	if (arr && *arr)
	{
		int i = 0;
		while ((*arr)[i])
		{
			free_and_null((void **) &((*arr)[i]));
			i++;
		}
		free_and_null((void **) arr);
	}
}