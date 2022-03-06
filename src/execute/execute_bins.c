/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:16:28 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_token_len(t_token *token)
{
	int	size;

	size = 1;
	while (token && token->type == ARG)
	{
		size++;
		token = token->next;
	}
	return (size);
}

static void	handle_bin_cmd(t_shell *shell, t_token *token, t_envs_lst *env)
{
	int		size;
	int		i;
	char	**args;

	if (token->type == CMD)
		ft_update_shlvl(shell, token, &env);
	size = get_token_len(token->next);
	args = (char **) malloc(sizeof(char *) * (size + 1));
	if (args == NULL)
		error(ERROR_MALLOC);
	i = -1;
	while (++i < size)
	{
		args[i] = ft_strtrim(token->str, " ");
		if (args[i] == NULL)
			error(ERROR_MALLOC);
		token = token->next;
	}
	args[size] = NULL;
	ft_launch_execve(env, args);
}

void	ft_execute_bins(t_shell *shell, t_token *token, t_envs_lst *env)
{
	pid_t	pid;
	int		status;

	ft_set_signals(token);
	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		handle_bin_cmd(shell, token, env);
	}
	else if (pid > 0)
	{
		status = 0;
		shell->pid = pid;
		waitpid(pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
	}
	else
		error(ERROR_FORK);
}
