#include <unistd.h>
#define SIZE 1000

int		main()
{
	char	buffer[SIZE];
	int		n_read;

	n_read = read(0, buffer, SIZE);
	write(1, buffer, n_read);
}