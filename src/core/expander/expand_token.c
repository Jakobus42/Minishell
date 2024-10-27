#include "core/expander/expander.h"
#include "core/shell/shell.h"

// TODO: maybe consider a buffer and realloc

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

static char *fetch_expand_value(t_shell *shell, const char **token)
{
	t_pair pair;
	int    key_size;

	key_size = get_valid_key_size(*token);
	pair.key = ft_substr(*token, 0, key_size);
	if (!pair.key)
		error_fatal(shell, "ft_substr in fetch_expanded_value\n", MALLOC_FAIL);
	*token += key_size;
	pair.value = get_env(shell->env, pair.key);
	free(pair.key);
	return pair.value;
}

static char *fetch_exit_code(t_shell *shell, const char **token)
{
	char *value;

	value = ft_itoa(shell->error_code);
	if (!value)
		error_fatal(shell, "ft_itoa in fetch_expanded_value\n", MALLOC_FAIL);
	(*token)++;
	return value;
}

static int expand_variable(t_shell *shell, const char **token, char *output)
{
	char *value;
	int   size;

	while (*token && **token == '$')
		(*token)++;
	if (**token == '?')
		value = fetch_exit_code(shell, token);
	else
		value = fetch_expand_value(shell, token);
	if (!value)
		return 0;
	size = ft_strlen(value);
	if (output)
		ft_strlcpy(output, value, size + 1);
	free(value);
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
		else if (quote_state != '\'' && *token == '$' && (get_valid_key_size((token + 1)) > 0 || *(token + 1) == '?'))
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