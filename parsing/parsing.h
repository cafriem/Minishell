/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:54:10 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/20 14:15:58 by cafriem          ###   ########.fr       */
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
	RE_INPUT,
	RE_OUTPUT,
	APPEND,
	HERE_DOC
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*line;
	char				*oldpwd;
	int					exit_code;
	struct s_env		*env;
	struct s_env		*dec_env;
	struct s_command	**command;
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
	t_direct			*redir;
}	t_command;

void	mini_cpyarr(int argc, char *argv[], char **string);
int		ft_double_pointer_counter2(char **dp);
int		ft_operfinder(const char *c);

#endif
