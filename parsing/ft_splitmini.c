/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:16 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/07 16:45:09 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_spmark(char *string)
{
	int	counter;
	int	sp_mark;
	int	s_mark;

	sp_mark = 0;
	counter = 0;
	s_mark = 0;
	printf("Checking SP_MARK\n");
	while (string[counter])
	{
		if (string[counter] == '"')
		{
			sp_mark++;
			counter++;
			while (string[counter] && string[counter] != '"')
				counter++;
			if (string[counter] == '"')
				sp_mark++;
		}
		else if (string[counter] == '\'')
		{
			s_mark++;
			counter++;
			while (string[counter] && string[counter] != '\'')
				counter++;
			if (string[counter] == '\'')
				s_mark++;
		}
		counter++;
	}
	if (sp_mark % 2 != 0 || s_mark % 2 != 0)
	{
		printf("PARSE ERROR\n");
		exit (0);
	}
	printf("PASSED SP_CHECKER\n");
}

int	ft_skip_spmark(const char *string, int start)
{
	char	letter;
	int		counter;

	counter = start;
	while (string[counter] && string[counter] != '"' && string[counter] != '\'')
		counter++;
	if (counter == (int)ft_strlen(string))
		return(counter);
	letter = string[counter];
	counter++;
	while (string[counter] != letter)
		counter++;
	return ((counter - start) + 1);
}

int	splitcount(const char *string, char separator)
{
	int	counter;
	int	sep;

	sep = 0;
	counter = 0;
	while (string[counter])
	{
		if (string[counter] == '\'' || string[counter] == '\"')
			counter += ft_skip_spmark(string, counter);
		if (string[counter] == separator)
			sep++;
		counter++;
	}
	return (sep + 1);
}

char	**ft_splitmini(const char *string, char separator)
{
	char	**main;
	int		counter;
	int		start;
	int		word_counter;

	counter = 0;
	word_counter = 0;
	start = 0;
	main = ft_calloc(splitcount(string, separator) + 1, sizeof(char *));
	if (main == NULL)
		return (NULL);
	while (string[counter] != '\0')
	{
		if (string[counter] == '\'' || string[counter] == '"')
			counter += ft_skip_spmark(string, counter);
		if (string[counter] == separator)
		{
			main[word_counter] = ft_strtrim(ft_substr(string, start, (counter - start)), " ");
			start = counter + 1;
			word_counter++;
		}
		counter++;
	}
	main[word_counter] = ft_strtrim(ft_substr(string, start, (counter - start)), " ");
	return (main);
}
