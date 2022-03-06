/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:18:53 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**free_commands(char **coms)
{
	int	i;

	i = -1;
	if (coms != NULL)
	{
		while (coms[++i])
			free(coms[i]);
		free(coms);
	}
	return (NULL);
}

static char	**one_command(char *str)
{
	char	**com;

	com = (char **)ft_calloc(2, sizeof(char *));
	if (com == NULL)
		error(ERROR_MALLOC);
	com[0] = ft_strdup(str);
	if (com[0] == NULL)
		error(ERROR_MALLOC);
	com[1] = NULL;
	return (com);
}

static char	*take_command(t_parse *parse, char *str)
{
	char	*command;

	command = ft_substr(str, parse->begin_str, parse->i - parse->begin_str + 1);
	if (command == NULL)
		error(ERROR_MALLOC);
	parse->begin_str = parse->i + 1;
	while (ft_is_whitespace(str[parse->begin_str]) == true
		&& parse->quotes.dble == false && parse->quotes.solo == false)
		parse->begin_str++;
	return (command);
}

static char	**more_commands(char *str, int pipe)
{
	char	**coms;
	t_parse	parse;
	int		j;

	parse = ft_parse_init();
	coms = (char **)ft_calloc(pipe + 2, sizeof(char *));
	if (coms == NULL)
		error(ERROR_MALLOC);
	j = 0;
	while (str[parse.i])
	{
		ft_set_quote_status(&parse.quotes, str[parse.i]);
		if ((str[parse.i] == '|' && parse.quotes.dble == false
				&& parse.quotes.solo == false) || str[parse.i + 1] == '\0')
		{
			coms[j++] = take_command(&parse, str);
			if (coms[j - 1] == NULL)
				return (free_commands(coms));
		}
		if (parse.quotes.dble == true && str[parse.i] == '\\')
			parse.i += 2;
		else if (str[parse.i] != '\0')
			parse.i++;
	}
	return (coms);
}

char	**ft_get_commands(char *str, int pipe)
{
	char	**coms;

	coms = NULL;
	if (pipe < 1)
		coms = one_command(str);
	else
		coms = more_commands(str, pipe);
	free(str);
	str = NULL;
	if (coms == NULL)
		return (NULL);
	return (coms);
}
