#ifndef ENV_H
#define ENV_H

#include "utils/utils.h"
#include "libft/libft.h"

typedef struct s_pair
{
	char *key;
	char *value;
} t_pair;

typedef struct s_env
{
	t_list *data;
} t_env;


#endif // ENV_H