/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:55:37 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(t_shell *shell, t_token *token)
{
	bool	is_newline;

	is_newline = true;
	if (token && token ->str
		&& ft_strncmp(token->str, "-n", ft_strlen("-n")) == 0)
	{
		is_newline = false;
		while (token && token ->str
			&& ft_strncmp(token->str, "-n", ft_strlen("-n")) == 0)
			token = token->next;
	}
	while (token && token->type == ARG)
	{
		write(STDOUT_FILENO, token->str, ft_strlen(token->str));
		if (token->next && token->next->type == ARG)
			write(STDOUT_FILENO, " ", 1);
		token = token->next;
	}
	if (is_newline)
		write(STDOUT_FILENO, "\n", 1);
	shell->exit_status = ERROR_NON;
}
