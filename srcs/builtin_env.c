/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:37:56 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 11:59:26 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_arr(t_env *env)
{
	int		size;
	char	**arr;
	char	**arr_head;
	t_env	*head;

	head = env;
	size = 1;
	while (env)
	{
		size++;
		env = env->next;
	}
	if (!(arr = malloc(sizeof(char*) * (size))))
		return (0);
	arr_head = arr;
	env = head;
	while (env)
	{
		*arr++ = ft_strjoin(env->key, env->val);
		env = env->next;
	}
	*arr = 0;
	return (arr_head);
}

t_env	*env_new(char *str)
{
	t_env	*env;
	char	*start;

	start = str;
	while (*str && *str != '=')
		str++;
	if (!*str)
		return (0);
	if (!(env = malloc(sizeof(t_env))))
		return (0);
	if (!(env->key = ft_substr(start, 0, str - start)))
	{
		free(env);
		return (0);
	}
	if (!*str || !(env->val = ft_strdup(++str)))
	{
		free(env->key);
		free(env);
		return (0);
	}
	env->prev = 0;
	env->next = 0;
	return (env);
}


void	add_env(t_env **lstenv, t_env *env)
{
	while (*lstenv && (*lstenv)->next)
		(*lstenv) = (*lstenv)->next;
	if (env)
	{
		if (*lstenv)
			(*lstenv)->next = env;
		env->prev = *lstenv;
		env->next = 0;
		(*lstenv) = env;
	}
}

void	env_init(t_env **lstenv, char **env)
{
	char	**env_tmp;

	*lstenv = 0;
	env_tmp = env;
	while (*env_tmp)
	{
		add_env(lstenv, env_new(*env_tmp));
		env_tmp++;
	}
	while ((*lstenv)->prev)
		(*lstenv) = (*lstenv)->prev;
	return ;
}

int		ft_env(char **argv, t_env **lstenv)
{
	t_env	*tmp;

	tmp = *lstenv;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
