/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:53:57 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 15:04:42 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **argv, t_env **lstenv)
{
	t_env	*tmp;
	char	*str;

	tmp = *lstenv;
	if (!tmp || !argv[1] || (argv[1] && argv[2]))
		return (0);
	str = argv[1];
	if ('0' <= *argv[1] && *argv[1] <= '9')
		return (1);
	while (*str)
		if (!(ft_isalnum(*str)) && *str != '_')
			return (1);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, argv[1]) == 0)
		{
			if (!tmp->next)
			{
				free(tmp);
				*lstenv = 0;
			}
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return 0;
}