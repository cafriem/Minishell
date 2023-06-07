/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:54:10 by amalbrei          #+#    #+#             */
/*   Updated: 2023/06/07 13:53:19 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "Libft/libft.h"

typedef enum e_mini_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*line;
	char				*oldpwd;
	char				**split_pipe;
	char				**temp2;
	char				*temp1;
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
	char				*file;
	t_state				direct;
}	t_direct;

typedef struct s_command
{
	char				**cmd_args;
	char				*temp;
	char				*split_pipe;
	int					int_temp;
	int					redir_amount;
	t_direct			*redir;
}	t_command;

//use ft_cmd_counter for cmd_args
//cmd_args = [redirect | command | another redirect]

//< t1 grep yes >t2>te

void	mini_cpyarr(int argc, char *argv[], char **string);
int		ft_double_pointer_counter2(char **dp);
int		ft_operfinder(const char *c);
//--------------------ft_redirecter.c-------------//
void	ft_redirect(struct s_command *command); // redirects
char	*filename(t_command *command, char *string, int start); //gets the file name
int		redirect_counter(char *string); // redirection counter, mainly for calloc
int		next_redir(char *string, int start); // moves to the next index with the file name
void	redirect_temp(char *string, t_command *command, int start); // sets the direct and file name
void	redir_temp(char *string, t_command *command); // goes though miltiple redirects
void	ft_redirect(t_command *command); // pretty useless 3 line command
// void	redirect_str(char *string, t_command *command); // *NEW* grabs the struct and does the stuff
// void	red(char *string, struct s_command *command); // putting redirecs in strucky waky
//--------------------ft_splitmini.c-------------//
void	check_spmark2(char *string); // checks if any open speachmarks part 2
void	check_spmark(t_shell *shell, int cmd); // checks if any open speachmarks
int		ft_skip_spmark(const char *string, int start); // skips all quotaion marks
int		splitcount(const char *string, char separator); //number off commands by pipes
char	**ft_splitmini(const char *string, char separator); // skips all quotaion marks


// in case of \ with '$' expansion, dont expand
// redirects, fix " within file names

#endif
