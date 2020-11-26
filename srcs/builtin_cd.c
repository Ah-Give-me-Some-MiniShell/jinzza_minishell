/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:49:22 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 19:45:23 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **argv, t_env **lstenv)
{
	int		ret;
	char	buffer[1000];
	char	*result;

	if (!argv[1])
		return (0);
	getcwd(buffer, 1000);
	if ((ret = chdir(argv[1])) < 0)
	{
		print_err(argv[1]);
		return (1);
	}
	result = ft_strjoin_free(ft_strdup("OLDPWD="), ft_strdup(buffer));
	add_val(result, lstenv);
	free(result);
	result = ft_strjoin_free(ft_strdup("PWD="), \
										ft_strdup(getcwd(buffer, 1000)));
	add_val(result, lstenv);
	free(result);
	return (0);
}
