/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addon_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:18:24 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	expand_additional(char *str, int quotes[2])
{
	char	*new;
	int		j;
	int		i;

	j = 0;
	i = -1;
	new = (char *)malloc(sizeof(char)
			* (ft_strlen(str) - quotes[0] - quotes[1] + 1));
	if (new == NULL)
		return (false);
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			new[j++] = str[i];
	new[j] = '\0';
	free(str);
	str = ft_strdup(new);
	if (str == NULL)
	{
		free(new);
		return (false);
	}
	free(new);
	return (true);
}

static bool	expand_command(char *str)
{
	int			i;
	int			quotes[2];

	i = -1;
	ft_memset(quotes, 0, sizeof(int) * 2);
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes[0]++;
		else if (str[i] == '\"')
			quotes[1]++;
	}
	if ((quotes[0] > 0 && quotes[0] % 2 == 0 && quotes[1] == 0)
		|| (quotes[1] > 0 && quotes[1] % 2 == 0 && quotes[0] == 0))
	{
		if (expand_additional(str, quotes) == false)
			return (false);
	}
	return (true);
}

void	ft_addon_token(t_token *coms)
{
	while (coms)
	{
		if (coms->type == CMD && expand_command(coms->str) == false)
			error(ERROR_MALLOC);
		if (coms->type == INPUT && (!coms->prev || coms->prev->type == PIPE))
		{
			if (coms->next && coms->next->type != PIPE
				&& coms->next->next && coms->next->next->type != PIPE)
			{
				coms->next->type = ARG;
				coms->next->next->type = CMD;
			}
		}
		coms = coms->next;
	}
}
