/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:17 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 15:37:45 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"



int		main(int argc, char **argv, char **env)
{
	t_env	*lstenv;
	t_arg	*arg;
	t_exe	*exe;
	int		size;
	int		ret;

	// signal(2, sigint_handler);

	env_init(&lstenv, env);
	while (42)
	{
		ft_putstr_fd(I_GREEN"국립국어원 외래어 표기법에 따르면 쉘(X) 셸(O) 입니다 \n> "WHITE, 1);
		arg = get_command_line(lstenv);
		size = arg_rewind(&arg);
		check_syntax(&arg);
		while (arg)
		{
			exe = build_exe_tree(&arg, size);
			while (exe && exe->prev)
				exe = exe->prev;
			if (exe && exe->argv && *exe->argv && **exe->argv)
				execute_shell(exe, &lstenv, &ret);
			// add_val(ft_strjoin_free(ft_strdup("?"), ft_itoa(ret)), &lstenv);
			exe_clear(&exe);
			if (!(arg->next))
				break;
			arg = arg->next;
		}
		arg_clear(&arg);
	}

}