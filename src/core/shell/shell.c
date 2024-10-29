#include "core/shell/shell.h"
#include "core/expander/expander.h"

#include <stdio.h>

void print_welcome_ascii_art()
{
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⡄⠀⠀⠀⠀⠀⠀⠀⣠⣄⠀⠀⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⡇⠀⠀⠀⠀⠀⠀⢰⣿⣿⡄⠀⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⣿⣿⣿⡇⠀⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣿⣿⣿⣯⣤⣤⣤⣀⣀⣸⣿⣿⣿⡇⠀⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀%s\n", YELLOW, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⡏⢠⡦⠈⣿⣿⣿⣿⣿⣿⠟⠛⢻⣷⡄⠀⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣦⣤⣾⣿⣿⣿⣿⣿⣿⠀⠿⢀⣿⣷⠄⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⢠⣄⠀⠀⠀⣼⣿⡆⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⡇⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⢸⣿⣷⣄⢀⣿⣿⣿⠀⠀⠀⢀⣿⣿⣿⠿⠋⠉⠁⠀⠀⠈⠉⠉⠻⢿⣿⣿⣿⣿⣷⠀⠀⠀%s\n", GREEN, RESET);
	printf("%s⠀⣿⣿⠿⣿⣿⡿⣛⢷⠀⠀⢸⣿⣿⠏⢀⣤⣄⠀⣠⣤⡄⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣦⣄⠀%s\n", YELLOW, RESET);
	printf("%s⠀⣿⣇⣀⣽⣿⣷⣤⣾⣧⠀⠘⣿⠏⠀⠛⠋⠙⠀⠛⠙⠛⠀⠾⠿⣷⢸⣿⣿⣿⣿⣿⣿⣿⡇%s\n", GREEN, RESET);
	printf("%s⢠⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⡿⣿⣿⣿⣿⣿⡇%s\n", GREEN, RESET);
	printf("%s⠘⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠁%s\n", GREEN, RESET);
	printf("%s⠀⢻⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠈⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⡿⠋⠀⠀%s\n", YELLOW, RESET);
	printf("%s⠀⠀⠉⠛⠛⠛⠛⠛⠛⠁⠀⠀⠀⠀⠀⠘⠻⢲⠦⠤⠤⠀⠀⠀⠀⣤⢴⡿⠟⠁⠀⠀⠀⠀%s\n", GREEN, RESET);
}

void initialize_shell(t_shell *shell, const char **env)
{
	ft_bzero(shell, sizeof(t_shell));
	if (VERBOSE)
		print_welcome_ascii_art();
	shell->env = convert_env_to_list(env);
	if (errno == ENOMEM)
		error_fatal(shell, "malloc", MALLOC_FAIL);
}

static t_list *generate_tokens(const char *input)
{
	t_token *token;
	t_list  *token_list = NULL;

	while ((token = next_token(&input)))
	{
		log_message(LOG_INFO, "registered token: `%s` of type: %s\n", token->value,
		            token_type_to_str(token->type));
		t_list *node = ft_lstnew(token);
		if (!node)
			return (free(token->value), free(token), token_list);
		ft_lstadd_back(&token_list, node);
	}
	return token_list;
}

bool scan_for_unclosed_quotes(t_list *tokens)
{
	char quote_state = 0;
	while (tokens)
	{
		const t_token *token = (t_token *) tokens->content;
		const char    *token_value = token->value;
		while (*token_value)
			update_quote_state(&quote_state, *token_value++);
		if (quote_state != 0)
		{
			log_message(LOG_ERROR, "detected unclosed quote in token: `%s` of type: %s\n",
			            token->value, token_type_to_str((token->type)));
			return true;
		}
		tokens = tokens->next;
	}
	return false;
}

uint8_t setup_pipeline(t_shell *shell, const char *input)
{
	shell->tokens = generate_tokens(input);
	if (scan_for_unclosed_quotes(shell->tokens))
		return 1; // TODO define error codes
	expand_tokens(shell, &shell->tokens);
	if (!shell->tokens)
		return 0;
	if (parse_tokens(shell, shell->tokens))
		return 2;
	shell->error_code = 0;
	return 0;
}