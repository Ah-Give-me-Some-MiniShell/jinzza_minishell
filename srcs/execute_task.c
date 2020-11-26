/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_task.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:04:56 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 17:52:57 by minckim          ###   ########.fr       */
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

void	clear_pipe(t_task *task, int option)
{
	if (option == MINISHELL_PREV)
	{
		while (task->prev)
		{
			close(task->prev->pipe_fd[1]);
			task = task->prev;
		}
	}
	else
	{
		while (task->next)
		{
			close(task->next->pipe_fd[0]);
			task = task->next;
		}
	}
}

void	execute_child_process(t_task *task, t_env **lstenv, int (*builtin)())
{
	if (task->fd[0] != 0)
		dup2(task->fd[0], 0);
	else if (task->pipe_fd[0] != 0)
	{
		dup2(task->pipe_fd[0], 0);
		clear_pipe(task, MINISHELL_PREV);
	}
	if (task->fd[1] != 1)
		dup2(task->fd[1], 1);
	else if (task->pipe_fd[1] != 1)
	{
		dup2(task->pipe_fd[1], 1);
		clear_pipe(task, MINISHELL_NEXT);
	}
	if (builtin)
		exit(builtin(task->argv, lstenv));
	path_finder(&task->argv[0], lstenv);
	task->ret = execve(task->argv[0], task->argv, env_to_arr(*lstenv));
	print_err(task->argv[0]);
	exit(task->ret & 0x7f);
}

void	execute_task(t_task *task, t_env **lstenv)
{
	int		(*builtin)();

	builtin = is_builtin(task->argv[0]);
	if (builtin && builtin != ft_echo && builtin != ft_env)
	{
		return_value(1, builtin(task->argv, lstenv));
		return ;
	}
	task->pid = fork();
	if(task->pid == 0)
		execute_child_process(task, lstenv, builtin);
	else
	{
		if (task->next)
			execute_task(task->next, lstenv);
		return ;
	}
}
