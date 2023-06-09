/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:54:10 by amalbrei          #+#    #+#             */
/*   Updated: 2023/06/12 21:22:52 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_mini_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>
}	t_state;

typedef struct s_shell
{
	char				*current_line; //original command line
	char				*line; // command line after env
	char				*oldpwd;
	char				**split_pipe; // split line from line
	unsigned long		pos; //Used in Recursive Decent Parsing
	char				**temp2; //might delete these later
	char				*temp1; //might delete these later
	int					exit_code;
	struct s_env		*env;
	struct s_env		*dec_env;
	struct s_command	*command;
}	t_shell;

typedef struct s_env
{
	char				*variable;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_direct
{
	char				*file; // file name
	t_state				direct; // what do to with the files
}	t_direct;

typedef struct s_command
{
	char				**cmd_args; // the command, flag and command line
	char				*cmd_line; // just a temp that i will be using for parsing, you can use it if you want
	int					int_temp; // just like the char temp
	int					redir_amount; // the amount of redirects there are in this command
	t_direct			*redir; // redirects
}	t_command;

extern t_shell	shell;

void	mini_cpyarr(int argc, char *argv[], char **string);
int		ft_double_pointer_counter2(char **dp);
int		ft_operfinder(const char *c);
//everything above this is useless
//--------------------start.c------------------//
void	temp_into_arg(t_shell *shell); // fills in shell.command.temp and does redirections
char	*sp_remover(char *str);// removes speechmarks from a string
//--------------------ft_redirecter.c-------------//
char	*filename2(char *string, int start, int amount);
char	*filename(t_command *command, char *string, int start); //gets the file name
int		redirect_counter(char *string); // redirection counter, mainly for calloc
int		next_redir(char *string, int start); // moves to the next index with the file name
void	redirect_temp(char *string, t_command *command, int start); // sets the direct and file name
void	redir_temp(char *string, t_command *command); // goes though miltiple redirects
void	ft_redirect(t_command *command); // pretty useless 3 line command
// void	redirect_str(char *string, t_command *command); // *NEW* grabs the struct and does the stuff
// void	red(char *string, struct s_command *command); // putting redirecs in strucky waky
//--------------------ft_splitmini.c-------------//
void	check_spmark(char *string); // checks if any open speachmarks
int		ft_skip_spmark(const char *string, int start); // skips all quotaion marks
int		splitcount(const char *string, char separator); //number off commands by pipes
char	**ft_splitmini(const char *string, char separator); // skips all quotaion marks
char	**ft_splitmini2(const char *string, char separator);
int	splitcount2(const char *string, char separator);
//--------------------ft_env.c-------------//
char	*ft_strjoinfree(char *str1, char *str2, int flag);
void	ft_env(t_shell *shell, char *env[]);
//--------------------ft_isalnum_mini.c-------------//
int		ft_isalnum_mini(int c); // isalnum with underscore added
//--------------------ft_env.c-------------//
void	match(char *expected, t_shell *shell, char *string);
void	pipeline(t_shell *shell, char *string);
void	simple_command(t_shell *shell, char *string);
void	io_list(t_shell *shell, char *string);
void	cmd_suffix(t_shell *shell, char *string);
void	io_redirect(t_shell *shell, char *string);
char	*word(char *string, int start);
void	spaces(t_shell *shell, char *string);
void	recursive_decent_parsing(t_shell *shell, char *string);
//-------------------ft_cmd_args.c----------------//
void	ft_cmd_args(t_command *command, char *string);
int		skip_redirect(char *string, int start);
char	*filename_skip(char *string, int start);
//-------------------ft_cmd_args.c----------------//
void	ft_env_loop(t_env *env, char *tenv[], int c);
void	ft_env_init(t_env *env, char *tenv[]);

// in case of ' with $ expansion, dont expand

#endif
