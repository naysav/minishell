/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:31:55 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(int error_type)
{
	if (error_type == ERROR_MALLOC)
		ft_putstr_fd("Process terminated with malloc error\n", STDERR_FILENO);
	else if (error_type == ERROR_DUP)
		ft_putstr_fd("Process terminated with dup error\n", STDERR_FILENO);
	else if (error_type == ERROR_FORK)
		ft_putstr_fd("Process terminated with fork error\n", STDERR_FILENO);
	else if (error_type == ERROR_OPEN)
		ft_putstr_fd("Process terminated with open error\n", STDERR_FILENO);
	else if (error_type == ERROR_CLOSE)
		ft_putstr_fd("Process terminated with close error\n", STDERR_FILENO);
	else if (error_type == ERROR_EXECVE)
		ft_putstr_fd("Process terminated with execve error\n", STDERR_FILENO);
	else if (error_type == ERROR_PATH)
		ft_putstr_fd("Process terminated with path error\n", STDERR_FILENO);
	else if (error_type == ERROR_PIPE)
		ft_putstr_fd("Process terminated with pipe error\n", STDERR_FILENO);
	exit(error_type);
}
