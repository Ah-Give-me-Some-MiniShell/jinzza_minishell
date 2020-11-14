/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join_free_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:03:34 by minckim           #+#    #+#             */
/*   Updated: 2020/11/03 19:53:45 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_str	*handle(t_str *str0, t_str *str1, \
				char **tmp_result, char **tmp_src)
{
	t_str	*result;
	int		len;

	len = str0->len + str1->len;
	if (str0->size <= len)
	{
		if (!(result = malloc(sizeof(t_str))))
			return (0);
		result->size = str0->size;
		while (result->size <= len)
			result->size <<= 1;
		if (!(result->str = malloc(sizeof(char) * result->size)))
			return (0);
		*tmp_result = result->str;
		*tmp_src = str0->str;
		while (**tmp_src)
			*(*tmp_result)++ = *(*tmp_src)++;
		ft_str_del(str0);
		result->len = len;
		return (result);
	}
	result = str0;
	*tmp_result = str0->str + str0->len;
	result->len = len;
	return (result);
}

t_str	*ft_str_join_free(t_str *str0, t_str *str1)
{
	t_str	*result;
	char	*tmp_result;
	char	*tmp_src;
	if (!str0)
		return (str1);
	if (!str1)
		return (str0);
	if (!(result = handle(str0, str1, &tmp_result, &tmp_src)))
		return (0);
	tmp_src = str1->str;
	while (*tmp_src)
		*tmp_result++ = *tmp_src++;
	*tmp_result = 0;
	ft_str_del(str1);
	return (result);
}
