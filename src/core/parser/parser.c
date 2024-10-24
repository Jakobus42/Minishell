#include "core/parser/parser.h"

static size_t count_args(const t_list *tokens)
{
	size_t       count = 0;
	t_token     *token;
	t_token_type prv_token_type = NONE;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if (token->type == PIPE)
			break;
		if (!is_redirect(prv_token_type) && token->type == WORD)
			count++;
		prv_token_type = token->type;
		tokens = tokens->next;
	}
	return count;
}

static bool construct_command(t_pipeline *pipeline, t_command **command, size_t arguments)
{
	*command = ft_calloc(sizeof(t_command), 1);
	if (!*command)
		return true;
	printf("%ld\n", arguments);
	(*command)->args = malloc(sizeof(char *) * arguments + 1);
	if (!(*command)->args)
	{
		return (free(*command), true);
	}
	(*command)->args[arguments] = NULL;
	if (ft_lstnew_add_back(&pipeline->commands, *command))
		return (free((*command)->args), free(*command), true);
	return false;
}

bool parse_tokens(const t_list *tokens, t_pipeline *pipeline)
{
	t_command *command = NULL;
	t_token   *token = NULL;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if (!command || token->type == PIPE)
		{
			if (construct_command(pipeline, &command, count_args(tokens)))
				return true;
			if (token->type == PIPE)
			{
				tokens = tokens->next;
				token = (t_token *) tokens->content;
			}
		}
		if (process_token(command, token))
			return true;
		tokens = tokens->next;
	}
	return false;
}
