/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:05 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:06 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lenofnum(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char		*result;
	size_t		sign;
	size_t		len;
	long long	n;

	n = num;
	sign = (n < 0);
	len = lenofnum(n);
	if (n < 0)
		n = -n;
	result = malloc(sizeof(char) * (len + sign + 1));
	if (!result)
		return (0);
	result[len + sign] = '\0';
	if (sign)
		result[0] = '-';
	while (len--)
	{
		result[len + sign] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
