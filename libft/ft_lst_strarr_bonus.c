/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_strarr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:09:25 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 20:32:52 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_strarr(t_list *lst)
{
	char	**result;
	char	**result_tmp;
	t_list	*tmp;

	if (!(result = malloc(sizeof(char*) * ((ft_lstsize(lst) + 1)))))
		return (0);
	result_tmp = result;
	while (lst)
	{
		tmp = lst;
		*result++ = lst->content;
		lst = lst->next;
		free(tmp);
	}
	*result = 0;
	return (result_tmp);
}
