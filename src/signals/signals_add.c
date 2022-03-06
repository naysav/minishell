/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:24:21 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sig_ignore(int sig)
{
	(void)sig;
}

void	ft_sig_heredoc(int sig)
{
	(void)sig;
	exit(ERROR_MAIN);
}

void	ft_sig_empty(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}
