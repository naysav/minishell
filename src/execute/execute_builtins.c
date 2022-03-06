/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:17:00 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(t_token *token)
{
	if (ft_strlen(token->str) == 0)
		return (false);
	else if (ft_strncmp(token->str, "pwd", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "env", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "export", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "unset", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "echo", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "cd", ft_strlen(token->str)) == 0)
		return (true);
	else if (ft_strncmp(token->str, "exit", ft_strlen(token->str)) == 0)
		return (true);
	else
		return (false);
}

void	ft_execute_builtins(t_shell *shell, t_token *token, t_envs_lst *env)
{
	if (ft_strncmp(token->str, "pwd", ft_strlen(token->str)) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(token->str, "env", ft_strlen(token->str)) == 0)
		ft_env(shell, &env);
	else if (ft_strncmp(token->str, "export", ft_strlen(token->str)) == 0)
		ft_export(shell, &env, token->next);
	else if (ft_strncmp(token->str, "unset", ft_strlen(token->str)) == 0)
		ft_unset(shell, &env, token->next);
	else if (ft_strncmp(token->str, "echo", ft_strlen(token->str)) == 0)
		ft_echo(shell, token->next);
	else if (ft_strncmp(token->str, "cd", ft_strlen(token->str)) == 0)
		ft_cd(shell, &env, token->next);
	else if (ft_strncmp(token->str, "exit", ft_strlen(token->str)) == 0)
		ft_exit(shell, &env, token->next);
}
