/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:00 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:01 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/parser/parser.h"
#include "core/shell/shell.h"

static size_t	count_args(const t_list *tokens)
{
	size_t			count;
	t_token			*token;
	t_token_type	prv_token_type;

	count = 0;
	prv_token_type = NONE;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == PIPE)
			break ;
		if (!is_redirect(prv_token_type) && token->type == WORD)
			count++;
		prv_token_type = token->type;
		tokens = tokens->next;
	}
	return (count);
}

static t_command	*appd_new_cmd_to_pipeln(t_shell *shell,
		const t_list *tokens)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		error_fatal(shell, "ft_calloc in construct_command", MALLOC_FAIL);
	command->argc = count_args(tokens);
	command->args = ft_calloc(sizeof(char *), (command->argc + 1));
	if (!command->args)
	{
		free(command);
		error_fatal(shell, "ft_calloc in construct_command", MALLOC_FAIL);
	}
	shell->pipeline.num_commands++;
	if (ft_lstnew_add_back(&shell->pipeline.commands, command))
		error_fatal(shell, "ft_lstnew_add_back in append_command_to_pipeline",
			MALLOC_FAIL);
	return (command);
}

bool	parse_tokens(t_shell *shell, const t_list *tokens)
{
	t_command		*command;
	t_token_type	prv_token_type;
	t_token			*token;

	command = NULL;
	prv_token_type = NONE;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == PIPE)
		{
			tokens = tokens->next;
			if (!tokens)
				break ;
			token = tokens->content;
			command = NULL;
		}
		if (!command)
			command = appd_new_cmd_to_pipeln(shell, tokens);
		process_token(shell, command, token, prv_token_type);
		prv_token_type = token->type;
		if (tokens)
			tokens = tokens->next;
	}
	return (false);
}
