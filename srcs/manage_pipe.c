#include "minishell.h"

void	manage_pipe(t_exe *exe, int	size)
{
	t_exe	*head;
	char	flag_exit;

	head = exe;
	flag_exit = 1;
	while (flag_exit)
	{
		exe = head;
		while (exe)
		{
			waitpid(exe->pid, &exe->status, WNOHANG);
			if (WIFEXITED(exe->status))
			{
				printf("in\n");
				if (exe->fd[0] != 0)
					close(exe->fd[0]);
				if (exe->fd[1] != 1)
					close(exe->fd[1]);
				flag_exit = 0;
			}
			else
				flag_exit = 1;	
			exe = exe->next;
		}
		printf("out\n");
	}
}