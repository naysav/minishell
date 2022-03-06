/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:20:08 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_set_quote_status(t_quotes *quotes, char ch)
{
	if (ch == '\'' && quotes->solo == true)
		quotes->solo = false;
	else if (ch == '\'' && quotes->dble == false)
		quotes->solo = true;
	else if (ch == '"' && quotes->dble == true)
		quotes->dble = false;
	else if (ch == '"' && quotes->solo == false)
		quotes->dble = true;
	else
		return (false);
	return (true);
}

bool	ft_is_outside_quotes(t_quotes *quotes)
{
	return (quotes->dble == false && quotes->solo == false);
}
