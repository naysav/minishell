/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:41:07 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:08 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	char	*start_copy;
	size_t	len;

	len = ft_strlen(s1);
	copy = malloc(sizeof(char) * len + 1);
	if (!copy)
		return (0);
	start_copy = copy;
	while (len--)
		*copy++ = *s1++;
	*copy = '\0';
	return (start_copy);
}
