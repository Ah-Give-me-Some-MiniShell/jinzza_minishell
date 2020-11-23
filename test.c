/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minckim <minckim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:10:03 by minckim           #+#    #+#             */
/*   Updated: 2020/11/20 15:16:50 by minckim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int	main()
{
	int		pid;
	int		status;
	int		fd[2];

	if (pipe(fd))
		printf("pipe failed\n");
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], 1);
		while (1)
			printf("a");
	}
	else
	{
		// waitpid(pid, &status, 0);
		char	*argv[] = {"h", 0};
		int		n;
		char	buffer[10];
		dup2(fd[0], 0);
		close(fd[1]);
		// execve("/usr/bin/grep", argv, 0);
		while ((n = read(0, buffer, 10)))
			write(1, buffer, n);
	}
}

