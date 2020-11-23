/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:04:56 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 22:44:28 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	*is_builtin(char *path)
{
	if (!path)
		return (0);
	if (ft_strcmp(path, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(path, "env") == 0)
		return (ft_env);
	else if (ft_strcmp(path, "export") == 0)
		return (ft_export);
	else if (ft_strcmp(path, "unset") == 0)
		return (ft_unset);
	else if (ft_strcmp(path, "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(path, "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(path, "exit") == 0)
		return (ft_exit);
	else
		return (0);
}

int	read_directory(char **file, char **path_vec)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*tmp;
	
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
	char			**path_vec_head;

	if (ft_strncmp(*file, "/", 1) == 0)
		return (MINISHELL_OK);
	while (*lstenv && ft_strcmp((*lstenv)->key, "PATH"))
		*lstenv = (*lstenv)->next;
	if (!*lstenv)
		return (MINISHELL_ERR);
	path_vec = ft_split((*lstenv)->val, ':');
	if (read_directory(file, path_vec) == MINISHELL_OK)
	{
		ft_clear_array(path_vec_head);
		return (0);
	}
	return (MINISHELL_ERR);
}

void	execute_child_process(t_exe *exe, t_env **lstenv, int (*builtin)())
{
	if (exe->fd[0] != 0)
		dup2(exe->fd[0], 0);
	else if (exe->pipe_fd[0] != 0)
	{
		dup2(exe->pipe_fd[0], 0);
		close(exe->prev->pipe_fd[1]);
	}
	if (exe->fd[1] != 1)
		dup2(exe->fd[1], 1);
	else if (exe->pipe_fd[1] != 1)
		dup2(exe->pipe_fd[1], 1);
	if (builtin)
		exit(builtin(exe->argv, lstenv));
	path_finder(&exe->argv[0], lstenv);
	exe->ret = execve(exe->argv[0], exe->argv, env_to_arr(*lstenv));
	print_err();
	exit(exe->ret);
}

int		execute_shell(t_exe *exe, t_env **lstenv)
{
	int		(*builtin)();

	if ((builtin = is_builtin(exe->argv[0])) && \
						(builtin != ft_echo && builtin != ft_env))
		return (return_value(1, builtin(exe->argv, lstenv)));
	exe->pid = fork();
	if(exe->pid == 0)
		execute_child_process(exe, lstenv, builtin);
	else
		return (0);
	return (0);
}