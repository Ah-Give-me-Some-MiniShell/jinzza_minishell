/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:17 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 17:59:44 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	print_ascii_art(char *path)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
	{
		print_err(path);
		return ;
	}
	while (1)
	{
		ret = get_next_line(fd, &line);
		ft_printf(GREEN"%s\n"WHITE, line);
		free(line);
		if (!ret)
			break ;
	}
	close(fd);
}

void	print_prompt(int option)
{
	if (option)
		ft_putstr_fd("  \n", 1);
	ft_putstr_fd(I_CYAN"드디어 끝났다!! "B_GREEN">> "WHITE, 1);
}

void	minishell(t_env **lstenv)
{
	t_arg	*arg;
	t_task	*task;
	int		size;

	print_prompt(0);
	arg = get_command_line(*lstenv);
	size = arg_rewind(&arg);
	check_syntax(&arg);
	while (arg)
	{
		task = build_task_tree(&arg, size);
		while (task && task->prev)
			task = task->prev;
		if (task && task->argv && *task->argv && **task->argv)
		{
			execute_task(task, lstenv);
			process_terminater(task);
		}
		task_clear(&task);
		if (!(arg->next))
			break;
		arg = arg->next;
	}
	arg_clear(&arg);
}

int		main(int argc, char **argv, char **env)
{
	t_env	*lstenv;

	(void)argc;
	(void)argv;
	print_ascii_art("./img/ascii_art");
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, handler_signal);
	env_init(&lstenv, env);
	while (42)
	{
		minishell(&lstenv);
	}
	return (0);
}