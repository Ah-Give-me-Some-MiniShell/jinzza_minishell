/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:57:21 by minckim           #+#    #+#             */
/*   Updated: 2020/11/28 13:06:40 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_flag.h"

int		check_flag_s_quote(char c, int *flag)
{
	if (c == '\'')
	{
		*flag ^= S_QUOTE;
		return (0);
	}
	return (c);
}

int		check_flag_d_quote(char *c, int *flag)
{
	if (*c == '\"')
	{
		*flag ^= D_QUOTE;
		return (0);
	}
	if (*c == '$')
	{
		*flag |= ENV;
		return (0);
	}
	if (*c == '\\')
	{
		*flag |= ESCAPE;
		if (c[1] == '\"')
			return (0);
		return (*c);
	}
	return (*c);
}

int		check_flag_on(char **c, int *flag)
{
	*flag |= **c == ' ' || **c == '\t' ? BLANK : 0;
	*flag |= **c == '\'' ? S_QUOTE : 0;
	*flag |= **c == '\"' ? D_QUOTE : 0;
	*flag |= **c == '$' ? ENV : 0;
	*flag |= **c == '\\' ? ESCAPE : 0;
	*flag |= **c == '<' ? RE_IN : 0;
	*flag |= **c == '>' ? RE_OUT : 0;
	if ((*flag & RE_OUT) && (*(*c + 1) == '>'))
	{
		*flag &= ~RE_OUT;
		*flag |= RE_APP;
		(*c)++;
	}
	*flag |= **c == '|' ? RE_PIPE : 0;
	*flag |= **c == ';' ? ENDLINE : 0;
	*flag |= **c == ' ' ? BLANK : 0;
	if (*flag)
		return (0);
	else
		return (**c);
}

int		check_flag(char **c, int *flag)
{
	if (*flag & ESCAPE)
	{
		*flag ^= ESCAPE;
		if (**c == '\\')
			return (0);
		return (**c);
	}
	if (*flag & S_QUOTE)
		return (check_flag_s_quote(**c, flag));
	if (*flag & D_QUOTE)
		return (check_flag_d_quote(*c, flag));
	if (*flag & BLANK)
	{
		if (**c == ' ' || **c == '\t')
			return (0);
		*flag ^= BLANK;
		return (**c);
	}
	if (!*flag)
		return (check_flag_on(c, flag));
	return (**c);
}
