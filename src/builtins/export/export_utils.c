/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:57:20 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:46:32 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**sort(char **tab, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j]) + 1) > 0)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

static int	get_num_of_keys(t_envs_lst **envs)
{
	int			size;
	t_envs_lst	*curr;

	size = 0;
	curr = *envs;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	ft_free_sorted_keys(char **keys, int size)
{
	int	i;

	if (keys == NULL)
		return ;
	i = -1;
	while (++i < size)
		free(keys[i]);
	free(keys);
}

char	**ft_get_sorted_keys(t_envs_lst **envs)
{
	char		**keys;
	int			size;
	int			i;
	t_envs_lst	*curr;

	if (envs == NULL)
		return (NULL);
	size = get_num_of_keys(envs);
	keys = (char **) malloc(sizeof(char *) * (size + 1));
	if (keys == NULL)
		error(ERROR_MALLOC);
	i = -1;
	curr = *envs;
	while (++i > -1 && curr)
	{
		keys[i] = ft_strjoin(curr->data->key, "");
		if (keys[i] == NULL)
			error(ERROR_MALLOC);
		curr = curr->next;
	}
	keys[i] = NULL;
	return (sort(keys, size));
}

void	ft_handle_export_error(t_shell *shell, t_envs_lst **envs,
	t_token *token)
{
	shell->exit_status = ERROR_MAIN;
	ft_putstr_fd(find_env_variable(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
