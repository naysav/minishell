/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:57:08 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:46:32 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_argc(t_token *token)
{
	int	size;

	size = 0;
	while (token && token->type == ARG)
	{
		size++;
		token = token->next;
	}
	return (size);
}

static bool	is_numeric(char *status)
{
	int	i;

	i = 0;
	if (status[i] == '+' || status[i] == '-')
		i++;
	if (status[i] == '\0')
		return (false);
	while (status[i] != '\0')
	{
		if (!(status[i] >= '0' && status[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_shell *shell, t_envs_lst **envs, t_token *token)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (token && token->str && !is_numeric(token->str))
	{
		ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(token->str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(ERROR_EXIT);
	}
	else if (get_argc(token) > 1)
	{
		ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = ERROR_NON;
	}
	else if (!token)
		exit(ERROR_NON);
	else
		exit(ft_atoi(token->str) % 256);
}
