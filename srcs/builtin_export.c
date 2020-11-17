/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:19:51 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 13:08:52 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp(tmp->key, node->key) == 0)
		{
			free(tmp->val);
			tmp->val = node->val;
			free(node->key);
			free(node);
			break ;
		}
		if (!(tmp->next))
		{
			tmp->next = node;
			node->prev = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	return 0;
}

t_env	**sort_env(t_env *lstenv)
{
	t_env	*head;
	t_env	**array;
	int		size;
	int		i;
	int		j;

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
				t_env	*tmp;
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	return (array);
}


int		ft_export(char **argv, t_env **lstenv)
{
	t_env	*node;
	t_env	**array;
	t_env	**array_head;
	int		size;

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
	return 0;
	// if (!(node = malloc(sizeof(t_env))))
	// 	return (-1);

}