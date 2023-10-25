/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_speechchecker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:16 by smokashi          #+#    #+#             */
/*   Updated: 2023/10/25 10:12:22 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	check_spmark3(int *s_mark, int *counter, char *string)
{
	(*s_mark)++;
	(*counter)++;
	while (string[(*counter)] && string[(*counter)] != '\'')
		(*counter)++;
	if (!string[(*counter)])
		return (1);
	if (string[(*counter)] && string[(*counter)] == '\'')
		(*s_mark)++;
	return (0);
}

int	check_spmark2(int *sp_mark, int *counter, char *string)
{
	(*sp_mark)++;
	(*counter)++;
	while (string[(*counter)] && string[(*counter)] != '"')
		(*counter)++;
	if (!string[(*counter)])
		return (1);
	if (string[(*counter)] && string[(*counter)] == '"')
		(*sp_mark)++;
	return (0);
}

void	check_spmark(t_shell *shell, char *string)
{
	int	counter;
	int	sp_mark;
	int	s_mark;

	sp_mark = 0;
	counter = 0;
	s_mark = 0;
	while (string[counter])
	{
		if (string[counter] == '"')
		{
			if (check_spmark2(&sp_mark, &counter, string) == 1)
				break ;
		}
		else if (string[counter] == '\'')
		{
			if (check_spmark3(&s_mark, &counter, string) == 1)
				break ;
		}
		counter++;
	}
	if (sp_mark % 2 != 0 || s_mark % 2 != 0)
		shell->fail = 1;
}

int	ft_skip_spmark(const char *string, int start)
{
	char	letter;
	int		counter;

	counter = start;
	while (string[counter] && string[counter] != '"'
		&& string[counter] != '\'')
		counter++;
	if (counter == (int)ft_strlen(string))
		return (counter);
	letter = string[counter];
	counter++;
	while (string[counter] && string[counter] != letter)
		counter++;
	return ((counter - start) + 1);
}

char	*sp_remover(char *str)
{
	char	*sp;
	char	quote;
	int		counter;
	int		counter2;

	counter = 0;
	counter2 = 0;
	sp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[counter])
	{
		if (str[counter] && (str[counter] == '\'' || str[counter] == '"'))
		{
			quote = str[counter];
			counter++;
			while (str[counter] && str[counter] != quote)
				sp[counter2++] = str[counter++];
			counter++;
		}
		else
			sp[counter2++] = str[counter++];
	}
	return (ft_strdupfree(sp));
}
