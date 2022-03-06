/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:34 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:35 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*res;
	int		i;
	char	ss;

	ss = (char)c;
	i = 0;
	res = (char *)s;
	while (n--)
	{
		if (res[i] == ss)
			return (res);
		res++;
	}
	return (0);
}
