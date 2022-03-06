/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:42 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dist, const void *src, size_t len)
{
	char	*dist_c;
	char	*src_c;
	int		i;

	src_c = (char *)src;
	dist_c = (char *)dist;
	i = 0;
	if (!dist && !src)
		return (dist);
	if (dist > src)
	{
		while (len--)
			dist_c[len] = src_c[len];
	}
	else
	{
		while (len--)
		{
			dist_c[i] = src_c[i];
			i++;
		}
	}	
	return (dist);
}
