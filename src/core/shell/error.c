/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 15:25:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/shell/shell.h"

void	error_fatal(t_shell *shell, const char *msg, uint8_t error_code)
{
	ft_lstclear(&shell->env, &free_env);
	if (msg)
		log_message(LOG_FATAL, "%s: %s", msg, strerror(errno));
	rl_clear_history();
	reset_shell(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(error_code);
}
