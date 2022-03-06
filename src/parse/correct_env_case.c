/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_env_case.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:18:48 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_lower(char *str)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * 4);
	if (new_str == NULL)
		error(ERROR_MALLOC);
	new_str[3] = '\0';
	i = 0;
	while (*str)
	{
		if (ft_isalpha(*str))
			new_str[i] = ft_tolower(*str);
		else
			new_str[i] = *str;
		i++;
		str++;
	}
	return (new_str);
}

static bool	check_env_registr(char *str)
{
	char	*new_str;

	if (str == NULL || ft_strlen(str) != 3)
		return (false);
	new_str = str_lower(str);
	if (new_str == NULL)
		return (false);
	if (ft_strncmp(new_str, "env", 3) != 0)
	{
		free(new_str);
		return (false);
	}
	free(new_str);
	return (true);
}

static bool	check_env_around(char *left, char *right)
{
	if (left)
	{
		while (*left)
		{
			if (ft_strchr_bo("<>|;", *left))
			{
				left++;
				continue ;
			}
			return (false);
		}
	}
	if (right)
	{
		while (*right)
		{
			if (ft_strchr_bo("<>|;", *right))
			{
				right++;
				continue ;
			}
			return (false);
		}
	}
	return (true);
}

void	ft_low_up_token(char **coms)
{
	int	i;

	i = -1;
	while (coms[++i])
	{
		if ((i == 0 && check_env_registr(coms[i]))
			|| (coms[i + 1] == NULL
				&& check_env_registr(coms[i])
				&& check_env_around(coms[i - 1], NULL))
			|| (i != 0 && coms[i + 1] != NULL
				&& check_env_registr(coms[i])
				&& check_env_around(coms[i - 1], coms[i + 1])))
		{
			free(coms[i]);
			coms[i] = NULL;
			coms[i] = ft_strdup("env");
			if (coms[i] == NULL)
				error(ERROR_MALLOC);
		}
	}
}
