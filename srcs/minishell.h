#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <unistd.h>
# define BUILTIN	"echo cd pwd export unset env exit"

typedef struct		s_arg
{
	struct s_arg	*prev;
	struct s_arg	*next;
	t_str			*str;
	int				type;
}					t_arg;

typedef struct		s_exe
{
	struct s_exe	*prev;
	struct s_exe	*next;
	char			**argv;
	int				fd[2];
	int				errno;
	int				ret;
	int				status;
	pid_t			pid;
}					t_exe;

typedef struct		s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*key;
	char			*val;
}					t_env;

int		print_env();
/*
**	===========================================================================
**	extract_word.c
*/
t_str	*extract_word(char **str, int *flag, t_env *lstenv, int *type);
/*
**	===========================================================================
**	get_command_line.c
*/
t_arg	*get_command_line(t_env *lstenv);
int		check_syntax(t_arg **arg);
/*
**	===========================================================================
**	check_flag.c
*/
int		check_flag(char **c, int *flag);
/*
**	===========================================================================
**	build_exe_tree.c
*/
t_exe	*build_exe_tree(t_arg **arg, int arg_size);
void	exe_clear(t_exe **exe);
int		arg_rewind(t_arg **arg);
void	arg_clear(t_arg **arg);

/*
**	===========================================================================
**	execute_arg.c
*/
int		get_errno();
int		execute_shell(t_exe *exe, t_env **lstenv);


/*
**	===========================================================================
**	builtin function
*/
/*
**	builtin_env.c -------------------------------------------------------------
*/
// t_env	*env_new(char *str, t_env *current);
t_env	*env_new(char *str);
int		print_env(t_env *env);
void	env_init(t_env **lstenv, char **env);
char	**env_to_arr(t_env *env);
int		ft_env(char **argv, t_env **lstenv);
/*
**	builtin_echo.c ------------------------------------------------------------
*/
int		ft_echo(char **argv, t_env **lstenv);
/*
**	builtin_cd.c --------------------------------------------------------------
*/
int		ft_cd(char **argv, t_env **lstenv);
/*
**	builtin_pwd.c -------------------------------------------------------------
*/
int		ft_pwd(char **argv, t_env **lstenv);
/*
**	builtin_export.c -------------------------------------------------------------
*/
int		ft_export(char **argv, t_env **lstenv);
/*
**	builtin_exit.c ------------------------------------------------------------
*/
ssize_t	ft_atoi_ssizet(char *str, int *flag);
int		ft_exit(char *8argv, t_env **lstenv);


#endif