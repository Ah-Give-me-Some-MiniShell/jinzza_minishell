#include "minishell.h"
#include "minishell_flag.h"

t_exe	*exe_new(t_exe *current, int arg_size)
{
	t_exe	*exe;

	if (!(exe = malloc(sizeof(t_exe))))
		return (0);
	if (current)
		current->next = exe;
	exe->prev = current;
	exe->next = 0;
	exe->argv = malloc(sizeof(char*) * (arg_size + 1));
	*exe->argv = 0;
	exe->fd[0] = 0;
	exe->fd[1] = 1;
	exe->ret = 0;
	return (exe);
}

void	arg_clear(t_arg **arg)
{
	if (!*arg)
		return ;
	if ((*arg)->prev)
		while ((*arg)->prev)
		{
			// printf("[%p]arg_clear_prev\n", (*arg));
			ft_str_del((*arg)->str);
			(*arg) = (*arg)->prev;
			free((*arg)->next);
		}
	else
		while ((*arg)->next)
		{
			// printf("[%p]arg_clear_next\n", (*arg));
			ft_str_del((*arg)->str);
			(*arg) = (*arg)->next;
			free((*arg)->prev);
		}
	if (*arg)
	{
		// printf("[%p]arg_clear_fine\n", (*arg));
		ft_str_del((*arg)->str);
		free((*arg));
		*arg = 0;
	}
}

int		arg_rewind(t_arg **arg)
{
	int		size;

	size = 0;
	if ((*arg))
		size++;
	while ((*arg) && (*arg)->prev)
	{
		*arg = (*arg)->prev;
		size++;
	}
	return (size);
}

void	exe_clear(t_exe **exe)
{
	if (!(*exe))
		return ;
	if ((*exe)->prev)
		while ((*exe)->prev)
		{
			// printf("[%p]exe_clear_prev\n", (*exe));
			// printf("[%p]argv\n", (*exe)->argv);
			// printf("[%p]argv[0]\n", (*exe)->argv[0]);
			free((*exe)->argv);
			(*exe) = (*exe)->prev;
			free((*exe)->next);
		}
	else
		while ((*exe)->next)
		{
			// printf("[%p]exe_clear_next\n", (*exe));
			// printf("[%p]argv\n", (*exe)->argv);
			// printf("[%p]argv[0]\n", (*exe)->argv[0]);
			free((*exe)->argv);
			(*exe) = (*exe)->next;
			free((*exe)->prev);
		}
	if (*exe)
	{
		// printf("[%p]exe_clear_fine\n", (*exe));
		// printf("[%p]argv\n", (*exe)->argv);
		// printf("[%p]argv[0]\n", (*exe)->argv[0]);
		// printf("[%s]argv[0]\n", (*exe)->argv[0]);
		free((*exe)->argv);
		free((*exe));
		*exe = 0;
	}
}

void	argv_append(t_exe *exe, t_arg *arg)
{
	char	**tmp;

	tmp = exe->argv;
	while (*tmp)
		tmp++;
	*tmp++ = arg->str->str;
	// printf("[%p][%s]append\n", tmp[-1], tmp[-1]);
	*tmp = 0;
}

t_exe	*build_exe_tree(t_arg **arg, int arg_size)
{
	t_exe	*exe;
	int		fd[2];

	exe = 0;
	exe = exe_new(exe, arg_size);
	while ((*arg) && *(*arg)->str->str)
	{
		if ((*arg)->type == RE_IN)
		{
			if (exe->fd[0] != 0)
				close(exe->fd[0]);
			if ((exe->fd[0] = open((*arg)->str->str, O_RDONLY)) < 0)
			{
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == RE_OUT)
		{
			if (exe->fd[1] != 1)
				close(exe->fd[1]);
			if ((exe->fd[1] = \
			open((*arg)->str->str, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			{
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == RE_APP)
		{
			if (exe->fd[1] != 1)
				close(exe->fd[1]);
			if ((exe->fd[1] = \
			open((*arg)->str->str, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			{
				exe_clear(&exe);
				return (0);
			}
		}
		else if ((*arg)->type == RE_PIPE)
		{
			pipe(fd);
			exe->fd[1] = fd[1];
			exe = exe_new(exe, arg_size);
			exe->fd[0] = fd[0];

		}
		else if ((*arg)->type == ENDLINE)
		{
			break ;
		}
		else
		{
			// ft_putstr_fd(arg[0]->str->str, 1);
			argv_append(exe, *arg);
		}
		if ((*arg)->next)
			(*arg) = (*arg)->next;
		else
			break;
	}
	return (exe);
}

