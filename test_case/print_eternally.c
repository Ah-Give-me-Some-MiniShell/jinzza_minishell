#include <unistd.h>
int	main()
{
	while (1)
		write(1, "0", 1);
}