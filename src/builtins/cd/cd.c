/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:55:50 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 16:26:06 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	update_old_path(t_shell *shell, t_envs_lst **envs, char *old_path)
{
	t_token		new_token;

	ft_remove_env_var(envs, "OLDPWD");
	new_token.str = ft_strjoin("OLDPWD=", old_path);
	if (new_token.str == NULL)
		error(ERROR_MALLOC);
	new_token.next = NULL;
	new_token.prev = NULL;
	new_token.type = ARG;
	ft_export(shell, envs, &new_token);
	free(new_token.str);
}

static void	update_new_path(t_shell *shell, t_envs_lst **envs, char *new_path)
{
	t_token		new_token;

	ft_remove_env_var(envs, "PWD");
	new_token.str = ft_strjoin("PWD=", new_path);
	if (new_token.str == NULL)
		error(ERROR_MALLOC);
	new_token.next = NULL;
	new_token.prev = NULL;
	new_token.type = ARG;
	new_token.type = ARG;
	ft_export(shell, envs, &new_token);
	free(new_token.str);
}

static void	handle_invalid_path(t_shell *shell, t_envs_lst **envs,
	char *path_to_go)
{
	shell->exit_status = ERROR_MAIN;
	ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(path_to_go, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

static void	update_paths(t_shell *shell, t_envs_lst **envs,
	char *old_path, char *new_path)
{
	update_old_path(shell, envs, old_path);
	update_new_path(shell, envs, new_path);
}

void	ft_cd(t_shell *shell, t_envs_lst **envs, t_token *token)
{
	char	old_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	char	*status;

	status = getcwd(old_path, PATH_MAX + 1);
	if (status == NULL)
		error(ERROR_PATH);
	if (token == NULL)
	{
		if (treatment_empty_path(shell, envs) == false)
			return ;
	}
	else
	{
		if (chdir(token->str) == -1)
			return (handle_invalid_path(shell, envs, token->str));
	}
	status = getcwd(new_path, PATH_MAX + 1);
	if (status == NULL)
		error(ERROR_PATH);
	update_paths(shell, envs, old_path, new_path);
	shell->exit_status = ERROR_NON;
}
