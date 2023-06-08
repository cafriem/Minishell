/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:18:57 by cafriem           #+#    #+#             */
/*   Updated: 2023/01/21 15:58:14 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_opr_counter(const char *c)
{
	int	op_counter;
	int	sp_mark;
	int	s_mark;
	int	i;

	op_counter = 0;
	sp_mark = 0;
	s_mark = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while ((s_mark % 2 != 0 || sp_mark % 2 != 0) && c[i])
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
			// if (!c[i])
			// 	return (0);
		}
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<' || c[i] == '|' )
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;
	size_t	j;
	size_t	size;

	i = start;
	j = 0;
	size = ft_strlen(s);
	if (!s)
		return (0);
	if (len > size)
		len = size;
	if (start + len > size)
		len = size - start;
	if (start >= size)
		len = 0;
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (0);
	while (i < size && j < len)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
}

static void	assigns(const char *s, char **str, char c, int count)
{
	int	start_index;
	int	sp_counter;
	int	s_counter;
	int	j;
	int	i;

	i = 0;
	j = 0;
	sp_counter = 0;
	s_counter = 0;
	while (i < count && s[j])
	{
		if (s[j] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
			j++;
		else
		{
			start_index = j;
			while (s[j] != '\0' && (s[j] != c && (sp_counter % 2 == 0 || s_counter % 2 == 0)))
			{
				while (sp_counter % 2 != 0 || s_counter % 2 != 0)
				{
					if (s[j] == '\'')
						s_counter++;
					if (s[j] == '"')
						sp_counter++;
					j++;
				}
				while (s[j] != c)
				{
					if (s[j] == '\'')
					{
						s_counter++;
						j++;
						break ;
					}
					if (s[j] == '"')
					{
						sp_counter++;
						j++;
						break ;
					}
					j++;
				}
			}
			while (s[j] == c && (sp_counter % 2 != 0 || s_counter % 2 != 0))
			{
				if (s[j] == '\'')
				{
					s_counter++;
					j++;
					break ;
				}
				if (s[j] == '"')
				{
					sp_counter++;
					j++;
					break ;
				}
				j++;
			}
			str[i] = ft_substr(s, start_index, j - start_index);
			i++;
		}
	}
	str[i] = 0;
}

static int	getwordcount(const char *s, char c)
{
	int	sp_counter;
	int	s_counter;
	int	i;
	int	j;

	i = 0;
	j = 0;
	sp_counter = 0;
	s_counter = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s_counter++;
		if (s[i] == '\"')
			sp_counter++;
		if (s[i] == c)
		{
			i++;
			if (s[i] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
			{
				printf("fail\n");
				exit (0);
				//fix men
			}
		}
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			if (sp_counter % 2 == 0 && s_counter % 2 == 0)
				j++;
			i++;
		}
		else if (s[i] != c && s[i + 1] != c)
			i++;
	}
	return (j);
}

char	**ft_splitps(const char *s, char c)
{
	size_t		count;
	char		**str;

	if (!s)
		return (NULL);
	count = ft_opr_counter(s);
	if (count == 0)
		return (NULL);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		return (str);
	assigns(s, str, c, count);
	return (str);
}

void	redir_add(t_parse *parse, t_shell shell, int counter, int redirects)
{
	char	*string;
	int		op2;
	int		op;

	op = ft_operfinder(parse->pipe[counter]) + 1;
	op2 = ft_2ndoperand(parse->pipe[counter]);
	string = ft_strdup(parse->pipe[counter]);
	if (parse->pipe[counter][op] == '<' && parse->pipe[counter][op + 1] == '<')
	{
		shell->command[counter]->redir[redirects]->direct = numbers;
		shell->command[counter]->redir[redirects]->file[redirects] = ft_strtrim(ft_substr(parse->pipe[counter], op, op2), ' ');
		free(parse->pipe[counter]);
		parse->pipe[counter] = ft_strtrim(ft_substr(string, op + 2, ft_strlen(string)), ' ');
	}
	else if (parse->pipe[counter][op] == '>' && parse->pipe[counter][op + 1] == '>')
	{
		shell->command[counter]->redir[redirects]->direct = numbers;
		shell->command[counter]->redir[redirects]->file[redirects] = ft_strtrim(ft_substr(parse->pipe[counter], op + 2, op2)), ' ');
		free(parse->pipe[counter]);
		parse->pipe[counter] = ft_strtrim(ft_substr(string, op + 2, ft_strlen(string)), ' ');
	}
	else if (parse->pipe[counter][op] == '<')
	{
		shell->command[counter]->redir[redirects]->direct = numbers;
		shell->command[counter]->redir[redirects]->file[redirects] = ft_strtrim(ft_substr(parse->pipe[counter], op, op2), ' ');
		free(parse->pipe[counter]);
		parse->pipe[counter] = ft_strtrim(ft_substr(string, op + 1, ft_strlen(string)), ' ');
	}
	else if (parse->pipe[counter][op] == '>')
	{
		shell->command[counter]->redir[redirects]->direct = numbers;
		shell->command[counter]->redir[redirects]->file[redirects] = ft_strtrim(ft_substr(parse->pipe[counter], op + 1, op2)), ' ');
		free(parse->pipe[counter]);
		parse->pipe[counter] = ft_strtrim(ft_substr(string, op + 1, ft_strlen(string)), ' ');
	}
		free(string);
}

void	command_input(t_parse *parse, t_shell shell, int counter)
{
	int	redirects;

	if (ft_strncmp(parse->pipe[counter], "cd ", 3) == 1
		|| ft_strncmp(parse->pipe[counter], "cd\0", 3) == 1)
	{
		shell->command[counter]->cmd_args = ft_calloc(2, sizeof(char *));
		shell->command[counter]->cmd_args[0] = ft_strdup("cd");
		shell->command[counter]->cmd_args[1] = ft_substr(parse->pipe[counter], 3, ft_operfinder(parse->pipe[counter]));
	}
	
	else if (ft_strncmp(parse->pipe[counter], "export ", 7) == 1
		|| ft_strncmp(parse->pipe[counter], "export\0", 7) == 1)
	{
		shell->command[counter]->cmd_args = ft_calloc(2, sizeof(char *));
		shell->command[counter]->cmd_args[0] = ft_strdup("export");
		shell->command[counter]->cmd_args[1] = ft_substr(parse->pipe[counter], 7, ft_operfinder(parse->pipe[counter]));
	}
	
	else if (ft_strncmp(parse->pipe[counter], "pwd ", 4) == 1
		|| ft_strncmp(parse->pipe[counter], "pwd\0", 4) == 1)
	{
		shell->command[counter]->cmd_args = ft_calloc(1, sizeof(char *));
		shell->command[counter]->cmd_args[0] = ft_strdup("pwd");
	}
	
	else if (ft_strncmp(parse->pipe[counter], "env ", 4) == 1
		|| ft_strncmp(parse->pipe[counter], "env\0", 4) == 1)
	{
		shell->command[counter]->cmd_args = ft_calloc(2, sizeof(char *));
		shell->command[counter]->cmd_args[0] = ft_strdup("env");
		shell->command[counter]->cmd_args[1] = ft_substr(parse->pipe[counter], 3, ft_operfinder(parse->pipe[counter]));
	}
	
	else if (ft_strncmp(parse->pipe[counter], "echo", 4) == 1)
	{
		shell->command[counter]->cmd_args = ft_calloc(2, sizeof(char *));
		shell->command[counter]->cmd_args[0] = ft_strdup("echo");
		shell->command[counter]->cmd_args[1] = ft_substr(parse->pipe[counter], 4, ft_operfinder(parse->pipe[counter]));
		echo_n(parse, shell, parse->pipe[counter], counter);
	}
	redirects = 0;
	if (ft_strlen(parse->pipe[counter]) != ft_operfinder(parse->pipe[counter]))
	{
		// ft_calloc(ft_cmd_counter(parse->pipe), t_direct)
		while (ft_strlen(parse->pipe[counter]) != ft_operfinder(parse->pipe[counter]))
		{
			redir_add(parse, shell, counter, redirects);
			redirects++;
		}
	}
	free(parse->pipe[counter]);
}
	// else if (ft_strncmp(parse->pipe[counter], "exit ", 5) == 1
	// 	|| ft_strncmp(parse->pipe[counter], "exit\0", 5) == 1)
	// {
	// 	shell->command[counter]->cmd_args[0] = ft_strdup("exit");
	// 	if (ft_strncmp(parse->pipe[counter], "exit\0", 5) == 1)
	// 		parse->target = ft_strdup("\0");
	// 	else
	// 	{
	// 		parse->pipe[counter] = ft_strtrim(ft_substr(parse->pipe[counter], 5, ft_strlen(parse->pipe[counter])), ' ');
	// 		parse->target[counter] = ft_substr(parse->pipe[counter], 5, ft_strlen(parse->pipe[counter]));
	// 	}
	// 	free(parse->pipe[counter]);
	// }

int	main(void)
{
	t_parse	parse;
	t_shell	shell;
	int		pcounter;
	int		pc;

	parse.pipe = ft_splitps(parse.pipe[pcounter], '|');
	pc = ft_double_pointer_counter2(parse.pipe);
	// shell->command = ft_calloc(pc,);
	pcounter = 0;
	while (pcounter < pc)
	{
		command_input(&parse, &shell, pcounter);
		pcounter++;
	}
}
