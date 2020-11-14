#include "minishell.h"

extern int	errno;

void	exe_del(t_exe *exe)
{
	ft_clear_array(exe->argv);
	ft_clear_array(exe->env);
	free(exe);
}

void	clear_arg(t_exe **exe_head)
{
	t_exe	*exe_curr;
	t_exe	*exe_pipe;
	t_exe	*tmp;

	exe_curr = *exe_head;
	while (exe_curr)
	{
		exe_pipe = exe_curr;
		while (exe_pipe)
		{
			tmp = exe_pipe->next;
			exe_del(exe_pipe);
			exe_pipe = tmp;
		}
		tmp = exe_curr->next;
		exe_del(exe_curr);
		exe_curr = tmp;
	}
	*exe_head = 0;
}

void	fd_connect(t_exe *exe, int *fd_tmp)
{
	if (exe->fd[0] != 0)
	{
		if (fd_tmp)
			fd_tmp[0] = dup(0);
		dup2(exe->fd[0], 0);
	}
	if (exe->fd[1] != 1)
	{
		if (fd_tmp)
			fd_tmp[1] = dup(1);
		dup2(exe->fd[1], 0);
	}
}

void	fd_disconnect(t_exe *exe, int *fd_tmp)
{
	if (exe->fd[0] != 0)
	{
		close(exe->fd[0]);
		if (fd_tmp)
		{
			dup2(fd_tmp[0], 0);
			close(fd_tmp[0]);
		}
	}
	if (exe->fd[1] != 1)
	{
		close(exe->fd[1]);
		if (fd_tmp)
		{
			dup2(fd_tmp[1], 0);
			close(fd_tmp[1]);
		}
	}
}

int		check_path(char *path, t_exe *exe)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*tmp;

	if (!(dir = opendir(path)))
		return (1);
	while ((dp = readdir(dir)))
	{
		if (ft_strcmp(exe->argv[0], dp->d_name))
			continue ;
		else
		{
			tmp = exe->argv[0];
			exe->argv[0] = ft_strjoin(path, exe->argv[0]);
			free(tmp);
			return (0);
		}
	}
	return (1);
}

void	find_path(t_exe *exe, t_env *lstenv)
{
	char			**path;
	char			**path_head;

	if (ft_strncmp(exe->argv[0], "./", 2) == 0)
		return ;
	while (lstenv && ft_strcmp(lstenv->key, "PATH"))
		lstenv = lstenv->next;
	if (!lstenv)
		return ;
	path = ft_split(lstenv->val, ':');
	path_head = path;
	while (*path && check_path(*path, exe))
	{
		path++;
	}
	ft_clear_array(path_head);
}

void	child_process(t_exe *exe, t_env *lstenv)
{
	fd_connect(exe, 0);
	find_path(exe, lstenv);
	exe->env = env_to_arr(lstenv);
	exe->ret = execve(exe->argv[0], exe->argv, exe->env);
	exit(exe->ret);
}

void	parent_process(t_exe *exe, t_env *lstenv)
{
	if (exe->pipe_next)
		exe->ret = execute_arg(exe->pipe_next, lstenv);
	exe->ret = waitpid(exe->pid, &exe->status, 0);
	if (exe->pipe_prev)
		kill(exe->pipe_prev->pid, SIGKILL);
	fd_disconnect(exe, 0);
}

void	*is_builtin(char *path)
{
	if (ft_strcmp(path, "echo"))
		return (ft_echo);
	if (ft_strcmp(path, "env"))
		return (ft_echo);
	return (0);
}

int		execute_arg(t_exe *exe, t_env *lstenv)
{
	int		(*builtin_function)(char**, char**);
	int		fd_tmp[2];

	if ((builtin_function = is_builtin(exe->argv[0])))
	{
		fd_connect(exe, fd_tmp);
		exe->env = env_to_arr(lstenv);
		exe->ret = builtin_function(exe->argv, exe->env);
		if (exe->pipe_next)
			execute_arg(exe, lstenv);
		fd_disconnect(exe, fd_tmp);
		return (exe->ret);
	}
	if ((exe->pid = fork()) < 0)
		return (-1);
	else if (exe->pid == 0)
		child_process(exe, lstenv);
	else
		parent_process(exe, lstenv);
	if (exe->ret)
		return (exe->ret);
	else
		return (0);
}