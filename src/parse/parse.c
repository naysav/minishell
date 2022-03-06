/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:35 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	parse_exit(t_shell *shell, char *str, int number)
{
	free(str);
	if (number == ERROR_NON)
		;
	else if (number == ERROR_MALLOC)
		shell->exit_status = ERROR_MALLOC;
	return (false);
}

bool	ft_parse(t_shell *shell, t_envs_lst *env, char *str, char *user)
{
	char	*new_str;

	if (ft_skip_tabulation(str) == true)
		return (false);
	new_str = ft_trim_tabulation(str);
	if (new_str == NULL)
		error(ERROR_MALLOC);
	if (ft_preparse(new_str, user) == false)
		return (parse_exit(shell, new_str, ERROR_NON));
	if (ft_parse_handling(shell, env, new_str) == false)
		error(ERROR_MALLOC);
	free(new_str);
	return (true);
}
