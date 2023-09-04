/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:35:56 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/04 17:20:12 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_cmd(struct s_cmd *ps, char **envp)
{
	if (g_minishell.exit_status == 0)
	{
		if ((ps->cmd && !ps->cmd[0]))
			error_st(ps->name_cmd, "command not found", 127);
		else if ((ps->cmd && ps->cmd[0]) && (access(ps->cmd[0], X_OK) != 0))
			ft_check_path(ps, envp);
		else
		{
			ps->pth_cmd = ft_strdup(ps->cmd[0]);
			if (!ps->pth_cmd)
				g_minishell.exit_status = 127;
		}
	}
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

void	ft_break_redir(struct s_cmd *ps, char **args, int *i, char *aux)
{
	int		file;

	if (ps->args[*i][0] == '<')
	{
		if (ps->infile)
			ft_free_double(ps->infile);
		ps->infile = ft_split(aux, 32);
		if (ps->args[*i][1] == '<')
			ft_break_dl(ps, i);
		else if (access(args[*i + 1], F_OK) == -1)
			error_st(ps->args[*i + 1], "No such file or directory", 1);
	}
	else if (ps->args[*i][0] == '>')
	{
		if (ps->outfile)
			ft_free_double(ps->outfile);
		ps->outfile = ft_split(aux, 32);
		if (ps->args[*i][1] == '>')
			file = ft_open(args[*i + 1], O_WRONLY | O_CREAT | O_APPEND);
		else
			file = ft_open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
		close(file);
	}
}

void	ft_check_redir(struct s_cmd *ps, int *i)
{
	char	*aux;

	if (!ps->args[*i + 1])
		g_minishell.exit_status = 258;
	else
	{
		aux = ft_strjoin(ps->args[*i], " ");
		aux = ft_strjoin_gnl(aux, ps->args[*i + 1]);
		ft_break_redir(ps, ps->args, i, aux);
		free(aux);
		(*i) += 2;
	}
}

void	ft_init_break(struct s_cmd *ps, char **envp)
{
	char	*aux;
	int		i;

	while (ps && g_minishell.exit_status == 0)
	{
		aux = ft_calloc(sizeof(char), 1);
		if (!aux)
			return ;
		i = 0;
		while (ps->args[i] && g_minishell.exit_status == 0)
		{
			if ((ps->args[i][0] == '<' || ps->args[i][0] == '>'))
				ft_check_redir(ps, &i);
			else
			{
				aux = ft_strjoin_gnl(aux, ps->args[i]);
				aux = ft_strjoin_gnl(aux, " ");
				i++;
			}
		}
		ps->cmd = ft_split(aux, 32);
		free(aux);
		ft_check_cmd(ps, envp);
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
