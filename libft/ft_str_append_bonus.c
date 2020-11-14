/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:05:19 by minckim           #+#    #+#             */
/*   Updated: 2020/11/03 19:53:55 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	*ft_str_append(t_str *dest, char c)
{
	char	*result;
	char	*result_tmp;
	char	*dest_tmp;
	
	if (!dest)
		if (!(dest = ft_str_new("")))
			return (0);
	if (dest->len + 1 >= dest->size)
	{
		dest->size <<= 1;
		dest_tmp = dest->str;
		if (!(result = malloc(sizeof(char) * dest->size)))
			return (0);
		result_tmp = result;
		while (*dest_tmp)
			*result_tmp++ = *dest_tmp++;
		free(dest->str);
		dest->str = result;
	}
	else
		result_tmp = dest->str + dest->len;
	*result_tmp++ = c;
	*result_tmp = 0;
	dest->len++;
	return (dest);
}