/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:19:28 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_strchr_bo(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (true);
		i++;
	}
	if (c == '\0')
		return (true);
	return (false);
}

bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	ft_skip_tabulation(char *str)
{
	int	i;
	int	size_str;

	i = -1;
	size_str = ft_strlen(str);
	while (ft_is_whitespace(str[++i]))
		size_str--;
	if (size_str == 0)
		return (true);
	return (false);
}

static int	trim_everything(char *str, int size_str, int *begin, int *final)
{
	while (ft_is_whitespace(str[*begin]))
	{
		(*begin)++;
		size_str--;
	}
	while (ft_is_whitespace(str[*final]))
	{
		(*final)--;
		size_str--;
	}
	return (size_str);
}

char	*ft_trim_tabulation(char *str)
{
	int		begin_index;
	int		final_index;
	int		size_str;

	begin_index = 0;
	final_index = ft_strlen(str) - 1;
	size_str = ft_strlen(str);
	if (size_str == 0)
		return (ft_strdup(""));
	if (trim_everything(str, size_str, &begin_index, &final_index) <= 0)
		return (ft_strdup(""));
	return (ft_substr(str, begin_index, size_str));
}
