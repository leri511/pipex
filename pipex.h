/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:44:43 by hsievier          #+#    #+#             */
/*   Updated: 2023/07/26 15:44:45 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //perror, strerror
# include <stdlib.h> //malloc, free
# include <unistd.h> // access, dup, dup2, unlink
# include <fcntl.h> //open, close, read, write
# include <string.h>
# include <sys/types.h> //execve, exit, fork, pipe
# include <sys/stat.h>
# include <sys/wait.h> //wait, waitpid

int		open_file(char *file, int in_or_out);
int		ft_strcmp(char *s1, char *s2);
char	*take_envp(char *name, char **envp);
char	*take_path(char *cmd, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	exec_cmd(char *cmd, char **envp);
void	ft_free_s(char **tab);
void	exit_handler(int n_exit);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);

#endif