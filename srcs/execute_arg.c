#include "minishell.h"
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
	status == 1 ? ft_printf("Hangup: 1\n") : 0;
	status == 2 ? ft_printf("Interrupt: 2\n") : 0;
	status == 3 ? ft_printf("Quit: 3\n") : 0;
	status == 4 ? ft_printf("Illegal instruction: 4\n") : 0;
	status == 5 ? ft_printf("Trace/BPT trap: 5\n") : 0;
	status == 6 ? ft_printf("Abort trap: 6\n") : 0;
	status == 7 ? ft_printf("EMT trap: 7\n") : 0;
	status == 8 ? ft_printf("Floating point exception: 8\n") : 0;
	status == 9 ? ft_printf("Killed: 9\n") : 0;
	status == 10 ? ft_printf("Bus error: 10\n") : 0;
	status == 11 ? ft_printf("Segmentation fault: 11\n") : 0;
	status == 12 ? ft_printf("Bad system call: 12\n") : 0;
	status == 13 ? ft_printf("Broken pipe: 13\n") : 0;
	status == 14 ? ft_printf("Alarm clock: 14\n") : 0;
	return (0);
}

int		ft_strsignal_pt2(int status)
{
	status == 15 ? ft_printf("Terminated: 15\n") : 0;
	status == 16 ? ft_printf("Urgent I/O condition: 16\n") : 0;
	status == 17 ? ft_printf("Suspended (signal): 17\n") : 0;
	status == 18 ? ft_printf("Suspended: 18\n") : 0;
	status == 19 ? ft_printf("Continued: 19\n") : 0;
	status == 20 ? ft_printf("Child exited: 20\n") : 0;
	status == 21 ? ft_printf("Stopped (tty input): 21\n") : 0;
	status == 22 ? ft_printf("Stopped (tty output): 22\n") : 0;
	status == 23 ? ft_printf("I/O possible: 23\n") : 0;
	status == 24 ? ft_printf("Cputime limit exceeded: 24\n") : 0;
	status == 25 ? ft_printf("Filesize limit exceeded: 25\n") : 0;
	status == 26 ? ft_printf("Virtual timer expired: 26\n") : 0;
	status == 27 ? ft_printf("Profiling timer expired: 27\n") : 0;
	status == 28 ? ft_printf("Window size changes: 28\n") : 0;
	status == 29 ? ft_printf("Information request: 29\n") : 0;
	return (0);
}

int		execute_shell(t_exe *exe, t_env **lstenv, int *ret)
{
	int		(*builtin)();

	if ((builtin = is_builtin(exe->argv[0])) && (builtin != ft_echo))
		return (builtin(exe->argv, lstenv));
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
			exit(builtin(exe->argv, lstenv));
		path_finder(&exe->argv[0], lstenv);
		exe->ret = execve(exe->argv[0], exe->argv, env_to_arr(*lstenv));
		ft_printf("%s\n", strerror(get_errno()));
		exit(exe->ret);
	}
	else
	{
		if (exe->next)
			execute_shell(exe->next, lstenv, ret);
		waitpid(exe->pid, &exe->status, 0);
		if (!exe->next)
		{
			exe->status > 14 ? \
			ft_strsignal_pt1(exe->status) : ft_strsignal_pt1(exe->status);
			*ret = WEXITSTATUS(exe->status);
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