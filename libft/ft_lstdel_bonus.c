/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:10:52 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 20:32:04 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

static void	ft_lstdel_zero(t_list **lst, int (*cmp)(void*, void*), \
			void *arg_cmp, void (*del)(void*))
{
	t_list	*prev;
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		if (cmp(curr->content, arg_cmp))
		{
			del(curr->content);
			prev->next = curr->next;
			free(curr);
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void		ft_lstdel(t_list **lst, int (*cmp)(void*, void*), \
			void *arg_cmp, void (*del)(void*))
{
	t_list	*prev;
	t_list	*curr;

	prev = 0;
	curr = *lst;
	if (!curr)
		return ;
	while (curr)
	{
		if (!cmp(curr->content, arg_cmp))
			break ;
		del(curr->content);
		*lst = curr->next;
		free(curr);
		curr = *lst;
	}
	ft_lstdel_zero(lst, cmp, arg_cmp, del);
}
