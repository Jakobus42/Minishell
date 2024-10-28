#include "utils/utils.h"
#include "core/tokenizer/tokenizer.h"

bool update_quote_state(char *quote_state, const char current_char)
{
	if (ft_strchr(QUOTES, current_char))
	{
		if (!*quote_state)
		{
			*quote_state = current_char;
			return true;
		}
		else if (current_char == *quote_state)
		{
			*quote_state = 0;
			return true;
		}
	}
	return false;
}