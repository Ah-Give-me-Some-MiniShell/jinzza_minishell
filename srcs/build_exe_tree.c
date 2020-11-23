/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exe_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:28:52 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 17:57:06 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#include "minishell_flag.h"



t_exe	*exe_new(t_exe *current, int arg_size)
{
	t_exe	*exe;

	if (!(exe = malloc(sizeof(t_exe))))
		return (0);
	if (current)
		current->next = exe;
	exe->prev = current;
	exe->next = 0;
	exe->argv = malloc(sizeof(char*) * (arg_size + 1));
	*exe->argv = 0;
	exe->fd[0] = 0;
	exe->fd[1] = 1;
	exe->pipe_fd[0] = 0;
	exe->pipe_fd[1] = 1;
	exe->ret = 0;
	exe->status = 0;
	return (exe);
}

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

void	exe_clear(t_exe **exe)
{
	if (!(*exe))
		return ;
	if ((*exe)->prev)
		while ((*exe)->prev)
		{
			free((*exe)->argv);
			(*exe) = (*exe)->prev;
			free((*exe)->next);
		}
	else
		while ((*exe)->next)
		{
			free((*exe)->argv);
			(*exe) = (*exe)->next;
			free((*exe)->prev);
		}
	if (*exe)
	{
		free((*exe)->argv);
		free((*exe));
		*exe = 0;
	}
}

void	argv_append(t_exe *exe, t_arg *arg)
{
	char	**tmp;

	tmp = exe->argv;
	while (*tmp)
		tmp++;
	*tmp++ = arg->str->str;
	*tmp = 0;
}

int		fd_redirection(t_arg **arg, t_exe *exe, int flag)
{
	(*arg) = (*arg)->next;
	if (exe->fd[0] != 0)
		close(exe->fd[0]);
	if ((exe->fd[0] = open((*arg)->str->str, O_RDONLY)) < 0)
	{
		print_err();
		exe_clear(&exe);
		return (MINISHELL_ERR);
	}
	return (MINISHELL_OK);
}

t_exe	*build_exe_tree(t_arg **arg, int arg_size)
{
	t_exe	*exe;
	int		fd[2];

	exe = exe_new(0, arg_size);
	while ((*arg) && *(*arg)->str->str)
	{
		if ((*arg)->type == RE_IN)
		{
			// (*arg) = (*arg)->next;
			// if (exe->fd[0] != 0)
			// 	close(exe->fd[0]);
			// if ((exe->fd[0] = open((*arg)->str->str, O_RDONLY)) < 0)
			// {
			// 	print_err();
			// 	exe_clear(&exe);
			// 	return (0);
			// }
		}
		else if ((*arg)->type == RE_OUT)
		{
			(*arg) = (*arg)->next;
			if (exe->fd[1] != 1)
				close(exe->fd[1]);
			if ((exe->fd[1] = \
			open((*arg)->str->str, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			{
				print_err();
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == RE_APP)
		{
			(*arg) = (*arg)->next;
			if (exe->fd[1] != 1)
				close(exe->fd[1]);
			if ((exe->fd[1] = \
			open((*arg)->str->str, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			{
				print_err();
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == RE_PIPE)
		{
			if (pipe(fd))
			{
				print_err();
				exe_clear(&exe);
				return (0);
			}
			exe->pipe_fd[1] = fd[1];
			if ((*arg)->next)
			{
				exe = exe_new(exe, arg_size);
				exe->pipe_fd[0] = fd[0];
			}
			else
			{
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == ENDLINE)
		{
			break ;
		}
		else
		{
			argv_append(exe, *arg);
		}
		if ((*arg)->next)
			(*arg) = (*arg)->next;
		else
			break;
	}
	return (exe);
}