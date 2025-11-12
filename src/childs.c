/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:27:03 by asoria            #+#    #+#             */
/*   Updated: 2025/11/12 09:20:35 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->infile < 0)
		exit(1);
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->tube[1], STDOUT_FILENO);
	close_pipes(pipex);
	close(pipex->infile);
	execute(argv[2], envp);
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->outfile < 0)
		exit(1);
	dup2(pipex->tube[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close_pipes(pipex);
	close(pipex->outfile);
	execute(argv[3], envp);
}
