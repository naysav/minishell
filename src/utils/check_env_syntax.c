/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:25:21 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 16:23:07 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	starts_with_correct_char(char *key)
{
	if (key && (ft_isalpha(key[0]) || key[0] == '_'))
		return (true);
	else
		return (false);
}

static bool	valid_chars(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0' && key[i] != '=')
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	check_env_syntax(char *key)
{
	if (!starts_with_correct_char(key) || !valid_chars(key))
		return (false);
	else
		return (true);
}
