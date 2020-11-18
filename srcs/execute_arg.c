#include "minishell.h"
#include "color.h"
// #define DEBUG


int	get_errno()
{
	extern int	errno;

	return (errno);
}

void	*is_builtin(char *path)
{
	if (!path)
		return (0);
	if (ft_strcmp(path, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(path, "env") == 0)
		return (ft_env);
	else if (ft_strcmp(path, "export") == 0)
		return (ft_export);
	else if (ft_strcmp(path, "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(path, "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(path, "exit") == 0)
		return (ft_exit);
	else
		return (0);
}

int		path_finder(char **file, t_env **lstenv)
{
	char			**path_vec;
	char			**path_vec_head;
	DIR				*dir;
	struct dirent	*dp;
	char			*tmp;

	if (ft_strncmp(*file, "/", 1) == 0)
		return (0);
	while (*lstenv && ft_strcmp((*lstenv)->key, "PATH"))
		*lstenv = (*lstenv)->next;
	if (!*lstenv)
		return (-1);
	path_vec = ft_split((*lstenv)->val, ':');
	path_vec_head = path_vec;
	while (*path_vec)
	{
		if (!(dir = opendir(*path_vec)))
		{
			path_vec++;
			continue;
		}
		while ((dp = readdir(dir)))
		{
			if (ft_strcmp(dp->d_name, *file) == 0)
			{
				*file = ft_strjoin_free(ft_strdup("/"), *file);
				*file = ft_strjoin_free(ft_strdup(*path_vec), *file);
				#ifdef DEBUG
				printf("[%s]path\n", *file);
				#endif
				ft_clear_array(path_vec_head);
				return (0);
			}
		}
		path_vec++;
		closedir(dir);
	}
	ft_clear_array(path_vec_head);
	return (-1);
}

int		ft_strsignal_pt1(int status)
{
	status == 1 ? ft_printf(I_RED"Hangup: 1\n"WHITE) : 0;
	status == 2 ? ft_printf(I_RED"Interrupt: 2\n"WHITE) : 0;
	status == 3 ? ft_printf(I_RED"Quit: 3\n"WHITE) : 0;
	status == 4 ? ft_printf(I_RED"Illegal instruction: 4\n"WHITE) : 0;
	status == 5 ? ft_printf(I_RED"Trace/BPT trap: 5\n"WHITE) : 0;
	status == 6 ? ft_printf(I_RED"Abort trap: 6\n"WHITE) : 0;
	status == 7 ? ft_printf(I_RED"EMT trap: 7\n"WHITE) : 0;
	status == 8 ? ft_printf(I_RED"Floating point exception: 8\n"WHITE) : 0;
	status == 9 ? ft_printf(I_RED"Killed: 9\n"WHITE) : 0;
	status == 10 ? ft_printf(I_RED"Bus error: 10\n"WHITE) : 0;
	status == 11 ? ft_printf(I_RED"Segmentation fault: 11\n"WHITE) : 0;
	status == 12 ? ft_printf(I_RED"Bad system call: 12\n"WHITE) : 0;
	status == 13 ? ft_printf(I_RED"Broken pipe: 13\n"WHITE) : 0;
	status == 14 ? ft_printf(I_RED"Alarm clock: 14\n"WHITE) : 0;
	return (0);
}

int		ft_strsignal_pt2(int status)
{
	status == 15 ? ft_printf(I_RED"Terminated: 15\n"WHITE) : 0;
	status == 16 ? ft_printf(I_RED"Urgent I/O condition: 16\n"WHITE) : 0;
	status == 17 ? ft_printf(I_RED"Suspended (signal): 17\n"WHITE) : 0;
	status == 18 ? ft_printf(I_RED"Suspended: 18\n"WHITE) : 0;
	status == 19 ? ft_printf(I_RED"Continued: 19\n"WHITE) : 0;
	status == 20 ? ft_printf(I_RED"Child exited: 20\n"WHITE) : 0;
	status == 21 ? ft_printf(I_RED"Stopped (tty input): 21\n"WHITE) : 0;
	status == 22 ? ft_printf(I_RED"Stopped (tty output): 22\n"WHITE) : 0;
	status == 23 ? ft_printf(I_RED"I/O possible: 23\n"WHITE) : 0;
	status == 24 ? ft_printf(I_RED"Cputime limit exceeded: 24\n"WHITE) : 0;
	status == 25 ? ft_printf(I_RED"Filesize limit exceeded: 25\n"WHITE) : 0;
	status == 26 ? ft_printf(I_RED"Virtual timer expired: 26\n"WHITE) : 0;
	status == 27 ? ft_printf(I_RED"Profiling timer expired: 27\n"WHITE) : 0;
	status == 28 ? ft_printf(I_RED"Window size changes: 28\n"WHITE) : 0;
	status == 29 ? ft_printf(I_RED"Information request: 29\n"WHITE) : 0;
	return (0);
}

int		execute_shell(t_exe *exe, t_env **lstenv)
{
	int		(*builtin)();

	if ((builtin = is_builtin(exe->argv[0])) && (builtin != ft_echo))
		return (return_value(1, builtin(exe->argv, lstenv)));
	#ifdef DEBUG
	printf("process: %s\n", exe->argv[0]);
	#endif
	exe->pid = fork();
	if(exe->pid == 0)
	{
		if (exe->fd[0] != 0)
			dup2(exe->fd[0], 0);
		if (exe->fd[1] != 1)
			dup2(exe->fd[1], 1);
		if ((builtin = is_builtin(exe->argv[0])))
		{
			exit(builtin(exe->argv, lstenv));
		}
		path_finder(&exe->argv[0], lstenv);
		exe->ret = execve(exe->argv[0], exe->argv, env_to_arr(*lstenv));
		ft_printf(I_RED"%s\n"WHITE, strerror(get_errno()));
		exit(exe->ret);
	}
	else
	{
		if (exe->next)
			execute_shell(exe->next, lstenv);
		waitpid(exe->pid, &exe->status, 0);
		if (!exe->next)
		{
			exe->status > 14 ? \
			ft_strsignal_pt1(exe->status) : ft_strsignal_pt1(exe->status);
			return_value(1, exe->status);
		}
		if (exe->prev)
			kill(exe->prev->pid, SIGKILL);
		if (exe->fd[0] != 0)
			close(exe->fd[0]);
		if (exe->fd[1] != 1)
			close(exe->fd[1]);
		return (WEXITSTATUS(exe->status));
	}
	return (0);
}