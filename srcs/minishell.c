/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:17 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 22:33:15 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	print_ascii_art(char *path)
{
	int		fd;
	char	buffer[1000];
	int		n_read;

	if ((fd = open(path, O_RDONLY)) < 0)
		return ;
	while ((n_read = read(0, buffer, 1000)))
		write(1, buffer, n_read);
}

void	print_prompt(int option)
{
	if (option)
		ft_putstr_fd("  \n", 1);
	ft_putstr_fd(\
	I_GREEN"국립국어원 외래어 표기법에 따르면 쉘(X) 셸(O) 입니다 > "WHITE, 1);
}

void	minishell(t_env **lstenv)
{
	t_arg	*arg;
	t_exe	*exe;
	t_exe	*head;
	int		size;

	print_prompt(0);
	arg = get_command_line(*lstenv);
	size = arg_rewind(&arg);
	check_syntax(&arg);
	while (arg)
	{
		exe = build_exe_tree(&arg, size);
		while (exe && exe->prev)
			exe = exe->prev;
		head = exe;
		if (exe && exe->argv && *exe->argv && **exe->argv)
		{
			while (exe)
			{
				execute_shell(exe, lstenv);
				exe = exe->next;
			}
			exe = head;
			process_terminater(exe, size);
		}
		exe_clear(&exe);
		if (!(arg->next))
			break;
		arg = arg->next;
	}
	arg_clear(&arg);
}

int		main(int argc, char **argv, char **env)
{
	t_env	*lstenv;

	print_ascii_art("../img/ascii_art");
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, handler_signal);
	env_init(&lstenv, env);
	while (42)
	{
		minishell(&lstenv);
	}

}