/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_convers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:23:25 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 16:29:22 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_command(char *str)
{
	if (ft_strncmp(str, "<<", ft_strlen("<<")) == 0)
		return (DOBINP);
	if (ft_strncmp(str, "<", ft_strlen("<")) == 0)
		return (INPUT);
	if (ft_strncmp(str, ">>", ft_strlen(">>")) == 0)
		return (APPEND);
	if (ft_strncmp(str, ">", ft_strlen(">")) == 0)
		return (TRUNC);
	if (ft_strncmp(str, "|", ft_strlen("|")) == 0)
		return (PIPE);
	return (EMPTY);
}

static void	init_token(t_token *tmp, int i)
{
	if (i == 0 && check_command(tmp->str) == EMPTY)
		tmp->type = CMD;
	else if (i == 0 && check_command(tmp->str) != EMPTY)
		tmp->type = check_command(tmp->str);
	else if (check_command(tmp->prev->str) == PIPE
		&& check_command(tmp->str) == EMPTY)
		tmp->type = CMD;
	else if (check_command(tmp->str) != EMPTY)
		tmp->type = check_command(tmp->str);
	else
		tmp->type = ARG;
}

t_token	*convert_to_struct(char **coms, t_token **fin_coms)
{
	int		i;
	t_token	*head;
	t_token	*tmp;

	i = -1;
	while (coms[++i])
	{
		tmp = ft_create_token(coms[i]);
		if (tmp == NULL)
			error(ERROR_MALLOC);
		if (i == 0)
			head = tmp;
		else
			add_token_back(&head, tmp);
		if (tmp->str)
			init_token(tmp, i);
	}
	if (fin_coms == NULL)
		return (head);
	add_token_back(fin_coms, head);
	return (*fin_coms);
}
