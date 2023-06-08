/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:31:42 by cafriem           #+#    #+#             */
/*   Updated: 2023/01/21 15:36:44 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

// void	everything_smol(char *string, size_t len)
// {
// 	int	counter;

// 	counter = 0;
// 	while (counter <= len && string)
// 	{
// 		if ((string [counter] >= 65) && (string[counter] <= 90))
// 			string[counter] += 32;
// 		counter++;
// 	}
// }

// int	n_finder(char *string, t_shell shell)
// {
// 	int	sp_marks;
// 	int	counter;
// 	int	end;

// 	counter = 0;
// 	sp_marks = 0;
// 	end = ft_strlen(string);
// 	while (string[counter] != '\0')
// 	{
// 		if (string[counter] == '"')
// 			sp_marks++;
// 		if (string[counter] == '|' && (sp_marks % 2 == 0))
// 			return (counter - 1);
// 		counter++;
// 	}
// 	return (counter);
// }

// void	echo_n(t_parse *parse, t_shell *shell, char *string, int num)
// {
// 	int	end;
// 	int	counter;

// 	counter = 0;
// 	end = ft_strlen(string);
// 	while ((string[counter] == ' ' || string[counter] == '-') && counter != end)
// 	{
// 		while (string[counter] == ' ')
// 			counter++;
// 		if (string[counter] == '-' && string[counter++] == 'n')
// 		{
// 			counter++;
// 			while (string[counter] == 'n')
// 				counter++;
// 			shell->command->flag = ft_strdup('-n');
// 		}
// 	}
// 	parse->target[num] = ft_substr(string, counter--, ft_strlen);
// }

// // strlen till operand
int	ft_operfinder(const char *c)
{
	int	sp_mark;
	int	s_mark;
	int	i;

	i = 0;
	sp_mark = 0;
	s_mark = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while (s_mark % 2 != 0 || sp_mark % 2 != 0)
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
		}
		if (c[i] == '>' || c[i] == '<')
		{
			i--;
			return (i);
		}
		i++;
	}
	return (i);
}

int	ft_direct(const char *c)
{
	int	sp_mark;
	int	s_mark;
	int	oper;
	int	i;

	sp_mark = 0;
	s_mark = 0;
	oper = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while (c[i] && (s_mark % 2 != 0 || sp_mark % 2 != 0))
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
		}
		if (oper == 0)
			return (i);
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			i += 2;
			oper++;
		}
		else if (c[i] == '>' || c[i] == '<')
		{
			i++;
			oper++;
		}
		else
			i++;
	}
	return (i);
}

int	ft_cmd_counter(const char *c)
{
	int	op_counter;
	int	sp_mark;
	int	s_mark;
	int	i;

	op_counter = 1;
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
		}
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<')
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

int main(void)
{
	int	malloc;

	printf("num = %d\n", ft_cmd_counter("lsaiuahd>>iuwa ht"));
}
