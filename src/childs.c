/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:27:03 by asoria            #+#    #+#             */
/*   Updated: 2025/11/12 09:06:50 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->tube[1], STDOUT_FILENO);
	close_pipes(pipex);
	execute(argv[2], envp);
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->tube[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close_pipes(pipex);
	execute(argv[3], envp);
}
