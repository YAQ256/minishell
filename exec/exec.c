/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:36 by saazcon-          #+#    #+#             */
/*   Updated: 2023/08/09 20:14:31 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printf_list(struct s_cmd *t)
{
	int i;

	printf("----------\n");
	printf("Datos cmd:\n");
	printf("----------\n");
	printf("Full Cmd-> %s\n", t->full_cmd); //errores de esta mierda
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
}

void	ft_churro(struct s_cmd	*t)
{
	int	i;

	i = 0;
	t->full_cmd = ft_calloc(sizeof(char), 1); //hay que reservar o se vuelve loco
	while (t->args[i] && t->args[i][0] != '<' && t->args[i][0] != '>')
	{
		t->full_cmd = ft_strjoin_gnl(t->full_cmd, t->args[i]);
		t->full_cmd = ft_strjoin_gnl(t->full_cmd, " ");
		i++;
	}
	if(t->args[i] && t->args[i][0] == '<')
	{
		t->infile = ft_calloc(sizeof(char *), 3);
		t->infile[0] = ft_strdup(t->args[i]);
		i++;
		while(t->args[i] && t->args[i][0] != '>')
		{
			if(!access(t->args[i], F_OK))
				printf("%s no existe bro", t->args[i]);
			else
				t->infile[1] = strdup(t->args[i]);
			i++;
		}
	}
	if(t->args[i] && t->args[i][0] == '>')
	{
		t->outfile = ft_calloc(sizeof(char *), 3);
		t->outfile[0] = ft_strdup(t->args[i]);
		t->outfile[1] = ft_strdup(t->args[i + 1]);
		i += 2;
		while(t->args[i])
		{
			if(!access(t->args[i], F_OK))
				printf("%s no existe bro", t->args[i]);
			i++;
		}
	}
}

int	ft_open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		return(0); //Debemos gestinar los errores.
	return (fd);
}

void	ft_redir(struct s_cmd	*ps)
{
	int file;

	if (ps->outfile && ps->outfile[0][0] == '>')
	{
		if (ps->outfile[0][1] == '>')
			file = open(ps->outfile[1], O_WRONLY | O_CREAT | O_APPEND);
		else
			file = open(ps->outfile[1], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	if (ps->infile && ps->infile[0][0] == '<')
	{
		if (ps->infile[0][1] == '<')
			ft_heredoc(ps->infile[1]); //dilimitador. //Peta
		else
		{
			file = open(ps->infile[1], O_RDONLY);
			dup2(file, STDIN_FILENO);
			close(file);
		}
	}
}

void	ft_pipex(struct s_cmd	*ps, t_env **envs)
{	
	pid_t	ps_id;
	int 	pipex[2];

	(void)envs; //quitar
	if (pipe(pipex) == -1)
		return ;
	ps_id = fork();
	if (ps_id == -1)
		return ;
	else if (ps_id == 0)
	{
		close(pipex[READ]);
		if (!ps->outfile)
			dup2(pipex[WRITE], STDOUT_FILENO);
		close(pipex[WRITE]);
		write(pipex[WRITE] , "Nace un hijo -> ps iniciado.\n", 29);
	}
	close(pipex[WRITE]);
	dup2(pipex[READ], STDIN_FILENO);
	close(pipex[READ]);
}

void	init_pipex(t_cmd **cmds, t_env **envs)
{
	struct s_cmd	*ps;
	//int 			i;

	(void)envs;
	ps = *cmds;
	while(ps)
	{
		ft_churro(ps);
		ft_printf_list(ps);
		ps = ps->next;
	}
	ps = *cmds;
	while(ps)
	{
		ft_redir(ps);
		ft_pipex(ps, envs);
		ps = ps->next;
	}
	//2. procesa info (costante)
	//3. muestra info (final)
	//ps = ps->next;*/
}


