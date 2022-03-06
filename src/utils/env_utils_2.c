/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:26:32 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:46:32 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env_variable(t_envs_lst **envs, char *key)
{
	t_envs_lst	*curr;

	if (envs == NULL || *envs == NULL || key == NULL)
		return (NULL);
	curr = *envs;
	while (curr)
	{
		if (ft_strncmp(curr->data->key, key,
				ft_strlen(curr->data->key)) == 0)
			return (curr->data->val);
		curr = curr->next;
	}
	return (NULL);
}

void	ft_free_envs(t_envs_lst **envs)
{
	t_envs_lst	*tmp;

	while (envs && *envs)
	{
		tmp = (*envs)->next;
		ft_remove_env_var(envs, (*envs)->data->key);
		*envs = tmp;
	}
}

void	ft_update_shlvl(t_shell *shell, t_token *token, t_envs_lst **env)
{
	char	*line;
	char	*lvl;

	if (ft_strnstr(token->str, "minishell", ft_strlen(token->str)) != NULL)
	{
		shell->shlvl++;
		lvl = ft_itoa(shell->shlvl);
		if (lvl == NULL)
			error(ERROR_MALLOC);
		line = ft_strjoin("SHLVL=", ft_itoa(shell->shlvl));
		if (line == NULL)
			error(ERROR_MALLOC);
		ft_remove_env_var(env, "SHLVL");
		ft_add_env_var(env, line);
		free(line);
		free(lvl);
	}
}
