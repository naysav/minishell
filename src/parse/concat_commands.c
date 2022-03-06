/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:18:42 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	size_string_all(t_parse *parse, char *str, int i)
{
	int		size;

	size = 0;
	while (str[++i] != '\0')
	{
		ft_set_quote_status(&parse->quotes, str[i]);
		if (str[i] == '$' && ft_is_whitespace(str[i + 1]) == false
			&& parse->quotes.solo == false)
			return (size);
		size++;
	}
	return (size);
}

static char	*transform_to_env(t_envs_lst *env, t_parse *parse, char *str,
							t_shell *shell)
{
	char	*transform;

	transform = NULL;
	if (str[parse->i] == '$' && ft_is_whitespace(str[parse->i + 1]) == false
		&& parse->quotes.solo == false)
	{
		transform = ft_parse_dollar(env, parse, str, shell);
		if (transform == NULL)
			error(ERROR_MALLOC);
	}
	else
	{
		parse->size = size_string_all(parse, str, parse->i - 1);
		transform = ft_substr(str, parse->i, parse->size);
		if (transform == NULL)
			error(ERROR_MALLOC);
		parse->i += (parse->size - 1);
	}
	return (transform);
}

static bool	concat_cmd(char *value, char **cmd)
{
	char	*tmp;

	if (*cmd == NULL)
	{
		*cmd = ft_strdup(value);
		if (*cmd == NULL)
			error(ERROR_MALLOC);
		return (true);
	}
	tmp = ft_strdup(*cmd);
	if (tmp == NULL)
		error(ERROR_MALLOC);
	free(*cmd);
	*cmd = ft_strjoin(tmp, value);
	free(tmp);
	if (*cmd == NULL)
		error(ERROR_MALLOC);
	return (true);
}

static char	*grow_up_free(char *transform, char *cmd, t_shell *shell)
{
	shell->exit_status = ERROR_MALLOC;
	if (transform != NULL)
		free(transform);
	if (cmd != NULL)
		free(cmd);
	return (NULL);
}

char	*ft_grow_up_str(t_envs_lst *env, char *str, t_shell *shell, bool *flag)
{
	t_parse	parse;
	char	*transform;
	char	*cmd;

	parse = ft_parse_init();
	transform = NULL;
	cmd = NULL;
	while (str[parse.i] != '\0')
	{
		transform = transform_to_env(env, &parse, str, shell);
		if (transform == NULL)
			return (grow_up_free(transform, cmd, shell));
		if (concat_cmd(transform, &cmd) == false)
			return (grow_up_free(transform, cmd, shell));
		if (transform)
		{
			free(transform);
			transform = NULL;
		}
		parse.i++;
	}
	if (cmd == NULL)
		*flag = true;
	return (cmd);
}
