/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:29:04 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:37:43 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	skip_spaces(char *line, size_t *i)
{
	while (is_space(line[(*i)]))
		(*i)++;
}

int	skip_quotes(char *line)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] && line[i] != quote)
			i++;
	if (line[i] == quote)
		return (i + 1);
	return (-1);
}

bool	handle_quotes(char *line, size_t *i)
{
	int	skip;

	skip = skip_quotes(line + (*i));
	if (skip == -1)
		return (false);
	(*i) += skip;
	return (true);
}

void	increase_token_index(size_t *count, size_t *i)
{
	(*count)++;
	(*i)++;
}
