/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:24:50 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 12:01:11 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **argv, t_env **lstenv)
{
	int		newline;

	(void)lstenv;
	newline = 0;
	argv++;
	if (ft_strcmp(*argv, "-n") == 0)
		newline = 1;
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (argv[1])
			ft_putstr_fd(" ", 1);
		argv++;
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}