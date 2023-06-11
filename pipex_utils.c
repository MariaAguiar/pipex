/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:11:04 by margarida         #+#    #+#             */
/*   Updated: 2023/04/29 09:58:57 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	pipe_handling2(int unused, int outpipe, char *filename, int flags)
{
	int		files;

	close(unused);
	dup2(outpipe, STDIN_FILENO);
	files = open(filename, flags, 0777);
	dup2(files, STDOUT_FILENO);
	close(files);
}

void	child_proc2(int *fd, char **paths, char **argv, char **env)
{
	int		pid2;

	wait(NULL);
	pipe_handling2(fd[1], fd[0], argv[4], O_WRONLY | O_TRUNC | O_CREAT);
	pid2 = fork();
	if (pid2 == -1)
		return ;
	else if (pid2 == 0)
		exec_child(paths, argv[3], env);
	else
		wait(NULL);
}

void	clear_paths(char **paths)
{
	int	i;

	i = -1;
	if (paths)
	{
		while (paths[++i])
		{
			*paths[i] = 0;
			free(paths[i]);
		}
		free(paths);
	}
}
