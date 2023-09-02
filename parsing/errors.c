/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:27:54 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 08:32:24 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_unexpected(char *token, size_t len)
{
	char	*str;

	str = ft_substr(token, 0, len);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(str);
}

static bool	check_tokens(char **tokens, int i)
{
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (tokens[i + 1] && tokens[i][0] == tokens[i + 1][0])
				return (error_unexpected(tokens[i + 1], 1
						+ (tokens[i][0] == '<' || tokens[i][0] == '>')), false);
			if (tokens[i][0] == '|' && (i == 0 || !tokens[i - 1]
					|| tokens[i - 1][0] == '|' || tokens[i - 1][0] == '>'
					|| tokens[i - 1][0] == '<'))
				return (error_unexpected("|", 1), false);
			if ((tokens[i][0] == '<' || tokens[i][0] == '>') && !tokens[i + 1])
				return (true);
			if ((tokens[i][0] == '<' || tokens[i][0] == '>') && tokens[i + 1]
				&& (tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>'))
				return (error_unexpected(tokens[i + 1], 1), false);
		}
		i++;
	}
	return (true);
}

static bool	check_newline(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!tokens[i + 1] || (tokens[i][0] == '<'
				&& tokens[i + 1][0] == '>'))
				return (true);
		}
		i++;
	}
	return (true);
}

bool	handle_unexpected(char ***tokens)
{
	if (!check_tokens(*tokens, 0))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (false);
	}
	if (!check_newline(*tokens))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (false);
	}
	return (true);
}
