/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:19:51 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 19:55:07 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		replace_val(t_env *tmp, t_env *node)
{
	if (ft_strcmp(tmp->key, node->key) == 0)
	{
		free(tmp->val);
		tmp->val = node->val;
		free(node->key);
		free(node);
		return (1);
	}
	if (!(tmp->next))
	{
		tmp->next = node;
		node->prev = tmp;
		return (1);
	}
	return (0);
}

int		add_val(char *str, t_env **lstenv)
{
	t_env	*tmp;
	t_env	*node;

	if (!(node = env_new(str)))
		return (-1);
	if (!*lstenv)
	{
		*lstenv = node;
		return (0);
	}
	tmp = *lstenv;
	while (tmp)
	{
		if (replace_val(tmp, node))
			break ;
		tmp = tmp->next;
	}
	return (0);
}

void	sort_arr(t_env **array, t_env *lstenv, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (lstenv)
	{
		array[i++] = lstenv;
		lstenv = lstenv->next;
	}
	array[i] = 0;
	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			if (ft_strcmp(array[i]->key, array[j]->key) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

t_env	**sort_env(t_env *lstenv)
{
	t_env	*head;
	t_env	**array;
	int		size;

	size = 0;
	head = lstenv;
	while (lstenv)
	{
		size++;
		lstenv = lstenv->next;
	}
	lstenv = head;
	if (!(array = malloc(sizeof(t_env*) * (size + 1))))
		return (0);
	sort_arr(array, lstenv, size);
	return (array);
}

int		ft_export(char **argv, t_env **lstenv)
{
	t_env	**array;
	t_env	**array_head;

	if (!argv[1])
	{
		array = sort_env(*lstenv);
		array_head = array;
		while (*array)
		{
			ft_printf("declare -x %s=\"%s\"\n", (*array)->key, (*array)->val);
			array++;
		}
		free(array_head);
		return (0);
	}
	add_val(argv[1], lstenv);
	return (0);
}
