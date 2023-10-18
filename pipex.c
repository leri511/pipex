/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:44:31 by hsievier          #+#    #+#             */
/*   Updated: 2023/07/26 15:44:33 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**str_cmd;
	char	*path;

	str_cmd = ft_split(cmd, ' ');
	path = take_path(str_cmd[0], envp);
	if (execve(path, str_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(str_cmd[0], 2);
		ft_free_s(str_cmd);
		exit(0);
	}
}

void	child(char **av, int *p_fd, char **envp)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec_cmd(av[2], envp);
}

void	parent(char **av, int *p_fd, char **envp)
{
	int		fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec_cmd(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child(av, p_fd, envp);
	parent(av, p_fd, envp);
}
