/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:05:49 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:46:32 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_path_dirs(char *cmd, t_envs_lst *env)
{
	char	**paths;
	char	*path;
	char	*cmd_with_slash;
	int		i;

	paths = ft_split(find_env_variable(&env, "PATH"), ':');
	cmd_with_slash = ft_strjoin("/", cmd);
	if ((paths == NULL && errno) || cmd_with_slash == NULL)
		error(ERROR_MALLOC);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], cmd_with_slash);
		if (path == NULL)
			error(ERROR_MALLOC);
		if (access(path, S_IXUSR) >= 0)
		{
			ft_free_paths(paths, cmd_with_slash);
			return (path);
		}
		free(path);
	}
	ft_free_paths(paths, cmd_with_slash);
	return (NULL);
}

static char	*get_full_path(char *cmd, t_envs_lst *env)
{
	char	*path;

	if (ft_strlen(cmd) == 0)
		return (NULL);
	path = check_path_dirs(cmd, env);
	if (path != NULL)
		return (path);
	else if (access(cmd, S_IXUSR) >= 0)
		return (cmd);
	else
		return (NULL);
}

static char	*parse_cmd(char *buf, t_envs_lst *env)
{
	char	*full_path;

	full_path = get_full_path(buf, env);
	if (ft_strlen(buf) == 0
		|| (full_path == NULL && find_env_variable(&env, "PATH") != NULL))
	{
		ft_putstr_fd(find_env_variable(&env, "USER"), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(buf, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else if (full_path == NULL)
	{
		ft_putstr_fd(find_env_variable(&env, "USER"), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(buf, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (full_path);
}

void	ft_launch_execve(t_envs_lst *env, char **args)
{
	char	*full_path;
	char	**envs;

	full_path = parse_cmd(args[0], env);
	envs = ft_parse_env_to_arr(&env);
	if (full_path != NULL)
	{
		if (execve(full_path, args, envs) == -1)
			error(ERROR_EXECVE);
	}
	else
		exit(ERROR_WRONG_CMD);
}

void	ft_set_signals(t_token *token)
{
	if (token->type == CMD && ft_strnstr(token->str, "minishell",
			ft_strlen(token->str)))
	{
		signal(SIGQUIT, ft_sig_ignore);
		signal(SIGINT, ft_sig_ignore);
	}
	if (token->type == CMD && ft_strnstr(token->str, "cat",
			ft_strlen(token->str)))
	{
		signal(SIGINT, ft_c_handle_fork);
		signal(SIGQUIT, ft_slash_handle_fork);
	}
}
