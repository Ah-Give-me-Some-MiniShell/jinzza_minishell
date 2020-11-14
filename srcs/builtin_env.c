/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:37:56 by minckim           #+#    #+#             */
/*   Updated: 2020/11/11 17:43:31 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}

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

t_env	*env_new(char *str, t_env *current)
{
	t_env	*result;
	char	*start;

	if (!(result = malloc(sizeof(t_env))))
		return (0);
	start = str;
	while (*str && *str != '=')
		str++;
	if (!(result->key = ft_substr(start, 0, str - start)))
		return (0);
	start = ++str;
	while (*str)
		str++;
	if (!(result->val = ft_substr(start, 0, str - start)))
		return (0);
	if (current)
		current->next = result;
	result->prev = current;
	result->next = 0;
	return (result);
}

int		env_init(t_env **lstenv, char **env)
{
	char		*str;
	char		*str_start;
	extern int	errno;

	*lstenv = 0;
	while (*env)
	{
		if (!*lstenv)
		{
			if (!((*lstenv) = env_new(*env, 0)))
				return (errno);
		}
		else
		{
			if (!((*lstenv)->next = env_new(*env, (*lstenv))))
				return (errno);
			(*lstenv) = (*lstenv)->next;
		}
		env++;
	}
	while ((*lstenv)->prev)
		(*lstenv) = (*lstenv)->prev;
	return (0);
}