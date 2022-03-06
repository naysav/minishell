/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:18:59 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:46:32 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	size_dollar(char *str, int i)
{
	static char	*pool_symbols = "\"\'$/-*#=\t: ";
	int			size;

	size = 0;
	if (str[i] == '$')
		i++;
	while (ft_strchr_bo(pool_symbols, str[i]) == false && str[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

static char	*key_dollar(char *str, int size, int i)
{
	char	*name_variable;
	int		j;

	name_variable = (char *)ft_calloc(size + 1, sizeof(char));
	if (name_variable == NULL)
		return (NULL);
	j = 0;
	if (str[i] == '$')
		i++;
	while (str[i] != '\0' && j < size)
		name_variable[j++] = str[i++];
	name_variable[j] = '\0';
	return (name_variable);
}

static char	*value_dollar(t_envs_lst *env, char *key)
{
	char	*tmp;
	char	*value;

	if (find_env_variable(&env, key) != NULL)
	{
		tmp = find_env_variable(&env, key);
		value = ft_strdup(tmp);
		if (value == NULL)
			error(ERROR_MALLOC);
		tmp = value;
		value = ft_strtrim(value, "\'\"");
		if (value == NULL)
			error(ERROR_MALLOC);
		free(tmp);
	}
	else
	{
		value = ft_strdup("");
		if (value == NULL)
			error(ERROR_MALLOC);
	}
	return (value);
}

char	*ft_parse_dollar(t_envs_lst *env, t_parse *parse, char *str,
						t_shell *shell)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!ft_isalpha(str[parse->i + 1]) && str[parse->i + 1] != '_')
	{
		parse->i++;
		if (str[parse->i] == '?')
			return (ft_itoa(shell->exit_status));
		return (ft_strdup("$"));
	}
	parse->size = size_dollar(str, parse->i);
	key = key_dollar(str, parse->size, parse->i);
	if (key == NULL)
		return (NULL);
	value = value_dollar(env, key);
	if (key)
		free(key);
	if (value == NULL)
		return (NULL);
	parse->i += parse->size;
	return (value);
}

bool	ft_search_dollar(char *str)
{
	int			i;
	bool		root;
	t_quotes	quotes;

	quotes = ft_quotes_init();
	i = -1;
	root = false;
	while (str[++i])
	{
		ft_set_quote_status(&quotes, str[i]);
		if (str[i] == '$' && ft_is_whitespace(str[i + 1]) == false
			&& quotes.solo == false)
		{
			root = true;
			break ;
		}
	}
	while (root && ft_strchr_bo("\'\"", str[--i]))
		;
	while (root && ft_is_whitespace(str[--i]))
		;
	if (root && str[i] && i > 0 && str[i] == '<' && str[i - 1] == '<')
		root = false;
	return (root);
}
