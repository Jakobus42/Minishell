#include "../../include/utils/utils.h"

void skip_whitespaces(const char **str)
{
	while (**str && ft_strchr(" \t\n\r\v\f", **str))
	{
		(*str)++;
	}
}