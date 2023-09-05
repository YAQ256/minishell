/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:37:38 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/05 20:44:24 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_st("fork:", "Cannot allocate memory", 1);
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		error_st("pipe:", "Too many open files", 1);
}

int	ft_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
		g_minishell.exit_status = 127;
	return (i);
}

void	ft_wait_for_childs(void)
{
	int status;
	
	sig_ignore();
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (WTERMSIG(status) == 3)
				g_minishell.exit_status = (128 + 3);
			if (WIFSIGNALED(status))
				write(1, "\n", 1);
			break;
		}
	}
}

void	ft_wait_for_heredoc(t_cmd *ps, pid_t	pid)
{
	int	fd;
	int	status;

	sig_ignore();
	waitpid(pid, &status, 0);
	if (!WEXITSTATUS(status))
	{
		if (access(ps->pth_hd, F_OK) != -1)
		{
			fd = ft_open(ps->pth_hd, O_WRONLY | O_CREAT | O_TRUNC);
			close(fd);
		}
	}
	sig_parent();
}
