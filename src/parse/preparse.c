/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:48 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_string(char *str, t_quotes *quotes, int *i, char *user)
{
	static char	*pool_symbols = "\\<>|;";

	ft_set_quote_status(quotes, str[*i]);
	if (str[*i] == '\\' && quotes->dble == true)
		(*i)++;
	else if (ft_strchr_bo(pool_symbols, str[*i]) == true
		&& ft_is_outside_quotes(quotes) == true)
		if (ft_check_seps(str, i, user) == false
			|| ft_check_redirect(str, i, user) == false)
			return (false);
	return (true);
}

bool	ft_preparse(char *str, char *user)
{
	int			i;
	t_quotes	quotes;

	quotes = ft_quotes_init();
	i = 0;
	while (str[i])
	{
		if (check_string(str, &quotes, &i, user) == false)
			return (false);
		if (str[i] != '\0')
			i++;
	}
	return (true);
}
