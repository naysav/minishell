/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:20:14 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	invalid_new_str(char *str, int pipe, int i)
{
	int	count_pipe;

	while (ft_is_whitespace(str[++i]))
		;
	if (i + 1 > (int)ft_strlen(str))
		return (true);
	i = -1;
	count_pipe = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '|')
			count_pipe++;
		else if (ft_is_whitespace(str[i]) == false || str[i] != '|')
			return (false);
	}
	if (count_pipe >= pipe)
		return (true);
	return (false);
}

static char	**split_exit(t_shell *shell)
{
	shell->exit_status = ERROR_MALLOC;
	return (NULL);
}

static char	*parse_command_additional(t_envs_lst *env, char *str,
									t_parse *parse, t_shell *shell)
{
	char	*str_without_space;
	char	*str_command;

	str_without_space = ft_trim_tabulation(str);
	if (str_without_space == NULL)
		error(ERROR_MALLOC);
	str_command = ft_grow_up_str(env, str_without_space, shell, &parse->flag);
	if (str_command == NULL && parse->flag == false)
		error(ERROR_MALLOC);
	if (invalid_new_str(str_command, parse->pipe, -1) == true)
	{
		parse->flag = true;
		free(str_command);
		str_command = NULL;
	}
	if (str_without_space)
		free(str_without_space);
	return (str_command);
}

static char	*new_split_com(char *str, t_parse *parse)
{
	char	*new;

	if (str[parse->i] != '\0')
		if (str[parse->i] != ';' && str[parse->i + 1] == '\0')
			(parse->i)++;
	if (str[parse->i] == ';' && ft_is_whitespace(str[parse->i - 1])
		&& parse->i - 2 >= 0 && ft_is_whitespace(str[parse->i - 2]))
		new = ft_substr(str, parse->begin_str, parse->i - parse->begin_str - 2);
	else if ((str[parse->i] == ';' && ft_is_whitespace(str[parse->i - 1]))
		|| (str[parse->i - 1] && ft_is_whitespace(str[parse->i - 1])
			&& str[parse->i - 2] && !ft_is_whitespace(str[parse->i - 2])
			&& str[parse->i] == '\0'))
		new = ft_substr(str, parse->begin_str, parse->i - parse->begin_str - 1);
	else
		new = ft_substr(str, parse->begin_str, parse->i - parse->begin_str);
	if (new == NULL)
		error(ERROR_MALLOC);
	return (new);
}

char	**ft_split_command(t_envs_lst *env, char *str,
						t_parse *parse, t_shell *shell)
{
	char	*new;
	char	*cmd;

	new = new_split_com(str, parse);
	if (ft_search_dollar(new) == true)
	{
		cmd = parse_command_additional(env, new, parse, shell);
		free(new);
		new = NULL;
		if ((cmd == NULL && parse->flag == false) || (parse->flag == true))
			return (split_exit(shell));
		return (ft_get_commands(cmd, parse->pipe));
	}
	return (ft_get_commands(new, parse->pipe));
}
