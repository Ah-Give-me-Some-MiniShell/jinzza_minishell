/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:24:50 by minckim           #+#    #+#             */
/*   Updated: 2020/11/12 11:09:20 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **argv, t_env *lstenv)
{
	int		newline;

	newline = 0;
	while (*argv)
	{
		if (ft_strcmp(*argv, "-n"))
			newline = 1;
		else
			ft_putstr_fd(*argv++, 1);
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}