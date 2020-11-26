/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:56:55 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 16:18:33 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#include "minishell_flag.h"

void	print_err(char *str)
{
	extern int	errno;
	
	ft_printf(I_RED"%s: %s\n"WHITE, str, strerror(errno));
}


int		ft_strsignal_pt1(int status)
{
	status == 1 ? ft_printf(I_RED"Hangup: 1\n"WHITE) : 0;
	status == 2 ? ft_printf(I_RED"Interrupt: 2\n"WHITE) : 0;
	status == 3 ? ft_printf(I_RED"Quit: 3\n"WHITE) : 0;
	status == 4 ? ft_printf(I_RED"Illegal instruction: 4\n"WHITE) : 0;
	status == 5 ? ft_printf(I_RED"Trace/BPT trap: 5\n"WHITE) : 0;
	status == 6 ? ft_printf(I_RED"Abort trap: 6\n"WHITE) : 0;
	status == 7 ? ft_printf(I_RED"EMT trap: 7\n"WHITE) : 0;
	status == 8 ? ft_printf(I_RED"Floating point exception: 8\n"WHITE) : 0;
	status == 9 ? ft_printf(I_RED"Killed: 9\n"WHITE) : 0;
	status == 10 ? ft_printf(I_RED"Bus error: 10\n"WHITE) : 0;
	status == 11 ? ft_printf(I_RED"Segmentation fault: 11\n"WHITE) : 0;
	status == 12 ? ft_printf(I_RED"Bad system call: 12\n"WHITE) : 0;
	status == 13 ? ft_printf(I_RED"Broken pipe: 13\n"WHITE) : 0;
	status == 14 ? ft_printf(I_RED"Alarm clock: 14\n"WHITE) : 0;
	return (0);
}

int		ft_strsignal_pt2(int status)
{
	status == 15 ? ft_printf(I_RED"Terminated: 15\n"WHITE) : 0;
	status == 16 ? ft_printf(I_RED"Urgent I/O condition: 16\n"WHITE) : 0;
	status == 17 ? ft_printf(I_RED"Suspended (signal): 17\n"WHITE) : 0;
	status == 18 ? ft_printf(I_RED"Suspended: 18\n"WHITE) : 0;
	status == 19 ? ft_printf(I_RED"Continued: 19\n"WHITE) : 0;
	status == 20 ? ft_printf(I_RED"Child exited: 20\n"WHITE) : 0;
	status == 21 ? ft_printf(I_RED"Stopped (tty input): 21\n"WHITE) : 0;
	status == 22 ? ft_printf(I_RED"Stopped (tty output): 22\n"WHITE) : 0;
	status == 23 ? ft_printf(I_RED"I/O possible: 23\n"WHITE) : 0;
	status == 24 ? ft_printf(I_RED"Cputime limit exceeded: 24\n"WHITE) : 0;
	status == 25 ? ft_printf(I_RED"Filesize limit exceeded: 25\n"WHITE) : 0;
	status == 26 ? ft_printf(I_RED"Virtual timer expired: 26\n"WHITE) : 0;
	status == 27 ? ft_printf(I_RED"Profiling timer expired: 27\n"WHITE) : 0;
	status == 28 ? ft_printf(I_RED"Window size changes: 28\n"WHITE) : 0;
	status == 29 ? ft_printf(I_RED"Information request: 29\n"WHITE) : 0;
	return (0);
}

void	handler_signal(int signo)
{
	if (signo == SIGINT)
	{
		return_value(1, signo);
		ft_putstr_fd("\b\b", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
	return ;
}