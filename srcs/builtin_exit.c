/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:54:24 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 13:46:52 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#define FLAG_OVERFLOW	1
#define FLAG_INVALID_CHAR	2

/*
** long long max = 9223372036854775807
*/

ssize_t	ft_atoi_ssizet(char *str, int *flag)
{
	size_t	n;
	int		sign;
	
	if (!str || !*str)
		return (0);
	n = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	sign = *str == '-' ? -1 : 1;
	str += *str == '-' || *str == '+' ? 1 : 0;
	while ('0' <= *str && *str <= '9')
	{
		n = n * 10 + *str++ - '0';
		if (n > 9223372036854775807)
		{
			*flag |= FLAG_OVERFLOW;
			break ;
		}
	}
	*flag |= *str == 0 ? 0 : FLAG_INVALID_CHAR;
	return (n * sign);
}


int		ft_exit(char **argv, t_env **lstenv)
{
	unsigned long long	n;
	int					flag;

	if (argv[1] && argv[2])
	{
		ft_printf(I_RED"exit: too many arguments\n"WHITE);
		exit(1);
	}
	flag = 0;
	(void)lstenv;
	if (argv[1])
		n = ft_atoi_ssizet(argv[1], &flag);
	else
		n = 0;
	if (flag)
	{
		ft_printf(I_RED"exit: numeric argument required\n"WHITE);
		exit(0xff);
	}
	exit(n);
}