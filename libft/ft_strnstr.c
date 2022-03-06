/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:41:24 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:25 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haystack;

	haystack = (char *)stack;
	i = 0;
	if (needle[0] == 0)
		return (haystack);
	while (haystack[i] && len > i)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && needle[j]
			&& haystack[i + j] && (len > i + j))
		{
			j++;
			if (!needle[j])
				return (haystack + i);
		}
		i++;
	}
	return (0);
}
