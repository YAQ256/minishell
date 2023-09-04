/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:18:33 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:37:00 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**init_args(char **tokens, size_t start, size_t end)
{
	char	**args;
	size_t	i;

	args = (char **)ft_calloc(sizeof(char *), end - start + 1);
	if (!args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		args[i] = ft_strdup(tokens[start + i]);
		i++;
	}
	return (args);
}

t_cmd	*new_cmd(char **tokens, size_t start, size_t end)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->has_pipe = false;
	cmd->next = NULL;
	cmd->args = init_args(tokens, start, end);
	if (!cmd->args || !cmd->args[0])
		return (free_cmds(cmd), NULL);
	cmd->name_cmd = cmd->args[0];
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

/* void	ft_free_lst_cmd(t_cmd **cmds, char **envp)
{
	struct s_cmd	*n;
	struct s_cmd	*aux;

	n = *cmds;
	if (envp)
		ft_free_double(envp);
	while (n)
	{
		if (n->args)
			ft_free_double(n->args);
		if (n->cmd)
			ft_free_double(n->cmd);
		if (n->infile)
			ft_free_double(n->infile);
		if (n->outfile)
			ft_free_double(n->outfile);
		if (n->dl_hd)
			ft_free_double(n->outfile);
		if (n->pth_hd)
			free(n->pth_hd);
		if (n->name_cmd)
			free(n->name_cmd);
		aux = n;
		n = n->next;
		free(aux);
	}
} */
