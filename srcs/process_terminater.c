/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_terminater.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:20:50 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 19:19:48 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		return_value(int option, int set_num)
{
	static int	ret;

	if (option)
		ret = set_num;
	return (ret);
}

void	fd_close(t_exe *exe, int *flag_exit)
{
	if (exe->fd[0] != 0)
		close(exe->fd[0]);
	if (exe->fd[1] != 1)
		close(exe->fd[1]);
	if (exe->pipe_fd[0] != 0)
		close(exe->pipe_fd[0]);
	if (exe->pipe_fd[1] != 1)
		close(exe->pipe_fd[1]);
	*flag_exit = 0;
	if (exe->prev)
		kill(exe->prev->pid, SIGKILL);
	wait(&exe->status);
	if (!exe->next)
	{
		return_value(1, exe->status);
		ft_strsignal_pt1(exe->status);
		ft_strsignal_pt2(exe->status);
	}
}

void	process_terminater(t_exe *exe, int	size)
{
	t_exe	*head;
	int		flag_exit;

	head = exe;
	flag_exit = 1;
	while (flag_exit)
	{
		exe = head;
		while (exe)
		{
			if (waitpid(exe->pid, &exe->status, WNOHANG))
				fd_close(exe, &flag_exit);
			else
				flag_exit = 1;
			exe = exe->next;
		}
	}
}