/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:23:14 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/05 19:56:43 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		perror(file);
	return (fd);
}

void	ft_infile(t_cmd *ps, int std)
{
	if (ps->infile && ps->infile[0][0] == '<')
	{
		if (ps->infile && ps->infile[0][1] == '<' && ps->infile[0][0] == '<')
			std = ft_open(ps->pth_hd, O_RDONLY);
		else
			std = ft_open(ps->infile[1], O_RDONLY);
		dup2(std, STDIN_FILENO);
		close(std);
	}
	else if (std != STDIN_FILENO)
	{
		dup2(std, STDIN_FILENO);
		close(std);
	}
}

void	ft_outfile(t_cmd *ps, int std)
{
	if (ps->outfile && ps->outfile[0][0] == '>')
	{
		if (ps->outfile[0][1] == '>' && ps->outfile[0][0] == '>')
			std = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_APPEND);
		else
			std = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(std, STDOUT_FILENO);
		close(std);
	}
	else if (std != STDOUT_FILENO)
	{
		dup2(std, STDOUT_FILENO);
		close(std);
	}
}
