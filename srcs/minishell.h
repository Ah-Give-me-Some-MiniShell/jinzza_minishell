/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:02:02 by minckim           #+#    #+#             */
/*   Updated: 2020/11/26 20:03:52 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <unistd.h>
# define MINISHELL_OK	0
# define MINISHELL_ERR	1
# define MINISHELL_PREV	0
# define MINISHELL_NEXT	1

typedef struct		s_arg
{
	struct s_arg	*prev;
	struct s_arg	*next;
	t_str			*str;
	int				type;
}					t_arg;

typedef struct		s_task
{
	struct s_task	*prev;
	struct s_task	*next;
	char			**argv;
	int				fd[2];
	int				pipe_fd[2];
	int				ret;
	int				status;
	int				is_exit;
	pid_t			pid;
}					t_task;

typedef struct		s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*key;
	char			*val;
}					t_env;

/*
**	===========================================================================
**	minishell.c ---------------------------------------------------------------
*/
void				print_prompt(int option);
/*
**	get_command_line.c --------------------------------------------------------
*/
int					check_syntax(t_arg **arg);
t_arg				*get_command_line(t_env *lstenv);
/*
**	check_flag.c --------------------------------------------------------------
*/
int					check_flag(char **c, int *flag);
/*
**	extract_word.c ------------------------------------------------------------
*/
t_str				*extract_word(\
							char **str, int *flag, t_env *lstenv, int *type);
/*
**	build_task_tree.c ---------------------------------------------------------
*/
t_task				*task_new(t_task *current, int arg_size);
t_task				*build_task_tree(t_arg **arg, int arg_size);
int					arg_rewind(t_arg **arg);
void				argv_append(t_task *task, t_arg *arg);
/*
**	path_finder.c -------------------------------------------------------------
*/
int					path_finder(char **file, t_env **lstenv);
/*
**	redirection_manage.c ------------------------------------------------------
*/
int					redirection_manage\
									(t_task **task, t_arg **arg, int arg_size);
/*
**	execute_task.c ------------------------------------------------------------
*/
void				execute_task(t_task *task, t_env **lstenv);
/*
**	process_terminater.c ------------------------------------------------------
*/
void				arg_clear(t_arg **arg);
void				task_clear(t_task **task);
int					return_value(int option, int set_num);
void				process_terminater(t_task *task);
/*
**	error_handler.c -----------------------------------------------------------
*/
void				print_err(char *str);
int					ft_strsignal_pt1(int status);
int					ft_strsignal_pt2(int status);
void				handler_signal(int signo);
/*
**	===========================================================================
**	builtin function
**	builtin_env.c -------------------------------------------------------------
*/
t_env				*env_new(char *str);
void				env_init(t_env **lstenv, char **env);
char				**env_to_arr(t_env *env);
int					ft_env(char **argv, t_env **lstenv);
/*
**	builtin_echo.c ------------------------------------------------------------
*/
int					ft_echo(char **argv, t_env **lstenv);
/*
**	builtin_cd.c --------------------------------------------------------------
*/
int					ft_cd(char **argv, t_env **lstenv);
/*
**	builtin_pwd.c -------------------------------------------------------------
*/
int					ft_pwd(char **argv, t_env **lstenv);
/*
**	builtin_export.c ----------------------------------------------------------
*/
int					add_val(char *str, t_env **lstenv);
int					ft_export(char **argv, t_env **lstenv);
/*
**	builtin_unset.c -----------------------------------------------------------
*/
int					ft_unset(char **argv, t_env **lstenv);
/*
**	builtin_exit.c ------------------------------------------------------------
*/
int					ft_exit(char **argv, t_env **lstenv);

#endif
