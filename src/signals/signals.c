/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:24:50 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:52:03 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tty_mask(void)
{
	struct termios	sterm;

	tcgetattr(0, &sterm);
	sterm.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &sterm);
}

void	ft_c_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_c_handle_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_slash_handle_fork(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
}

void	start_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_c_handle);
}
