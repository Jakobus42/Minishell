#include "core/shell/shell.h"
#include "core/shell/signal.h"
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

void    initialize_shell(t_shell *shell, const int argc, const char** argv, const char** env)
{
	(void)argc;
	(void)argv;
	ft_bzero(shell, sizeof(t_shell));
	if (VERBOSE)
		print_welcome_ascii_art();
	shell->env = convert_env_to_list(shell, env);
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

static uint8_t setup_pipeline(t_shell *shell, const char *input)
{
	shell->tokens = generate_tokens(input);
	open_heredocs(shell, shell->tokens);
	if (validate_token_sequence(shell->tokens))
		return 2;
	expand_tokens(shell, &shell->tokens);
	if (!shell->tokens)
		return 0;
	if (parse_tokens(shell, shell->tokens))
		return 2;
	return 0;
}

void    run_shell(t_shell *shell) {
	while (true)
	{
		handle_signal(shell, MODE_INTERACTIVE);
		shell->input = readline(PROMPT);
		if (!shell->input)
			error_fatal(shell, NULL, shell->error_code);
		handle_signal(shell, MODE_NON_INTERACTIVE);
		if(*shell->input)
			add_history(shell->input);
		shell->error_code = setup_pipeline(shell, shell->input);
		if (shell->error_code == 0 && shell->pipeline.commands)
		{
			if (VERBOSE)
				debug_print_pipeline(&shell->pipeline);
			execute(shell);
			if (shell->exec.exit == true)
				error_fatal(shell, NULL, shell->error_code);
		}
		if (errno)
			log_message(LOG_INFO, "errno: %d\n", errno);
		log_message(LOG_INFO, "error_code: %d\n", shell->error_code);
		reset_shell(shell);
	}
}