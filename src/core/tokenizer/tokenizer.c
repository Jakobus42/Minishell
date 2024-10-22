#include "../../../include/core/tokenizer/tokenizer.h"
#include "../../../include/core/shell.h"

void generate_tokens(t_shell *shell, const char *input)
{
	while (*input)
	{
		skip_whitespaces(&input); // TODO: somehow put this in next_token :c
		if (!*input)
			break;
		t_token *token = next_token(&input);
		if (!token)
			error_exit(shell, "", ERROR_GENERAL);
		t_list *node = ft_lstnew(token);
		ft_lstadd_back(&shell->tokens.data, node);
	}
}