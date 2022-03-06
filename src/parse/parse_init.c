/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:18 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quotes	ft_quotes_init(void)
{
	t_quotes	quotes;

	quotes.dble = false;
	quotes.solo = false;
	return (quotes);
}

t_parse	ft_parse_init(void)
{
	t_parse	parse_data;

	parse_data.quotes = ft_quotes_init();
	parse_data.i = 0;
	parse_data.begin_str = 0;
	parse_data.pipe = 0;
	parse_data.flag = false;
	parse_data.size = 0;
	parse_data.token_amount = 0;
	parse_data.index_token = 0;
	return (parse_data);
}
