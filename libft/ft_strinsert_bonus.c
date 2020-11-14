/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:14:57 by minckim           #+#    #+#             */
/*   Updated: 2020/11/03 20:23:13 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strinsert(char *dest, char *src, int idx)
{
	char	*dest_tmp;
	char	*result;
	char	*result_tmp;
	size_t	size;

	size = ft_strlen(dest);
	if (idx < 0)
		idx = size + idx + 1;
	if (idx < 0)
		idx = 0;
	size += ft_strlen(src);
	if (!(result = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	dest_tmp = dest;
	result_tmp = result;
	while (*dest && idx--)
		*result++ = *dest++;
	while (*src)
		*result++ = *src++;
	while (*dest)
		*result++ = *dest++;
	*result = 0;
	return (result_tmp);
}