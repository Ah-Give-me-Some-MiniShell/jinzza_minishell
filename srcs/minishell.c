/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:17 by minckim           #+#    #+#             */
/*   Updated: 2020/11/18 19:51:49 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	print_prompt(int option)
{
	if (option)
		ft_putstr_fd("  \n", 1);
	ft_putstr_fd(\
	I_GREEN"국립국어원 외래어 표기법에 따르면 쉘(X) 셸(O) 입니다 > "WHITE, 1);
}

int		return_value(int option, int set_num)
{
	static int	ret;

	if (option)
		ret = set_num;
	return (ret);
}

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		exit(SIGINT);
	}
	else if (signo == SIGQUIT)
	{
		exit(SIGQUIT);
	}
	return ;
}
void	handler_signal(int signo)
{
	return_value(1, signo);
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b", 1);
		print_prompt(1);
	}
	return ;
}

void	minishell(t_env **lstenv)
{
	t_arg	*arg;
	t_exe	*exe;
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
		if (exe && exe->argv && *exe->argv && **exe->argv)
		{
			execute_shell(exe, lstenv);
			manage_pipe(exe, size);
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

	// signal(SIGINT, handler_signal);
	// signal(SIGQUIT, handler_signal);
	env_init(&lstenv, env);
	while (42)
	{
		minishell(&lstenv);
		printf("ahahahahahah\n");
	}

}