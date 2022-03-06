/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:07 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	fill_env_array(t_envs_lst **envs, char **parsed_envs)
{
	int			i;
	t_envs_lst	*curr;
	char		*key;
	char		*env_line;

	i = -1;
	curr = *envs;
	while (++i > -1 && curr != NULL)
	{
		key = ft_strjoin(curr->data->key, "=");
		if (key == NULL)
			error(ERROR_MALLOC);
		env_line = ft_strjoin(key, curr->data->val);
		if (env_line == NULL)
			error(ERROR_MALLOC);
		parsed_envs[i] = env_line;
		curr = curr->next;
	}
	parsed_envs[i] = NULL;
}

char	**ft_parse_env_to_arr(t_envs_lst **envs)
{
	int			i;
	t_envs_lst	*curr;
	char		**parsed_envs;

	if (envs == NULL)
		return (NULL);
	curr = *envs;
	i = -1;
	while (++i > -1 && curr != NULL)
		curr = curr->next;
	parsed_envs = (char **) malloc(sizeof(char *) * (i + 1));
	if (parsed_envs == NULL)
		error(ERROR_MALLOC);
	fill_env_array(envs, parsed_envs);
	return (parsed_envs);
}

void	ft_parse_envs_to_lst(t_envs_lst **envs, char **env)
{
	int	i;

	if (env == NULL)
		return ;
	i = 0;
	while (env[i])
		ft_add_env_var(envs, env[i++]);
}
