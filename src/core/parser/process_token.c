#include "../../../include/core/parser/parser.h"

static bool is_word(const t_token_type type)
{
	return type == WORD || type == DQ_WORD || type == SQ_WORD;
}

static bool is_redirect(const t_token_type type)
{
	return type == REDIRECT_APPEND || type == REDIRECT_OUT || type == REDIRECT_IN || type == HEREDOC;
}

static void process_word(t_command *command, const t_token *token)
{ // TODO MALLOC EROORS AHHH
	command->args = NULL;
	if (!command->cmd)
	{
		command->cmd = ft_strdup(token->value);
	}
	else
	{
		// command->args++ = ft_strdup(token->value); //TODO: realloc ig???? :c
	}
}

static void process_operator(t_command *command, const t_token *token)
{ // TODO MALLOC EROORS AHHH
	t_redirection *redir = ft_calloc(sizeof(t_redirection), 1);
	redir->file_name = ft_strdup(token->value);
	redir->type = token->type;
	t_list *node = ft_lstnew(redir);
	ft_lstadd_back(&command->redir, node);
}

bool process_token(t_command *command, const t_token *token)
{
	if (is_word(token->type))
	{
		process_word(command, token);
	}
	else if (is_redirect(token->type))
	{
		process_operator(command, token);
	}
	else
	{
		return true;
	}
	return false;
}