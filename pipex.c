/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:04:48 by margarida         #+#    #+#             */
/*   Updated: 2023/04/29 09:58:59 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*check_paths(char **paths, char *cmd)
{
	int		i;

	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(paths[i], F_OK) == 0)
			break ;
	}
	if (!paths[i])
	{
		write(2, "command not found: ", 19);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		return (0);
	}
	return (paths[i]);
}

void	exec_child(char **paths, char *argv, char **env)
{
	char	**arr;

	arr = NULL;
	arr = ft_split(argv, ' ');
	if (!check_paths(paths, arr[0]))
		clear_paths(arr);
	else if (execve(check_paths(paths, arr[0]), arr, env) == -1)
	{
		clear_paths(paths);
		clear_paths(arr);
	}
}

void	pipe_handling1(int unused, int inpipe, char *filename, int flags)
{
	int		files;

	close(unused);
	files = open(filename, flags, 0777);
	dup2(files, STDIN_FILENO);
	dup2(inpipe, STDOUT_FILENO);
	close(inpipe);
}

static char	**get_paths(char **env)
{
	char	**paths;

	while (*env[0] != 'P' || !ft_strnstr(*env, "PATH=/", ft_strlen(*env)))
		env++;
	*env += 5;
	paths = ft_split(*env, ':');
	return (paths);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		pid;
	char	**paths;

	if (argc == 5)
	{
		paths = get_paths(env);
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (2);
		else if (pid == 0)
		{
			pipe_handling1(fd[0], fd[1], argv[1], O_RDONLY);
			exec_child(paths, argv[2], env);
		}
		else
			child_proc2(fd, paths, argv, env);
		clear_paths(paths);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
