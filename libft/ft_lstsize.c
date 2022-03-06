/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:40:29 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 18:40:30 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *current)
{
	int	i;

	if (!current)
		return (0);
	i = 1;
	while (current -> next != 0)
	{
		current = current -> next;
		i++;
	}
	return (i);
}
