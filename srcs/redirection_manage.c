/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 02:43:13 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 17:56:40 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_flag.h"

int		fd_redirection_in(t_arg **arg, t_task **task)
{
	(*arg) = (*arg)->next;
	if ((*task)->pipe_fd[0] != 0)
	{
		close((*task)->pipe_fd[0]);
		(*task)->pipe_fd[0] = 0;
	}
	if ((*task)->fd[0] != 0)
		close((*task)->fd[0]);
	if (((*task)->fd[0] = open((*arg)->str->str, O_RDONLY)) < 0)
	{
		if ((*task)->fd[1] != 1)
			close((*task)->fd[1]);
		print_err((*arg)->str->str);
		task_clear(task);
		return (MINISHELL_ERR);
	}
	return (MINISHELL_OK);
}

int		fd_redirection_out(t_arg **arg, t_task **task)
{
	(*arg) = (*arg)->next;
	if ((*task)->fd[1] != 1)
		close((*task)->fd[1]);
	if (((*task)->fd[1] = \
	open((*arg)->str->str, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		if ((*task)->fd[0] != 0)
			close((*task)->fd[0]);
		print_err((*arg)->str->str);
		task_clear(task);
		return (MINISHELL_ERR);
	}
	return (MINISHELL_OK);
}

int		fd_redirection_app(t_arg **arg, t_task **task)
{
	(*arg) = (*arg)->next;
	if ((*task)->fd[1] != 1)
		close((*task)->fd[1]);
	if (((*task)->fd[1] = \
	open((*arg)->str->str, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
	{
		if ((*task)->fd[0] != 0)
			close((*task)->fd[0]);
		print_err((*arg)->str->str);
		task_clear(task);
		return (MINISHELL_ERR);
	}
	return (MINISHELL_OK);
}

int		fd_redirection_pipe(t_arg **arg, t_task **task, int arg_size)
{
	int		fd[2];

	if ((*task)->fd[1] != 1)
		return (MINISHELL_OK);
	if (pipe(fd))
	{
		if ((*task)->fd[0] != 0)
			close((*task)->fd[0]);
		print_err((*arg)->str->str);
		task_clear(task);
		return (MINISHELL_ERR);
	}
	(*task)->pipe_fd[1] = fd[1];
	if ((*arg)->next)
	{
		(*task) = task_new((*task), arg_size);
		(*task)->pipe_fd[0] = fd[0];
		return (MINISHELL_OK);
	}
	task_clear(task);
	return (MINISHELL_ERR);
}

int		redirection_manage(t_task **task, t_arg **arg, int arg_size)
{
	int		ret;
	
	ret = MINISHELL_OK;
	if ((*arg)->type == RE_IN)
		ret = fd_redirection_in(arg, task);
	else if ((*arg)->type == RE_OUT)
		ret = fd_redirection_out(arg, task);
	else if ((*arg)->type == RE_APP)
		ret = fd_redirection_app(arg, task);
	else if ((*arg)->type == RE_PIPE)
		ret = fd_redirection_pipe(arg, task, arg_size);
	else if ((*arg)->type == ENDLINE)
		return (1);
	else
		argv_append(*task, *arg);
	if (ret == MINISHELL_ERR)
	{
		while ((*arg)->next && (*arg)->type != ENDLINE)
			*arg = (*arg)->next;
		return (1);
	}
	return (0);
}