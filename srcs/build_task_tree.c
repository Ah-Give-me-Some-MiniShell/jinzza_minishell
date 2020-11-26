/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_task_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:28:52 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 17:51:51 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#include "minishell_flag.h"

t_task	*task_new(t_task *current, int arg_size)
{
	t_task	*task;

	if (!(task = malloc(sizeof(t_task))))
		return (0);
	if (current)
		current->next = task;
	task->pid = 0;
	task->prev = current;
	task->next = 0;
	task->argv = malloc(sizeof(char*) * (arg_size + 1));
	*task->argv = 0;
	task->fd[0] = 0;
	task->fd[1] = 1;
	task->pipe_fd[0] = 0;
	task->pipe_fd[1] = 1;
	task->ret = 0;
	task->status = 0;
	task->is_exit = 0;
	return (task);
}

int		arg_rewind(t_arg **arg)
{
	int		size;

	size = 0;
	if ((*arg))
		size++;
	while ((*arg) && (*arg)->prev)
	{
		*arg = (*arg)->prev;
		size++;
	}
	return (size);
}

void	argv_append(t_task *task, t_arg *arg)
{
	char	**tmp;

	tmp = task->argv;
	while (*tmp)
		tmp++;
	*tmp++ = arg->str->str;
	*tmp = 0;
}

t_task	*build_task_tree(t_arg **arg, int arg_size)
{
	t_task	*task;

	task = task_new(0, arg_size);
	while ((*arg) && *(*arg)->str->str)
	{
		if (redirection_manage(&task, arg, arg_size))
			break ;
		if ((*arg)->next)
			*arg = (*arg)->next;
		else
			break ;
	}
	return (task);
}
