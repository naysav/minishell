/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:56:02 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 16:26:06 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	treatment_invalid_path(t_shell *shell, t_envs_lst **envs,
	char *path_to_go)
{
	shell->exit_status = ERROR_MAIN;
	ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(path_to_go, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

bool	treatment_empty_path(t_shell *shell, t_envs_lst **envs)
{
	char	*home_path;

	home_path = find_env_variable(envs, "HOME");
	if (home_path == NULL)
	{
		shell->exit_status = ERROR_MAIN;
		ft_putstr_fd(home_path, STDERR_FILENO);
		ft_putstr_fd(": cd: HOME not set", STDERR_FILENO);
		return (false);
	}
	else
	{
		if (chdir(home_path) == -1)
		{
			treatment_invalid_path(shell, envs, home_path);
			return (false);
		}
		return (true);
	}
}
