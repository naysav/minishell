/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:41:28 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:29 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	char	*result;
	char	*start;
	char	*end;
	char	*start_result;

	if (!s)
		return (0);
	while (ft_strchr(set, *s) && *s)
		s++;
	start = (char *)s;
	while (*s)
		s++;
	while (ft_strchr(set, *--s) && s >= start)
		;
	end = (char *)(s + 1);
	result = malloc(sizeof(char) * (end - start) + 1);
	if (!result)
		return (0);
	s = start;
	start_result = result;
	while (start++ < end)
		*result++ = *s++;
	*result = '\0';
	return (start_result);
}
