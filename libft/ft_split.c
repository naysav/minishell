/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:59 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:00 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static size_t	ft_col(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (*s)
	{
		if (*s != c)
		{
			res++;
			while (*s != c && *s)
				s++;
			s--;
		}
		s++;
	}
	return (res);
}

static size_t	ft_lenword(char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s++)
		i++;
	return (i);
}

static char	*ft_word_rc(char *s, size_t len)
{
	char	*split;
	char	*split_start;

	split = (char *)malloc(sizeof(char) * (len + 1));
	if (!split)
		return (0);
	split_start = split;
	while (len--)
	{
		*split++ = *s++;
	}
	*split = '\0';
	return (split_start);
}

static char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (*split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**split;
	size_t	i;
	char	*s;
	size_t	cols;

	if (!str)
		return (0);
	s = (char *)str;
	i = 0;
	cols = ft_col(s, c);
	split = (char **)malloc(sizeof(char *) * (cols + 1));
	if (!split)
		return (0);
	while (cols--)
	{
		while (*s == c)
			s++;
		split[i] = ft_word_rc(s, ft_lenword(s, c));
		if (!split[i])
			return (ft_free(split));
		i++;
		s += ft_lenword(s, c);
	}
	split[i] = NULL;
	return (split);
}
