#include "core/expander/expander.h"
#include "core/shell/shell.h"

static bool update_quote_state(char *quote_state, const char current_char)
{
	if (ft_strchr(QUOTES, current_char))
	{
		if (!*quote_state)
		{
			*quote_state = current_char;
			return true;
		}
		else if (current_char == *quote_state)
		{
			*quote_state = 0;
			return true;
		}
	}
	return false;
}

static t_pair fetch_expand_data(t_shell *shell, const char **token)
{
	t_pair pair;
	int    key_size;

	if (**token == '$')
		(*token)++;
	pair.value = NULL;
	key_size = get_valid_key_size(*token);
	if (key_size > 0)
	{
		pair.key = ft_substr(*token, 0, key_size);
		if (!pair.key)
			error_fatal(shell, "ft_substr in fetch_expanded_value\n", MALLOC_FAIL);
		pair.value = get_env(shell->env, pair.key);
		*token += key_size;
	}
	return pair;
}

static int expand_variable(t_shell *shell, const char **token, char *output)
{
	t_pair pair = fetch_expand_data(shell, token);
	int    size = 0;

	if (pair.value)
	{
		size = ft_strlen(pair.value);
		if (output)
			ft_strlcpy(output, pair.value, size + 1);
	}
	free(pair.value);
	free(pair.key);
	return size;
}

// if the output is NULL this function only reads the bytes to expand and returns the size, otherwise it writes the bytes
static int process_expansion(t_shell *shell, const char *token, char *output)
{
	int  size = 0;
	char quote_state = 0;

	while (*token)
	{
		if (update_quote_state(&quote_state, *token))
			token++;
		else if (*token == '$' && quote_state != '\'')
			size += expand_variable(shell, &token, output ? &output[size] : NULL);
		else
		{
			if (output)
				output[size] = *token;
			size++;
			token++;
		}
	}
	return size;
}

char *expand_token(t_shell *shell, const char *token)
{
	const int expected_size = process_expansion(shell, token, NULL);
	char     *expanded_token = ft_calloc(sizeof(char), expected_size + 1);
	if (!expanded_token)
		error_fatal(shell, "ft_calloc in expand_token", MALLOC_FAIL);
	process_expansion(shell, token, expanded_token);
	return expanded_token;
}