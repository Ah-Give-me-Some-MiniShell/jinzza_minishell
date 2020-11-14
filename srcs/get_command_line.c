/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:22 by minckim           #+#    #+#             */
/*   Updated: 2020/11/14 00:54:24 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_flag.h"

t_arg	*arg_new(t_arg *curr, t_str *str, int type)
{
	t_arg	*result;

	if (!(result = malloc(sizeof(t_arg))))
		return (0);
	result->str = str;
	result->prev = curr;
	result->next = 0;
	result->type = type;
	if (curr)
		curr->next = result;
	return (result);
}

t_arg	*get_command_line(t_env *lstenv)
{
	char	*cmdline;
	char	*cmdline_head;
	t_arg	*arg;
	int		flag;
	int		type;

	arg = arg_new(0, ft_str_new(""), 0);
	flag = 0;
	while (1)
	{
		get_next_line(0, &cmdline);
		cmdline_head = cmdline;
		arg->str = ft_str_join_free(arg->str, 
			extract_word(&cmdline, &flag, lstenv, &type));
		while (*cmdline)
			arg = arg_new(arg, 
			extract_word(&cmdline, &flag, lstenv, &type), type);
		free(cmdline_head);
		if (!(flag &(S_QUOTE | D_QUOTE | ESCAPE)))
			break ;
		ft_putstr_fd("> ", 1);
	}
	return arg;
}
