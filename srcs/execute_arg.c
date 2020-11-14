#include "minishell.h"

int	get_errno()
{
	extern int	errno;

	return (errno);
}

int		execute_shell(t_exe *exe)
{
	exe->pid = fork();
	if(exe->pid == 0)
	{
		if (exe->fd[0] != 0)
			dup2(exe->fd[0], 0);
		if (exe->fd[1] != 1)
			dup2(exe->fd[1], 1);
		
	}
}