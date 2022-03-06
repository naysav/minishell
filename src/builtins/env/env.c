/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:56:55 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_shell *shell, t_envs_lst **envs)
{
	t_envs_lst	*curr;

	shell->exit_status = ERROR_NON;
	if (envs == NULL)
		return ;
	curr = *envs;
	while (curr != NULL)
	{
		write(STDOUT_FILENO, curr->data->key, ft_strlen(curr->data->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, curr->data->val, ft_strlen(curr->data->val));
		write(STDOUT_FILENO, "\n", 1);
		curr = curr->next;
	}
	return ;
}
