/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 07:04:08 by asoria            #+#    #+#             */
/*   Updated: 2025/11/12 09:08:33 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../includes/pipex.h" */
#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct s_pipex
{
	int	pid1;
	int	pid2;
	int	infile;
	int	outfile;
	int	tube[2];
}	t_pipex;

/* childs.c */
void	first_child(t_pipex *pipex, char **argv, char **enpv);
void	second_child(t_pipex *pipex, char **argv, char **enpv);

/* utils.c */
void	execute(char *argv, char **envp);
void	close_pipes(t_pipex *pipex);
void	errmsg(char *error_message, int errno);
char	*find_path(char *cmd, char **envp);
#endif
