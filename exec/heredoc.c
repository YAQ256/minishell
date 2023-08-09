/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:34:37 by saazcon-          #+#    #+#             */
/*   Updated: 2023/08/08 21:24:00 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_read_line(int fd, char *stash)
{
	char	*buff;
	int		readed;

	buff = ft_calloc(sizeof(char), 2);
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strrchr(buff, '\n') && readed != 0)
	{
		readed = read(fd, buff, 1);
		if (readed == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		buff[readed] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	line = ft_calloc(sizeof(char), 1);
	if (!line)
		return (NULL);
	line = ft_read_line(fd, line);
	return (line);
}
//Todo lo de arriba es un mini get_next_line, por si nos da pereza meter un file entero.

// Utilizo un pipe para gestionar la info que escriba el user y la 
// redirigo por la entrada por defecto del futuro proceso que se realice
// En general es redirigir datos de un punto a otro, ya sea con el write, el gnl o el dup2.
void	ft_heredoc(char *del)
{
	char	*line;
	int 	pipex[2];

	if (pipe(pipex) == -1)
		return ; //ft_error(v, "Error: Pipe Error:", 1);
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{ //debo gestionar el tema senales de ctrl
		if (ft_strncmp(del, line, ft_strlen(line) - 1) == 0)
			break ;
		write(pipex[WRITE], line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(pipex[WRITE]);
	//dup2(pipex[READ], STDIN_FILENO);
	close(pipex[READ]);
}