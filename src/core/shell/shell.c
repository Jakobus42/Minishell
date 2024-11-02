/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 15:38:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/expander/expander.h"
#include "core/shell/shell.h"
#include "core/shell/signal.h"
#include <stdio.h>

void	print_welcome_ascii_art(void)
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

bool	initialize_shell(t_shell *shell, const int argc, const char **argv,
		const char **env)
{
	(void)argv;
	if (argc > 2)
	{
		log_message(LOG_ERROR, "no arguments requiered\n");
		return (1);
	}
	if (!env || (env && !*env))
	{
		log_message(LOG_FATAL, "enviorment is empty, cant start shell\n");
		return (1);
	}
	ft_bzero(shell, sizeof(t_shell));
	if (VERBOSE)
		print_welcome_ascii_art();
	shell->env = convert_env_to_list(shell, env);
	if (errno == ENOMEM)
		error_fatal(shell, "malloc", MALLOC_FAIL);
	return (0);
}

static t_list	*generate_tokens(const char *input)
{
	t_token	*token;
	t_list	*token_list;
	t_list	*node;

	token_list = NULL;
	while (true)
	{
		token = next_token(&input);
		if (!token)
			break ;
		log_message(LOG_INFO, "registered token: `%s` of type: %s\n",
			token->value, token_type_to_str(token->type));
		node = ft_lstnew(token);
		if (!node)
			return (free(token->value), free(token), token_list);
		ft_lstadd_back(&token_list, node);
	}
	return (token_list);
}

static uint8_t	setup_pipeline(t_shell *shell, const char *input)
{
	shell->tokens = generate_tokens(input);
	open_heredocs(shell, shell->tokens);
	if (validate_token_sequence(shell->tokens))
		return (2);
	expand_tokens(shell, &shell->tokens);
	if (!shell->tokens)
		return (0);
	if (parse_tokens(shell, shell->tokens))
		return (2);
	return (0);
}

void	run_shell(t_shell *shell)
{
	while (true)
	{
		handle_signal(shell, MODE_INTERACTIVE);
		shell->input = readline(GREEN "shell<3 " RESET);
		if (!shell->input)
			error_fatal(shell, NULL, shell->error_code);
		handle_signal(shell, MODE_NON_INTERACTIVE);
		if (*shell->input)
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
