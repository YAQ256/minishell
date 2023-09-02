/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:36 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/02 10:05:49 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(struct s_cmd *ps, char **envp, int infile, int outfile)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		ft_infile(ps, infile);
		ft_outfile(ps, outfile);
		//ft_cmd(ps, envp);
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
	len = ft_lstlen(ps);
	envp = format_env(*env);
	ft_init_break(ps, envp);
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
