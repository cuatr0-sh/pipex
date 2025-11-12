/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:35:46 by asoria            #+#    #+#             */
/*   Updated: 2025/11/12 09:37:26 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	errmsg(char *reason, int errorno)
{
	write(2, reason, ft_strlen(reason));
	exit(errorno);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	if (!argv || !*argv)
		exit(127);
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		if (cmd)
			free_split(cmd);
		exit(127);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_split(cmd);
		exit(126);
	}
}
