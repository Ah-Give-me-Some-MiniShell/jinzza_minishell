/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:52:54 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 12:01:20 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **argv, t_env **lstenv)
{
	int		ret;
	char	buffer[1000];
	char	*result;

	result = getcwd(buffer, 1000);
	ft_putstr_fd(buffer, 1);
	return (0);
}