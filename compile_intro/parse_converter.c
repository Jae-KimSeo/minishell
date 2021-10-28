#include "minishell.h"

static char	*joinstatus(char **token, char *result)
{
	char	*status;

	*token += 2;
	status = ft_itoa(g_shell.status);
	if (status == NULL)
		return (ft_free_ret(result, NULL));
	return (ft_strjoin_free(result, status, 3));
}


/*
converter에서 setting할 것
$? : fore_ground
~. ~/ -> HOME
$환경변수 -> 값으로
export + = 이면 에러 export 인자가 2개이상-> export (cmd) arg = (앞이나 뒤가 공백이면 에러)
a="====b"
*/

//
strncmp
//
static char	*joinenv(char **token, char *result)
{
	char	*value;
	char	*key;

	if (!ft_strncmp(*token, "$?", 2))
		return (joinstatus(token, result));
	key = ft_strdup("");
	if (key == NULL)
		return (ft_free_ret(result, NULL));
	++(*token);
	while (**token && (ft_isalnum(**token) || **token == '_'))
	{
		key = ft_strappendc(key, **token);
		if (key == NULL)
			return (ft_free_ret(result, NULL));
		++(*token);
	}
	value = get_envp_value(key);
	free(key);
	if (value == NULL)
		return (NULL);
	result = ft_strjoin_free(result, value, 2);
	--(*token);
	return (result);
}

static int	init_normalize(char **token, char **result, int *flag)
{
	*flag = TK_NONE;
	if (!ft_strncmp(*token, "~/", 2) || !ft_strcmp(*token, "~"))
	{
		*result = get_envp_value("HOME");
		++(*token);
	}
	else
		*result = ft_calloc(sizeof(char), 1);
	if (*result == NULL)
		return (0);
	return (1);
}
Ï
static int	handle_flag(char *token, int *flag)
{
	if (!(*flag & ~(TK_QOUTES)) && *token == '"')
	{
		*flag ^= TK_QOUTES;
		return (1);
	}
	else if (!(*flag & ~(TK_QOUTE)) && *token == '\'')
	{
		*flag ^= TK_QOUTE;
		return (1);
	}
	return (0);
}

char	*converter(char **token, int type)
{
	int		flag;
	char	*result;

	flag = TK_NONE;
	if (!init_normalize(token, &result, &flag))
		return (NULL);
	while (**token)
	{
		if (!handle_flag(*token, &flag))
		{
			if (!(flag & ~(TK_QOUTES)) && **token == '$' && *(*token + 1) && \
				(!ft_strncmp(*token, "$?", 2) || ft_isalpha(*(*token + 1)) || \
				*(*token + 1) == '_'))
				result = joinenv(token, result);
			else
				result = ft_strappendc(result, **token);
			if (result == NULL)
				return (NULL);
		}
		++(*token);
	}
	return (result);
}*/