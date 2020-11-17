/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:54:24 by minckim           #+#    #+#             */
/*   Updated: 2020/11/16 18:10:51 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** long long max = 9223372036854775807
*/
#define FLAG_OVERFLOW	1
#define FLAG_INVALID_CHAR	2

ssize_t	ft_atoi_ssizet(char *str, int *flag)
{
	size_t	n;
	int		sign;

	*flag = 0;
	if (!*str)
		return (0);
	n = 0;
	sign = 1;
	while (9 <= *str && *str <= 13 || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (n >= 922337203685477580 && *str > '7')
		{
			printf("[%zu]\n", n);
			*flag |= FLAG_OVERFLOW;
		}
		n *= 10;
		n += *str++ - '0';
	}
	*flag |= *str == 0 ? 0 : FLAG_INVALID_CHAR;
	return (n * sign);
}


int		ft_exit(char **argv, t_env *lstenv)
{
	unsigned long long	n;

	if (argv || argv[0])
		n = ft_atoi(argv[0]);
	exit(0);
}