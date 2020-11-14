/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_new_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:47:08 by minckim           #+#    #+#             */
/*   Updated: 2020/11/03 19:53:43 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	*ft_str_new(char *str)
{
	int		len;
	int		size;
	t_str	*result;
	char	*result_tmp;

	if (!(result = malloc(sizeof(t_str))))
		return (0);
	len = ft_strlen(str);
	size = 1;
	while (size <= len)
		size <<= 1;
	result->size = size;
	result->len = len;
	if (!(result->str = malloc(sizeof(char) * size)))
		return (0);
	result_tmp = result->str;
	while (*str)
		*result_tmp++ = *str++;
	*result_tmp = 0;
	return (result);
}