/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:45:10 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/05 18:04:36 by saazcon-         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <dirent.h>

# define WRITE	1
# define READ	0
# define BUFF	4096

typedef struct s_cmd
{
	char			**args;
	char			**cmd;
	char			**infile;
	char			**outfile;
	char			**dl_hd;
	char			*pth_hd;
	char			*pth_cmd;
	char			*name_cmd;
	bool			has_pipe;
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
	int		signal;
	int		exit_status;
	t_env	*envs;
}	t_minishell;

extern t_minishell	g_minishell;

//==================builtins==================//
void	exit_arg(t_cmd *cmd);
int		ft_builtin(t_cmd *cmd, t_env **env, int len);
int		builtin_env(t_cmd *cmd, t_env **envs);
int		builtin_echo(t_cmd *cmd, t_env **envs);
int		builtin_exit(t_cmd *cmd, t_env **envs);
int		builtin_pwd(t_cmd *cmd, t_env **envs);
int		builtin_unset(t_cmd *cmd, t_env **envs);
int		builtin_cd(t_cmd *cmd, t_env **envs);
void	error_identifier(char *identifier);
int		is_builtin(t_cmd *cmd);
int		builtin_export(t_cmd *cmds, t_env **env);
void	print_env_list(t_env **env);
int		process_argument(char *arg, t_env **envs);
int		is_valid_identifier(char *arg);
t_env	*sort_env_list(t_env **env);
int		cmp_env_nodes(t_env *tmp1, t_env *tmp2);
void	swap_env_nodes(t_env *tmp1, t_env *tmp2);
t_env	*create_new_env_node(char *key_value);
void	handle_argument_with_equals(char *arg, t_env **envs);
void	handle_argument_without_equals(char *arg, t_env **envs);
t_env	*find_env_node(t_env **env, char *key);
void	add_env_node(t_env **env, t_env *new_node);
void	free_env_node(t_env *node);
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
void	ft_init_exec(t_cmd **cmds, t_env **env);
void	ft_init_heredoc(struct s_cmd *ps, t_env **envs);
void	ft_init_break(struct s_cmd *ps, char **envp);
void	ft_check_path(t_cmd *ps, char **envp);
void	ft_pipe(int fd[2]);
void	ft_infile(struct s_cmd *ps, int std);
void	ft_outfile(struct s_cmd *ps, int std);
void	ft_wait_for_childs(void);
void	ft_free_double(char **str);
void	ft_free_cmd(t_cmd **cmds, char **envp);
pid_t	ft_fork(void);
int		ft_lstlen(t_cmd *lst);
int		ft_open(char *file, int flags);
int		ft_path(char **env);
char	*ft_strjoin_gnl(char *stash, char *buff);
bool	is_child_process(t_cmd *cmds); //ft de yaq
void	cmds_has_pipes(t_cmd *cmds); //ft de yaq
void	error_e(char *msg, char *more, int exit_status);
void	sig_heredoc(void); //checkea
void	sig_child(void); //checkea
void	sig_parent(void); //checkea
void	sig_ignore(void); //checkea
void	error_st(char *msg, char *more, int exit_status);
int		check_exit_status(t_cmd *cmd);

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