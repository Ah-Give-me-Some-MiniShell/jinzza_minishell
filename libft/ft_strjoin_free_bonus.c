/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:01:12 by minckim           #+#    #+#             */
/*   Updated: 2020/11/03 20:23:29 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char *str0, char *str1)
{
	int		size;
	char	*result;
	char	*result_tmp;
	char	*str_tmp;

	size = ft_strlen(str0);
	size += ft_strlen(str1);
	if (!(result_tmp = (result = malloc(sizeof(char) * size))))
		return (0);
	str_tmp = str0;
	while (*str0)
		*result++ = *str0++;
	free(str_tmp);
	str_tmp = str1;
	while (*str1)
		*result++ = *str1++;
	free(str_tmp);
	*result = 0;
	return (result_tmp);
}