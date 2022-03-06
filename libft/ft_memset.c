/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:44 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:45 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	char	*dest_c;

	dest_c = (char *)destination;
	while (n--)
		*dest_c++ = (char)c;
	return (destination);
}
