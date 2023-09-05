/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:25:07 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/05 19:54:44 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstlen(t_cmd *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char	*ft_strjoin_gnl(char *stash, char *buff)
{
	char	*str;
	int		i;
	int		j;

	if (!stash || !buff)
		return (NULL);
	str = ft_calloc(sizeof(char), ft_strlen(stash) + ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	free(stash);
	return (str);
}

void	cmds_has_pipes(t_cmd *cmds)
{
	t_cmd	*head;

	head = cmds;
	while (head)
	{
		head->has_pipe = true;
		head = head->next;
	}
}

void	ft_free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_cmd(t_cmd **cmds, char **envp)
{
	t_cmd	*ps;

	ps = *cmds;
	if (envp)
		ft_free_double(envp);
	while (ps)
	{
		if (ps->cmd)
			ft_free_double(ps->cmd);
		if (ps->infile)
			ft_free_double(ps->infile);
		if (ps->outfile)
			ft_free_double(ps->outfile);
		if (ps->dl_hd)
			ft_free_double(ps->dl_hd);
		if (ps->pth_cmd)
			free(ps->pth_cmd);
		if (ps->pth_hd)
		{
			if (access(ps->pth_hd, F_OK) != -1)
				unlink(ps->pth_hd);
			free(ps->pth_hd);
		}
		ps = ps->next;
	}
}
