/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:41:12 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:13 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ressize;
	size_t	i;

	i = 0;
	ressize = (ft_strlen(dst));
	if (dstsize < ressize)
		return (dstsize + ft_strlen(src));
	while ((i < dstsize - ressize - 1) && src[i]
		&& (ressize < dstsize - 1) && (dstsize > 0))
	{
		dst[ressize + i] = src[i];
		i++;
	}
	dst[ressize + i] = '\0';
	return (ressize + ft_strlen(src));
}
