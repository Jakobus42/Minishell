#include "core/parser/parser.h"

static bool initialize_command(t_pipeline *pipeline, t_command **command)
{
	*command = ft_calloc(sizeof(t_command), 1);
	if (!*command)
		return true;
	if (ft_lstnew_add_back(&pipeline->commands, *command))
		return (free(*command), true);
	return false;
}

static bool process_pipe(const t_list **tokens, t_token **token, t_parser_state *state)
{
	*state = STATE_PIPE;
	*tokens = (*tokens)->next;
	if (!*tokens)
	{
		printf("unexpected end of pipeline\n");
		return true;
	}
	*token = (t_token *) (*tokens)->content;
	return false;
}

bool parse_tokens(const t_list *tokens, t_pipeline *pipeline)
{
	t_command     *command = NULL;
	t_parser_state state = STATE_START;
	t_token       *token = NULL;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if (tokens->next == NULL)
			state = STATE_END;
		if (!is_expected_token(state, token->type))
			return log_syntax_error(token, state);
		if (!command || token->type == PIPE)
		{
			if (initialize_command(pipeline, &command))
				return true;
			if (token->type == PIPE && process_pipe(&tokens, &token, &state))
				return true;
		}
		if (process_token(command, token, &state))
			return true;
		tokens = tokens->next;
	}
	return false;
}
