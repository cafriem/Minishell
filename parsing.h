/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:28 by smokashi          #+#    #+#             */
/*   Updated: 2023/11/02 15:13:26 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

int	g_exit_signal;

typedef enum e_mini_state
{
	RE_INPUT,
	RE_OUTPUT,
	HERE_DOC,
	APPEND
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*oldpwd;
	char				**split_pipe;
	int					hd;
	unsigned long		pos;
	unsigned long		rdp_temp;
	char				*rdp_word;
	int					number_commands;
	int					fail;
	int					fd_tmp;
	unsigned int		exit_code;
	char				**env_joind;
	struct s_env		*env;
	struct s_command	*command;
}	t_shell;

typedef struct s_env
{
	char				*cmd;
	char				*val;
	struct s_env		*next;
}	t_env;

typedef struct ptr
{
	struct env	*env;
	struct env	*export;
}	t_ptr;

typedef struct s_direct
{
	char				*file;
	t_state				direct;
}	t_direct;

typedef struct s_command
{
	char				**cmd_args;
	char				*cmd_line;
	int					pid;
	int					no_args;
	int					int_temp;
	int					no_redir;
	int					echooption;
	int					fd[2];
	int					fd_redi;
	t_direct			*redir;
}	t_command;

//--------------------start.c------------------//
void	temp_into_arg(t_shell *shell);
char	*sp_remover(char *str);
void	start_work(t_shell *shell);

//--------------------ft_redirecter.c-------------//
char	*filename(t_command *command, char *string, int start);
int		redirect_counter(char *string);
void	redirect_temp(char *string, t_command *command, int start);
void	redir_temp(char *string, t_command *command);
void	ft_redirect(t_command *command);
//--------------------ft_splitmini.c-------------//
void	check_spmark(t_shell *shell, char *string);
int		ft_skip_spmark(const char *string, int start);
int		splitcount(const char *string, char separator);
char	**ft_splitmini(const char *string, char separator);
//--------------------ft_env.c-------------//
char	*ft_strjoinfree(char *str1, char *str2, int flag);
void	ft_env(t_shell *shell, int counter);
//--------------------ft_isalnum_mini.c-------------//
int		ft_isalnum_mini(int c);
//--------------------ft_env.c-------------//
void	match(char *expected, t_shell *shell, char *string);
void	pipeline(t_shell *shell, char *string);
void	simple_command(t_shell *shell, char *string);
void	io_list(t_shell *shell, char *string);
void	cmd_suffix(t_shell *shell, char *string);
void	io_redirect(t_shell *shell, char *string);
char	*word(char *string, int start);
void	spaces(t_shell *shell, char *string);
void	printstruct(t_shell *shell);
void	recursive_decent_parsing(t_shell *shell, char *string);
//-------------------ft_cmd_args.c----------------//
void	ft_cmd_args(t_command *command, char *string);
int		skip_redirect(char *string, int start);
int		filename_skip(char *string, int start);
void	ft_cmd_args_sp(t_command *command);
//-------------------ft_cmd_args.c----------------//
void	ft_env_loop(t_env *env, char *tenv[], int c);
void	ft_env_init(t_shell *shell, char *tenv[]);
//------------------------------------//
char	*ft_strtrim_free(char *s1, char const *set);
void	ft_env_free(t_shell *shell);
void	free_command_args(t_shell *shell);

#endif
