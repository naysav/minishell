/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:23:31 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	com_tok(char **coms, t_parse *parse, char *str)
{
	if (str[parse->i] != '|' && str[parse->i + 1] == '\0')
		(parse->i)++;
	coms[parse->index_token] = ft_substr(str, parse->begin_str,
			parse->i - parse->begin_str);
	if (coms[parse->index_token] == NULL)
		return (false);
	if (ft_strchr_bo("<>|", str[parse->i]) == false && str[parse->i] != '\0')
	{
		(parse->i)++;
		while (ft_is_whitespace(str[parse->i]))
			(parse->i)++;
		parse->begin_str = parse->i;
	}
	(parse->index_token)++;
	return (true);
}

static bool	sym_tok_redirects(char **coms, t_parse *parse, char *str)
{
	if (ft_strchr_bo("<>", str[parse->i + 1]))
	{
		if (str[parse->i + 1] == '>')
			coms[parse->index_token] = ft_strdup(">>");
		else
			coms[parse->index_token] = ft_strdup("<<");
		(parse->i)++;
	}
	else if (str[parse->i] == '>')
		coms[parse->index_token] = ft_strdup(">");
	else if (str[parse->i] == '<')
		coms[parse->index_token] = ft_strdup("<");
	if (coms[parse->index_token] == NULL)
		return (false);
	(parse->i)++;
	while (ft_is_whitespace(str[parse->i]))
		(parse->i)++;
	parse->begin_str = parse->i;
	(parse->index_token)++;
	return (true);
}

static bool	sym_tok(char **coms, t_parse *parse, char *str)
{
	if (ft_strchr_bo("<>", str[parse->i]))
	{
		if (sym_tok_redirects(coms, parse, str) == false)
			return (false);
	}
	else
	{
		coms[parse->index_token] = ft_strdup("|");
		if (coms[parse->index_token] == NULL)
			return (false);
	}
	return (true);
}

bool	ft_token_new(char **coms, t_parse *parse, char *str)
{
	if (str[parse->i] == '|' || str[parse->i + 1] == '\0')
		parse->flag = true;
	if (ft_strchr_bo("<>|", str[parse->i]))
	{
		if (parse->i != 0)
		{
			if (ft_is_whitespace(str[parse->i - 1]) == false)
			{
				if (com_tok(coms, parse, str) == false)
					return (false);
			}
		}
		if (sym_tok(coms, parse, str) == false)
			return (false);
	}
	else
	{
		if (com_tok(coms, parse, str) == false)
			return (false);
	}
	return (true);
}
