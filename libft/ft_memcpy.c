/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:39 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:40 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	char	*dest_c;
	char	*src_c;

	dest_c = (char *)destination;
	src_c = (char *)source;
	if (!destination && !source)
		return (0);
	while (n--)
		*dest_c++ = *src_c++;
	return (destination);
}
