/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilita.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:44:56 by hsievier          #+#    #+#             */
/*   Updated: 2023/08/14 15:47:35 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ret == -1)
	{
		ft_putstr_fd("zsh: permission denied:\n", 2);
		exit(1);
	}
	return (ret);
}

void	ft_free_s(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*take_envp(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*take_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	**vse_path;
	char	*pic_part;
	char	**str_cmd;

	i = -1;
	vse_path = ft_split(take_envp("PATH", envp), ':');
	str_cmd = ft_split(cmd, ' ');
	while (vse_path[++i])
	{
		pic_part = ft_strjoin(vse_path[i], "/");
		exec = ft_strjoin(pic_part, str_cmd[0]);
		free(pic_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_s(str_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_s(vse_path);
	ft_free_s(str_cmd);
	return (cmd);
}
