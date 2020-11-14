/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_array_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:18:14 by minckim           #+#    #+#             */
/*   Updated: 2020/11/09 22:22:21 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_clear_array(char **arr)
{
	char	**arr_tmp;

	if (!arr)
		return ;
	arr_tmp = arr;
	while (*arr)
		free(*arr++);
	free(arr_tmp);
}