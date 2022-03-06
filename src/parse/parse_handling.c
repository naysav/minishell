/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:13 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	process_pars_exit(char **com, t_shell *shell, bool status)
{
	int		i;

	i = -1;
	if (com)
	{
		while (com[++i])
			free(com[i]);
		free(com);
	}
	if (status)
		return (true);
	shell->exit_status = ERROR_MALLOC;
	return (false);
}

static bool	process_parsing(t_shell *shell, t_parse *parse,
							t_envs_lst *env, char *str)
{
	char	**com;

	com = ft_split_command(env, str, parse, shell);
	if (com == NULL && parse->flag == false)
		return (false);
	parse->pipe = 0;
	parse->begin_str = parse->i + 1;
	if (parse->flag == true)
		return (true);
	if (ft_process_tokening(shell, com, env) == false)
		return (process_pars_exit(com, shell, false));
	return (process_pars_exit(com, shell, true));
}

int	ft_parse_handling(t_shell *shell, t_envs_lst *env, char *str)
{
	t_parse	parse_data;

	parse_data = ft_parse_init();
	while (str[parse_data.i])
	{
		ft_set_quote_status(&parse_data.quotes, str[parse_data.i]);
		if (str[parse_data.i] == '\0' || (str[parse_data.i] == ';'
				&& ft_is_outside_quotes(&parse_data.quotes) == true)
			|| str[parse_data.i + 1] == '\0')
		{
			parse_data.flag = false;
			if (process_parsing(shell, &parse_data, env, str) == false)
				return (false);
		}
		if (str[parse_data.i] == '|'
			&& ft_is_outside_quotes(&parse_data.quotes) == true)
			parse_data.pipe++;
		if (str[parse_data.i] == '\\' && parse_data.quotes.dble == true)
			parse_data.i += 2;
		else if (str[parse_data.i] != '\0')
			parse_data.i++;
	}
	return (true);
}
