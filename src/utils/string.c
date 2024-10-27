#include "utils/utils.h"

void skip_whitespaces(const char **str)
{
	while (**str && ft_strchr(" \t\n\r\v\f", **str))
	{
		(*str)++;
	}
}

const char *skip_quotes(const char *input, const char quote)
{
	if (quote)
	{
		input++;
		while (*input && *input != quote)
			input++;
		if (*input == quote)
			input++;
	}
	return input;
}

char *ft_strjoin_null(char const *s1, char const *s2)
{
	size_t i;
	char  *str;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *) s2));
	if (!s2)
		return (ft_strdup((char *) s1));
	if (s1 || s2)
		i = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, i + 1);
	ft_strlcat(str, s2, i + 1);
	return (str);
}