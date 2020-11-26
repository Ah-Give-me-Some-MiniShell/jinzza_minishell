/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_terminater.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:20:50 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 17:56:54 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clear(t_arg **arg)
{
	if (!*arg)
		return ;
	if ((*arg)->prev)
		while ((*arg)->prev)
		{
			ft_str_del((*arg)->str);
			(*arg) = (*arg)->prev;
			free((*arg)->next);
		}
	else
		while ((*arg)->next)
		{
			ft_str_del((*arg)->str);
			(*arg) = (*arg)->next;
			free((*arg)->prev);
		}
	if (*arg)
	{
		ft_str_del((*arg)->str);
		free((*arg));
		*arg = 0;
	}
}

void	task_clear(t_task **task)
{
	if (!(*task))
		return ;
	if ((*task)->prev)
		while ((*task)->prev)
		{
			free((*task)->argv);
			(*task) = (*task)->prev;
			free((*task)->next);
		}
	else
		while ((*task)->next)
		{
			free((*task)->argv);
			(*task) = (*task)->next;
			free((*task)->prev);
		}
	if (*task)
	{
		free((*task)->argv);
		free((*task));
		*task = 0;
	}
}

int		return_value(int option, int set_num)
{
	static int	ret;

	if (option)
		ret = set_num;
	return (ret);
}

void	fd_close(t_task *task)
{
	if (task->fd[0] != 0)
		close(task->fd[0]);
	if (task->pipe_fd[0] != 0)
		close(task->pipe_fd[0]);
	if (task->fd[1] != 1)
		close(task->fd[1]);
	if (task->pipe_fd[1] != 1)
		close(task->pipe_fd[1]);
	if (task->prev)
		kill(task->prev->pid, SIGKILL);
	if (!task->next)
	{
		return_value(1, WTERMSIG(task->status) ? \
			WTERMSIG(task->status) + 0x80 : WEXITSTATUS(task->status));
		ft_strsignal_pt1(task->status);
		ft_strsignal_pt2(task->status);
	}
	task->is_exit = 1;
}

void	process_terminater(t_task *task)
{
	t_task	*head;
	int		flag_exit;

	head = task;
	flag_exit = 1;
	while (flag_exit)
	{
		flag_exit = 0;
		task = head;
		while (task)
		{
			if (waitpid(task->pid, &task->status, \
					WNOHANG | WUNTRACED | WCONTINUED))
			{
				if (!task->is_exit)
					fd_close(task);
			}
			else
				flag_exit++;
			task = task->next;
		}
	}
}
