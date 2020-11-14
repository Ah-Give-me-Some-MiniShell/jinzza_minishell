#include "minishell.h"

int	get_errno()
{
	extern int	errno;

	return (errno);
}

