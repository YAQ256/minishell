/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:45:10 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/08/08 20:12:34 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# define HEREDOC_FILE ".heredoc"

# define WRITE	1
# define READ	0

typedef struct s_cmd
{
	char			**args;
	char			**infile; //bloque de entrada
	char			**outfile; //bloque de salida
	char			*name_cmd; //nombre del cmd sin comando
	char			*full_cmd; //cmd completo
	bool			has_pipe;//no lo uso
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd, t_env **envs);
}	t_builtin;

typedef struct s_minishell
{
	bool	force_exit;
	bool	heredoc; //para que tu quieres eso
	int		signal;
	t_env	*envs;
}	t_minishell;

extern t_minishell	g_minishell;

//==================builtins==================//
int		builtin_echo(t_cmd *cmd, t_env **envs);
int		builtin_env(t_cmd *cmd, t_env **envs);
void	exit_arg(t_cmd *cmd);
int		builtin_exit(t_cmd *cmd, t_env **envs);
int		builtin_pwd(t_cmd *cmd, t_env **envs);
int		builtin_unset(t_cmd *cmd, t_env **envs);
int		builtin_cd(t_cmd *cmd, t_env **envs);
int		builtin_export(t_cmd *cmd, t_env **envs);
void	error_identifier(char *identifier);
//==================parsing==================//
char	**format_env(t_env *envs);
bool	handle_unexpected(char ***tokens);
void	error(char *msg, char *more);
void	error_heredoc(char *delimiter);
void	error_write(char *cmd);
void	free_tokens(char **tokens);
t_cmd	*new_cmd(char **tokens, size_t start, size_t end);
void	add_cmd(t_cmd **cmds, t_cmd *new);
char	*last_cmd_arg(t_cmd *cmds);
void	free_cmds(t_cmd *cmds);
t_env	*get_env(t_env *envs, char *key);
t_env	*set_env(t_env **envs, char *key, char *value);
t_env	*remove_env(t_env **envs, char *key);
void	free_env(t_env *env);
char	*join_path(char *s1, char *s2);
char	*resolve_path(char *file, t_env *envs, int perms);
bool	is_space(char c);
void	skip_spaces(char *line, size_t *i);
int		skip_quotes(char *line);
bool	handle_quotes(char *line, size_t *i);
void	increase_token_index(size_t *count, size_t *i);
char	**tokenize(char *line, t_env *envs, char *pretoken);
bool	special_char(char c);
char	**token_split(char **tokens, size_t *i, bool *split_token, int k);
int		check_end_by_quote(char *line, int i);
int		isinquote(char *token, size_t *i);
char	*replace_env_var(t_env *envs, char *token, \
	bool *split_token, char *tokenpre);
char	*trim_token_quote(char **token);
//==================parsing==================//
void	main_signal(int signal);
void	heredoc_signal(int signal);
void	cmd_signal(int signal);
//==================exec==================//
void	init_pipex(t_cmd **cmds, t_env **envs);
void	ft_heredoc(char *del);
char	*ft_strjoin_gnl(char *stash, char *buff);

//===SETTINGS 	COLORS===/
//===Color font code===/
# define BLACK   "\x1B[30m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1B[37m"
# define ORANGE  "\x1B[38;2;255;128;0m"
# define ROSE    "\x1B[38;2;255;151;203m"
# define LBLUE   "\x1B[38;2;53;149;240m"
# define LGREEN  "\x1B[38;2;17;245;120m"
# define GRAY    "\x1B[38;2;176;174;174m"
# define RESET   "\x1b[0m"

#endif