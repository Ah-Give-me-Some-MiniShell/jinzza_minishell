/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:22 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 00:10:57 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_flag.h"


int	check_syntax(t_arg **arg)
{
	t_arg	*head;
	int		check;

	check = 0;
	head = *arg;
	while (head)
	{
		if (head->type & (RE_IN | RE_OUT | RE_PIPE | ENDLINE))
			check += 1;
		else
			check = 0;
		if (check > 1)
		{
			ft_printf("syntax error near unexpected token '%s'\n", \
			head->str->str);
			arg_clear(arg);
			return (1);
		}
		head = head->next;
	}
	return (0);
}




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
