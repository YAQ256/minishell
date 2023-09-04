/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:01:44 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/04 16:33:51 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_heredoc_write(char *ln, int file, t_env **envs)
{
	char	*var;
	int		start;
	int		j;

	j = 0;
	while (ln[j])
	{
		if (ln[j] == '$')
		{
			j++;
			start = j;
			while (ln[j] && ln[j] != 32 && ln[j] != '"' && ln[j] != '\'')
				j++;
			var = ft_substr(ln, start, (j - start));
			ft_putstr_fd(find_env_node(envs, var)->value, file);
		}
		else
			write(file, &ln[j++], 1);
	}
	write(file, "\n", 1);
}

void	ft_heredoc(struct s_cmd *ps, int file, t_env **envs)
{
	char	*line;
	int		i;

	i = 0;
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, ps->dl_hd[i], ft_strlen(line) + 1) == 0)
			i++;
		else if (!ps->dl_hd[i + 1])
			ft_heredoc_write(line, file, envs);
		if (!ps->dl_hd[i])
			break ;
		free(line);
		line = readline("> ");
	}
	free(line);
}

char	*ft_temp_name(void)
{
	char	*name;
	char	*num;
	int		i;

	i = 0;
	while (i != 2147483647)
	{
		num = ft_itoa(i);
		if (!num)
			return (NULL);
		name = ft_strjoin("/tmp/hd_", num);
		if (!name)
			return (NULL);
		free(num);
		if (access(name, F_OK) != 0)
			return (errno = 0, name);
		free(name);
		i++;
	}
	return (NULL);
}

void	ft_init_heredoc(struct s_cmd *ps, t_env **envs)
{
	int		fd;
	int		i;

	i = 0;
	sig_heredoc();
	while (ps)
	{
		if (ps->infile && ps->infile[0][1] == '<' && ps->infile[0][0] == '<')
		{
			ps->pth_hd = ft_temp_name();
			if (!ps->pth_hd)
				g_minishell.exit_status = 1;
			fd = ft_open(ps->pth_hd, O_WRONLY | O_CREAT | O_TRUNC);
			ft_heredoc(ps, fd, envs);
			close(fd);
		}
		ps = ps->next;
	}
	sig_parent();
}
