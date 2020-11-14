/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_flag.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:59:14 by minckim           #+#    #+#             */
/*   Updated: 2020/11/12 00:19:16 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FLAG_H
# define MINISHELL_FLAG_H
# define S_QUOTE	0x1
# define D_QUOTE	0x2
# define ESCAPE		0x4
# define ENV		0x8
# define RE_IN		0x10
# define RE_OUT		0x20
# define RE_APP		0x40
# define RE_PIPE	0x80
# define ENDLINE	0x100
# define BLANK		0x200
# define SYNTAX_ERR	0x400
#endif