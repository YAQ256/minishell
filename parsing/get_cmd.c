/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:18:33 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/11 17:06:24 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**init_args(t_cmd *cmd, char **tokens, size_t start, size_t end)
{
	char	**args;
	size_t	i;
	(void)cmd;

	args = (char **)ft_calloc(sizeof(char *), end - start + 1);
	if (!args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		if (tokens[start + i][0] == '>' || tokens[start + i][0] == '<')
		{
			if (printf("iniciar las redirecciones\n"))
			{
				while (i > 0)
					free(args[--i]);
				free(args);
				return (NULL);
			}
			start += 2;
			continue ;
		}
		args[i] = ft_strdup(tokens[start + i]);
		i++;
	}
	return (args);
}

t_cmd	*new_cmd(char **tokens, size_t start, size_t end)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->has_heredoc = false;
	cmd->has_pipe = false;
	cmd->pid = -1;
	cmd->next = NULL;
	cmd->args = init_args(cmd, tokens, start, end);
	if (!cmd->args || !cmd->args[0])
		return (free_cmds(cmd), NULL);
	cmd->name = cmd->args[0];
	return (cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	last = *cmds;
	while (last->next)
		last = last->next;
	last->next = new;
}

char	*last_cmd_arg(t_cmd *cmds)
{
	size_t	i;

	while (cmds->next)
		cmds = cmds->next;
	i = 0;
	while (cmds->args[i])
		i++;
	return (cmds->args[i - 1]);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	size_t	i;

	//printf("cerrar redirecciones\n");
	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		i = 0;
		while (tmp->args && tmp->args[i])
			free(tmp->args[i++]);
		if (tmp->args)
			free(tmp->args);
		free(tmp);
	}
}
