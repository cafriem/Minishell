/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:24 by smokashi          #+#    #+#             */
/*   Updated: 2023/09/04 14:30:45 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	skip_redirect(char *string, int start)
{
	int	counter;

	counter = start;
	if (string[counter] == '>' && string[counter + 1] == '>')
	{
		counter += 2;
		counter += filename_skip(string, counter);
	}
	else if (string[counter] == '<' && string[counter + 1] == '<')
	{
		counter += 2;
		counter += filename_skip(string, counter);
	}
	else if (string[counter] == '>')
	{
		counter += 1;
		counter += filename_skip(string, counter);
	}
	else if (string[counter] == '<')
	{
		counter += 1;
		counter += filename_skip(string, counter);
	}
	return (counter - start);
}

int	redirect_counter(char *string)
{
	int	redirector;
	int	c;

	c = 0;
	redirector = 0;
	while (string[c])
	{
		if ((string[c] == '>' && string[c + 1] == '>')
			|| (string[c] == '<' && string[c + 1] == '<'))
		{
			c += 2;
			redirector++;
		}
		else if (string[c] == '>' || string[c] == '<')
		{
			c++;
			redirector++;
		}
		else if (string[c] == '\'' || string[c] == '\"')
			c += ft_skip_spmark(string, c);
		else
			c++;
	}
	return (redirector);
}
