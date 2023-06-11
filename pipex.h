/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:05:20 by margarida         #+#    #+#             */
/*   Updated: 2023/04/16 11:34:44 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

void	child_proc2(int *fd, char **paths, char **argv, char **env);
char	*check_paths(char **paths, char *cmd);
void	clear_paths(char **paths);
void	exec_child(char **paths, char *argv, char **env);
void	pipe_handling1(int unused, int inpipe, char *filename, int flags);
void	pipe_handling2(int unused, int outpipe, char *filename, int flags);

#endif