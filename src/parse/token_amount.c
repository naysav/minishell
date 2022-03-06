/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_amount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:23:17 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	split_token(t_parse *parse, char *com)
{
	if (ft_is_whitespace(com[parse->i]))
	{
		while (ft_is_whitespace(com[parse->i]))
			(parse->i)++;
		if (ft_strchr_bo("<>|\0", com[parse->i]) == false)
			parse->token_amount++;
	}
	else if (ft_strchr_bo("<>|", com[parse->i]))
	{
		(parse->i)++;
		parse->token_amount++;
		if (ft_strchr_bo("<>", com[parse->i - 1]))
		{
			if (com[parse->i] == '>' || com[parse->i] == '<')
				(parse->i)++;
			if (ft_strchr_bo("\t \0", com[parse->i]) == false)
			{
				(parse->i)++;
				parse->token_amount++;
			}
		}
	}
	return (parse->token_amount);
}

int	ft_token_amount(char *com)
{
	static char	*pool_symbols = "<>|\t ";
	t_parse		parse;

	parse = ft_parse_init();
	parse.token_amount = 1;
	while (com[parse.i])
	{
		if (com[parse.i] == '\\' && parse.quotes.solo == false
			&& com[parse.i + 1] != '\0')
			parse.i++;
		ft_set_quote_status(&parse.quotes, com[parse.i]);
		if (ft_strchr_bo(pool_symbols, com[parse.i]) == true
			&& parse.quotes.solo == false && parse.quotes.dble == false)
			parse.token_amount = split_token(&parse, com);
		else
			parse.i++;
	}
	return (parse.token_amount);
}
