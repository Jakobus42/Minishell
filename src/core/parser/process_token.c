#include "core/parser/parser.h"
#include "core/shell.h"

// TODO: free on malloc fail
// TODO: refactor

bool process_redirect(t_command *command, const t_token *token, t_token_type redirect_type)
{
	printf("[DEBUG] ENTERD process_redirect: \n");
	t_redirection *redirect = ft_calloc(sizeof(t_redirection), 1);
	if (!redirect)
		return true;
	redirect->file_name = ft_strdup(token->value);
	printf("[DEBUG] filename: %s \n", redirect->file_name);
	if (!redirect->file_name)
		return (free(redirect), true);
	redirect->type = redirect_type;
	if (ft_lstnew_add_back(&command->redir, redirect))
		return (free(redirect->file_name), free(redirect), true);
	return false;
}

static bool process_word(t_command *command, const t_token *token)
{
	printf("[DEBUG] ENTERD process_word: \n");
	static int argument_count = 0;
	printf("[DEBUG] argument_count: %d\n", argument_count);
	printf("[DEBUG] Type: %s\n", token_type_to_str(token->type));
	command->args[argument_count] = ft_strdup(token->value);
	printf("[DEBUG] command->args[%d]: %s\n", argument_count, command->args[argument_count]);
	if (!command->args[argument_count])
		return true;
	if (++argument_count >= command->argc)
		argument_count = 0;
	return false;
}

bool process_token(t_command *command, const t_token *token, t_token_type prv_token_type)
{
	if (token->type != WORD)
		return false;
	printf("[DEBUG] prv_token_type: %s\n", token_type_to_str(token->type));
	if (is_redirect(prv_token_type))
		return process_redirect(command, token, prv_token_type);
	return process_word(command, token);
}
