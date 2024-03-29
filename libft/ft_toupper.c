/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:08:55 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/22 18:41:42 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	i;

	i = (unsigned char)c;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}	
