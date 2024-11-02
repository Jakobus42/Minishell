/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/shell/shell.h"
#include "utils/utils.h"

void	debug_print_env(t_list *env)
{
	t_pair	*pair;

	while (env)
	{
		pair = (t_pair *)env->content;
		if (pair)
			printf("Key: %s, Value: %s\n", pair->key, pair->value);
		else
			printf("Env content is NULL\n");
		env = env->next;
	}
}

void	debug_print_redirections(t_list *redir)
{
	t_redirection	*redirection;

	if (!redir)
		return ;
	printf("\n");
	while (redir)
	{
		redirection = (t_redirection *)redir->content;
		if (redirection)
			printf("filename: %s, type: %s\n", redirection->file_name,
				token_type_to_str(redirection->type));
		else
			printf("NULL\n");
		redir = redir->next;
	}
	printf("\n");
}

static void	print_args_debug(char **args, int argc)
{
	int	j;

	j = 0;
	while (j < argc)
	{
		printf("command->args[%d]: %s\n", j, args[j]);
		j++;
	}
}

void	debug_print_pipeline(t_pipeline *pipeline)
{
	int			i;
	t_list		*commands;
	t_command	*command;

	i = 0;
	commands = pipeline->commands;
	if (!commands)
		return ;
	printf("\n");
	while (commands)
	{
		command = (t_command *)commands->content;
		if (!command)
			return ;
		printf("----- %s%d%s -----\n", GREEN "COMMAND[", i, "]" RESET);
		printf("command->argc: %d\n", command->argc);
		if (command->args)
			print_args_debug(command->args, command->argc);
		else
			printf("NULL\n");
		debug_print_redirections(command->redirs);
		commands = commands->next;
		i++;
	}
	printf("\n");
}
