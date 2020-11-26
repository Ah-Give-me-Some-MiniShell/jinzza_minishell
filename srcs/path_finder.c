/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 02:49:37 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 20:08:32 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		read_directory(char **file, char **path_vec)
{
	DIR				*dir;
	struct dirent	*dp;

	while (*path_vec)
	{
		if (!(dir = opendir(*path_vec)))
		{
			path_vec++;
			continue;
		}
		while ((dp = readdir(dir)))
		{
			if (ft_strcmp(dp->d_name, *file) == 0)
			{
				*file = ft_strjoin_free(ft_strdup("/"), *file);
				*file = ft_strjoin_free(ft_strdup(*path_vec), *file);
				return (MINISHELL_OK);
			}
		}
		path_vec++;
		closedir(dir);
	}
	return (MINISHELL_ERR);
}

int		path_finder(char **file, t_env **lstenv)
{
	char			**path_vec;

	if (ft_strncmp(*file, "/", 1) == 0)
		return (MINISHELL_OK);
	while (*lstenv && ft_strcmp((*lstenv)->key, "PATH"))
		*lstenv = (*lstenv)->next;
	if (!*lstenv)
		return (MINISHELL_ERR);
	path_vec = ft_split((*lstenv)->val, ':');
	if (read_directory(file, path_vec) == MINISHELL_OK)
	{
		ft_clear_array(path_vec);
		return (0);
	}
	return (MINISHELL_ERR);
}
