/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:57:50 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 16:23:07 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_unset(t_shell *shell, t_envs_lst **envs, t_token *token)
{
	while (token && token->type == ARG)
	{
		if (!check_env_syntax(token->str))
		{
			shell->exit_status = ERROR_MAIN;
			ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
			ft_putstr_fd(": unset: `", STDERR_FILENO);
			ft_putstr_fd(token->str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		else
		{
			ft_remove_env_var(envs, token->str);
			shell->exit_status = ERROR_NON;
		}
		token = token->next;
	}
	shell->exit_status = ERROR_NON;
}
