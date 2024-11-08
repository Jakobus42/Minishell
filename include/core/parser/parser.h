/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:46:05 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:46:06 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core/error.h"
# include "core/tokenizer/tokenizer.h"
# include "libft/libft.h"
# include "utils/logger.h"

# define HEREDOC_FILENAME_LENGTH 20

typedef struct s_redirection
{
	t_token_type	type;
	char			*file_name;
}					t_redirection;

typedef struct s_command
{
	t_list			*redirs;
	char			**args;
	int				argc;
}					t_command;

typedef struct s_pipeline
{
	t_list			*commands;
	int				num_commands;
}					t_pipeline;

// -- parser.c --
bool				parse_tokens(t_shell *shell, const t_list *tokens);

// -- process_token.c --
void				process_token(t_shell *shell, t_command *command,
						const t_token *token, t_token_type prv_token_type);

// -- syntax.c --
bool				validate_token_sequence(const t_list *tokens);

// -- heredoc.c --
void				open_heredocs(t_shell *shell, t_list *tokens);

#endif // PARSER_H