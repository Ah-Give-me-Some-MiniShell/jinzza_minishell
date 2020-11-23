/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:49:22 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 22:39:44 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_cd(char **argv, t_env **lstenv)
{
	int		ret;
	t_env	*tmp;
	char	buffer[1000];
	char	*result;

	result = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(buffer, 1000)));
	add_val(result, lstenv);
	free(result);
	if ((ret = chdir(argv[1])) < 0)
		print_err();
	result = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(buffer, 1000)));
	add_val(result, lstenv);
	free(result);
	return (0);
}

// int		ft_cd(char **argv, t_env **lstenv)
// {
// 	int		ret;
// 	t_env	*tmp;
// 	char	buffer[1000];
// 	char	*result;

// 	tmp = *lstenv;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
// 		{
// 			free(tmp->val);
// 			tmp->val = ft_strdup(getcwd(buffer, 1000));
// 		}
// 		tmp = tmp->next;
// 	}
// 	if ((ret = chdir(argv[1])) < 0)
// 		print_err();
// 	tmp = *lstenv;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, "PWD") == 0)
// 		{
// 			free(tmp->val);
// 			tmp->val = ft_strdup(getcwd(buffer, 1000));
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }