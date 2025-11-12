/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 07:16:06 by asoria            #+#    #+#             */
/*   Updated: 2025/11/12 09:07:08 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	manage_fork(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		close(pipex->tube[0]);
		first_child(pipex, argv, envp);
	}
	if (pipex->pid1 > 0)
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == 0)
		{
			close(pipex->tube[1]);
			second_child(pipex, argv, envp);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		errmsg("Error: wrong number of arguments\n", 1);
	if (pipe(pipex.tube) < 0)
		errmsg("Error: pipe creation failed\n", 4);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		errmsg("Error: couldn't open file\n", 2);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex.outfile < 0)
		errmsg("Error: couldn't create outfile\n", 3);
	manage_fork(&pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
