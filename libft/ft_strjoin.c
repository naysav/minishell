/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:41:10 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:11 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_rslt;
	size_t	len1;
	size_t	len2;
	char	*s;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (len1 + len2) + 1);
	if (!s)
		return (0);
	s_rslt = s;
	while (len1--)
		*s++ = *s1++;
	while (len2--)
		*s++ = *s2++;
	*s = '\0';
	return (s_rslt);
}
