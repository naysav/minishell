/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:23:37 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:53:00 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_create_token(char *content)
{
	t_token	*element;

	element = (t_token *)ft_calloc(1, sizeof(t_token));
	if (element == NULL)
		return (element);
	else
	{
		element->str = ft_strdup(content);
		if (element->str == NULL)
		{
			free(element);
			element = NULL;
			return (NULL);
		}
	}
	return (element);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *lst;
	if (curr == NULL)
		*lst = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		tmp = curr;
		curr->next = new;
		tmp = curr->next;
		tmp->prev = curr;
	}
}

void	ft_token_struct_free(t_token *lst)
{
	t_token	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->str != NULL)
			free(lst->str);
		if (lst != NULL)
			free(lst);
		lst = tmp;
	}
}
