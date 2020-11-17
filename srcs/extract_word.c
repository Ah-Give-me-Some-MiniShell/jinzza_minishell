/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:19:10 by minckim           #+#    #+#             */
/*   Updated: 2020/11/17 15:51:09 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_flag.h"

// t_str	*extract_env(char **str, int *flag, t_env *lstenv)
// {
// 	char	*start;
// 	char	*key;
// 	t_str	*result;

// 	start = ++(*str);
// 	while (**str && (ft_isalnum(**str) || **str == '_'))
// 		(*str)++;
// 	key = ft_substr(start, 0, *str - start);
// 	while (lstenv)
// 	{
// 		if (ft_strcmp(key, lstenv->key))
// 		{
// 			lstenv = lstenv->next;
// 			continue ;
// 		}
// 		result = ft_str_new(lstenv->val);
// 		break ;
// 	}
// 	free(key);
// 	*flag ^= ENV;
// 	(*str)--;
// 	return (result);
// }

t_str	*extract_env(char **str, int *flag, t_env *lstenv)
{
	char	*start;
	char	*key;
	t_str	*result;

	start = ++(*str);
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	key = ft_substr(start, 0, *str - start);
	printf("[%s]\n", key);
	while (lstenv && ft_strcmp(key, lstenv->key))
		lstenv = lstenv->next;
	if (lstenv)
		result = ft_str_new(lstenv->val);
	else
		result = ft_str_new("");
	free(key);
	*flag ^= ENV;
	(*str)--;
	return (result);
}


t_str	*extract_redirection(char **str, int *flag, t_env *lstenv, int *type)
{
	t_str	*word;
	
	word = ft_str_new("");
	if (*flag & RE_IN)
		word = ft_str_join_free(word, ft_str_new("<"));
	if (*flag & RE_OUT)
		word = ft_str_join_free(word, ft_str_new(">"));
	if (*flag & RE_APP)
		word = ft_str_join_free(word, ft_str_new(">>"));
	if (*flag & RE_PIPE)
		word = ft_str_join_free(word, ft_str_new("|"));
	if (*flag & ENDLINE)
		word = ft_str_join_free(word, ft_str_new(";"));
	*type = *flag;
	*flag = 0;
	(*str)++;
	return (word);
}

void	pass_blank(char **str, int *flag, t_env *lstenv, int *type)
{
	while (**str && (*flag & BLANK))
	{
		check_flag(str, flag);
		if (!(*flag & BLANK))
			break ;
		(*str)++;
	}
}

t_str	*extract_word(char **str, int *flag, t_env *lstenv, int *type)
{
	int		c;
	t_str	*word;
	
	if (*flag & (RE_IN | RE_OUT | RE_APP | RE_PIPE | ENDLINE))
		return (extract_redirection(str, flag, lstenv, type));
	word = ft_str_new("");
	*type = 0;
	while (**str)
	{
		if ((c = check_flag(str, flag)))
			ft_str_append(word, c);
		else if (*flag & ENV)
			word = ft_str_join_free(word, extract_env(str, flag, lstenv));
		else if (*flag & (BLANK | RE_IN | RE_OUT | RE_APP | RE_PIPE | ENDLINE))
			break ;
		(*str)++;
	}
	pass_blank(str, flag, lstenv, type);
	if (*word->str || !**str)
		return (word);
	else
		return (ft_str_join_free(word, extract_word(str, flag, lstenv, type)));
}
