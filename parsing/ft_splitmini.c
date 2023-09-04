/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:16 by cafriem           #+#    #+#             */
/*   Updated: 2023/09/04 14:30:45 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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
		else if (string[counter] == separator)
		{
			sep++;
			counter++;
		}
		else
			counter++;
	}
	return (sep + 1);
}

char	**ft_splitmini(const char *string, char separator)
{
	char	**main;
	int		*counter;

	counter = ft_calloc(3, sizeof(int));
	main = ft_calloc(splitcount(string, separator) + 1, sizeof(char *));
	if (main == NULL)
		return (NULL);
	while (string[counter[0]])
	{
		if (string[counter[0]] == '\'' || string[counter[0]] == '"')
			counter[0] += ft_skip_spmark(string, counter[0]);
		else if (string[counter[0]] == separator)
		{
			main[counter[1]] = ft_strtrim_free(ft_substr
					(string, counter[2], (counter[0] - counter[2])), " ");
			counter[2] = counter[0] + 1;
			counter[1]++;
			counter[0]++;
		}
		else
			counter[0]++;
	}
	main[counter[1]] = ft_strtrim_free(
			ft_substr(string, counter[2], (counter[0] - counter[2])), " ");
	return (free(counter), main);
}
