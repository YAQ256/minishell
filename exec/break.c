/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:35:56 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/02 10:24:32 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_path(t_cmd *ps, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;
	char	*path_cmd;
	
	i = ft_path(envp);
	env_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], "/");
		path_cmd = ft_strjoin(path, ps->cmd[0]);
		free(path);
		if (access(path_cmd, X_OK) == 0)
		{
			ps->pth_cmd = ft_strdup(path_cmd);
			free(path_cmd);
			ft_free_double(env_path);
			return (0); //exit
		}
		free(path_cmd);
	}
	ft_free_double(env_path);
	return (1); //fail
}

int	ft_check_cmd(struct s_cmd *ps, char **envp)
{
	if (access(ps->cmd[0], X_OK) != 0)
		return (ft_check_path(ps, envp));
	else
	{
		ps->pth_cmd = ft_strdup(ps->cmd[0]);
		if (!ps->pth_cmd)
			return (1); //mejorable
		return (0);
	}
}

void	ft_breack_check(struct s_cmd *ps, char **envp)
{
	if ((ps->cmd && !ps->cmd[0]) || (ft_check_cmd(ps, envp) != 0))
		error_st(ps->name_cmd, "command not found", 127);
	if (ps->infile && (!ps->infile[0] || !ps->infile[1]))
		perror ("falla el infile");//g_minishell.exit_status = 127;
	if (ps->outfile && (!ps->outfile[0] || !ps->outfile[1]))
		perror ("falla el outfile");//g_minishell.exit_status = 127;
	if (ps->infile && ps->infile[0][1] == '<' && ps->infile[0][0] == '<')
		if (ps->dl_hd && !ps->dl_hd[0])
			perror ("falla el heredoc, el dl");//g_minishell.exit_status = 127;		
}

void	ft_break_dl(struct s_cmd *ps, int *i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(sizeof(char), 1);
	if (!aux)
		return ;
	j = 0;
	while (ps->dl_hd && ps->dl_hd[j])
	{
		aux = ft_strjoin_gnl(aux, ps->dl_hd[j]);
		aux = ft_strjoin_gnl(aux, " ");
		free(ps->dl_hd[j]);
		j++;
	}
	free(ps->dl_hd);
	aux = ft_strjoin_gnl(aux, ps->args[*i + 1]);
	aux = ft_strjoin_gnl(aux, " ");
	ps->dl_hd = ft_split(aux, 32);
	free(aux);
}

void	ft_break_redir(struct s_cmd *ps, char **args, int *i) //no se para que esta la variable args, corrigelo cuando puedas.
{
	char	*aux;
	int		file;

	aux = ft_strjoin(args[*i], " ");
	aux = ft_strjoin_gnl(aux, args[*i + 1]);
	if (ps->args[*i][0] == '<')
	{
		if (ps->args[*i][1] == '<')
			ft_break_dl(ps, i);
		else if (access(args[*i + 1], F_OK) == -1)
			perror (args[*i]); //Gestionar mejor el error con exitstatus
		ps->infile = ft_split(aux, 32);
	}
	if (ps->args[*i][0] == '>')
	{
		ps->outfile = ft_split(aux, 32);
		file = ft_open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
		close(file);
	}
	(*i) += 2;
	free(aux);
	if ((ps->args[*i]) && (ps->args[*i + 1]) && (ps->args[*i][0] == '<' \
	|| ps->args[*i][0] == '>'))
		ft_break_redir(ps, args, i);
}

void	ft_init_break(struct s_cmd *ps, char **envp)
{
	char	*aux;
	int		i;

	while (ps)
	{
		aux = ft_calloc(sizeof(char), 1);
		if (!aux)
			return ;
		i = 0;
		while (ps->args[i])
		{
			if ((ps->args[i + 1]) && (ps->args[i][0] == '<' \
			|| ps->args[i][0] == '>'))
				ft_break_redir(ps, ps->args, &i);
			else
			{
				aux = ft_strjoin_gnl(aux, ps->args[i]);
				aux = ft_strjoin_gnl(aux, " ");
				i++;
			}
		}
		ps->cmd = ft_split(aux, 32);
		free(aux);
		ft_breack_check(ps, envp);
		ps = ps->next;
	}
}

/* void	ft_printf_list(struct s_cmd *t)
{
	int i;

	printf("\n----------\n");
	printf("Datos cmd:\n");
	printf("----------\n");
	printf("Cmd->");
	i = 0;
	while(t->cmd && t->cmd[i])
	{
		printf("%s ", t->cmd[i]);
		i++;
	}
	printf("\n");
	printf("infile-> ");
	i = 0;
	while(t->infile && t->infile[i])
	{
		printf("%s ", t->infile[i]);
		i++;
	}
	printf("\n");
	printf("outfile-> ");
	i = 0;
	while(t->outfile && t->outfile[i])
	{
		printf("%s ", t->outfile[i]);
		i++;
	}
	printf("\n");
	printf("delimitadores-> ");
	i = 0;
	while(t->dl_hd && t->dl_hd[i])
	{
		printf("%s ", t->dl_hd[i]);
		i++;
	}
	printf("\n");
} */
