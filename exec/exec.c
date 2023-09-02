/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:36 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/02 08:08:50 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_cmd(struct s_cmd *ps, char **envp)
{
	char	**pwd;
	char	*path;
	int		i;

	if (access(ps->cmd[0], F_OK) != 0)
	{
		pwd = ft_split(ft_path(envp), ':');
		if (!pwd)
			return (1); //No existe env
		i = -1;
		while (pwd[++i])
		{
			path = ft_strjoin(ft_strjoin(pwd[i], "/"), ps->cmd[0]);
			if (access(path, F_OK) == 0)
				break ;
			free(path);
		}
		ft_free_double(pwd);
		if (!path)
		{
			g_minishell.exit_status = 127;
			return (1); //No existe path
		}
	}
	ps->pth_cmd = ft_strdup(path);
	return	(0); //sale bien
} //liberar el path y el pwd */

void	ft_execute(struct s_cmd *ps, char **envp, int infile, int outfile)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		ft_infile(ps, infile);
		ft_outfile(ps, outfile);
		ft_cmd(ps, envp);
		if (execve(ps->pth_cmd, ps->cmd, envp) == -1)
			exit(0);
	}
}

int	ft_pipex(struct s_cmd *cmd, char **envp, int inhe)
{
	int	pipex[2];

	ft_pipe(pipex);
	ft_execute(cmd, envp, inhe, pipex[WRITE]);
	close(pipex[WRITE]);
	if (inhe != STDIN_FILENO)
		close(inhe);
	return (pipex[READ]);
}

void	ft_init_exec(t_cmd **cmds, t_env **env)
{
	char	**envp;
	int		file;
	int		len;
	t_cmd	*ps;

	ps = *cmds;
	envp = format_env(*env);
	len = ft_lstlen(ps);
	ft_break_down(ps);
	ft_init_heredoc(ps, env);
	file = STDIN_FILENO;
	while (ps)
	{
		if (is_builtin(ps))
			file = ft_builtin(ps, env, len);
		else if (!ps->next)
			ft_execute(ps, envp, file, STDOUT_FILENO);
		else
			file = ft_pipex(ps, envp, file);
		ps = ps->next;
	}
	if (file != STDIN_FILENO)
		close(file);
	ft_wait_for_childs();
	ft_free_cmd(cmds, envp);
}
