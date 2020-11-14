#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_env		*lstenv;
	t_arg	*arg;
	t_exe	*exe;
	int		size;

	env_init(&lstenv, env);
	while (1)
	{
		arg = get_command_line(lstenv);
		size = arg_rewind(&arg);
		while (arg)
		{
			printf("[%d|%s]\n", arg->type, arg->str->str);

			exe = build_exe_tree(&arg, size);
			// printf("[%s]main:exe->argv\n", exe->argv[0]);
			exe_clear(&exe);
			if (!(arg->next))
				break;
			arg = arg->next;
		}
		arg_clear(&arg);
	}
}
